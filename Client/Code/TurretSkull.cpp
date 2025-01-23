#include "stdafx.h"
#include "TurretSkull.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "Shadow_Monster.h"
#include "Pile_Bullet.h"
#include "Player.h"


CTurretSkull::CTurretSkull(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev, OBJ_ID::MONSTER_TURRETSKULL)
{
}

CTurretSkull::CTurretSkull(const CMonster& rhs)
	: CMonster(rhs)
{
}

CTurretSkull::~CTurretSkull()
{
}

HRESULT CTurretSkull::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// Stat Info
	m_tStatInfo.bDead = false;
	m_tStatInfo.fCurHP = 1000.f;
	m_tStatInfo.fMaxHP = m_tStatInfo.fCurHP;
	//m_tStatInfo.fAD = 30.f;


	// 원래 이미지 크기
	m_vImageSize.x = 0.76f; // 100px = 1.f
	m_vImageSize.y = 1.34f;
	m_vImageSize.z = 2.f; //  고정

	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 3.f, m_vImageSize.y * 3.f, m_vImageSize.z });
	m_pTransformCom->Set_Pos(_vec3{ 451.f, m_pTransformCom->Get_Scale().y, 390.f });

	std::mt19937 gen(m_Random());
	std::bernoulli_distribution coinFlip(0.5);

	if (coinFlip(gen))
	{
		m_pTransformCom->Set_Dir({ 1.f, 0.f, 0.f });
		m_iDirZ = 0;
	}
	else
	{
		m_pTransformCom->Set_Dir({ -1.f, 0.f, 0.f });
		m_iDirZ = 0;
	}

	
	m_fAccTime = 2.f;

	m_bSkill = false;

	m_pPlayer = nullptr;

	m_szName = L"Turret_Skull";

	m_fHigh = m_pTransformCom->Get_Info(INFO::INFO_POS).y + 1;
	m_fLow = m_pTransformCom->Get_Info(INFO::INFO_POS).y - 1;

	m_tPosY.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tPosY.Set_Lerp(0.8f, m_pTransformCom->Get_Info(INFO::INFO_POS).y, m_fHigh);

	m_pStateMachineCom = nullptr;

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Turret_Shadow",
			CShadow_Monster::Create(m_pGraphicDev, this, m_pTransformCom->Get_Scale().y * 0.7, 1.5f));

	return S_OK;
}

_int CTurretSkull::Update_Object(const _float& fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_ALPHA, this);
	_int iExit = CMonster::Update_Object(fTimeDelta);

	if (m_pTransformCom->Get_Info(INFO::INFO_POS).y == m_fHigh)
	{
		m_tPosY.Init_Lerp(LERP_MODE::SMOOTHSTEP);
		m_tPosY.Set_Lerp(2.f, m_pTransformCom->Get_Info(INFO::INFO_POS).y, m_fLow);
	}
	else if (m_pTransformCom->Get_Info(INFO::INFO_POS).y == m_fLow)
	{
		m_tPosY.Init_Lerp(LERP_MODE::SMOOTHSTEP);
		m_tPosY.Set_Lerp(2.f, m_pTransformCom->Get_Info(INFO::INFO_POS).y, m_fHigh);
	}


	m_tPosY.Update_Lerp(fTimeDelta);
	m_pTransformCom->Set_PosY(m_tPosY.fCurValue);


	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	if (nullptr != m_pPlayer)
	{
		m_vDir = m_pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pTransformCom->Get_Info(INFO::INFO_POS);
		m_fLength = D3DXVec3Length(&m_vDir);
		


		if (m_fLength < 65)
		{
			m_pTransformCom->Set_Dir(m_vDir);
			m_bAttack = true;
		}
		else
		{
			m_bAttack = false;
			m_fAccTime = 0.f;
		}
			
	}

	if (m_bAttack)
	{
		m_fAccTime += fTimeDelta;
		if (m_fAccTime > 3.f)
		{
			CGameObject* pBullet = CPile_Bullet::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO::INFO_POS), m_pPlayer, this);
			CEventMgr::GetInstance()->Add_Obj(L"Pile_Bullet", pBullet);

			m_fAccTime -= 3.f;
		}
	}
	

	return iExit;
}

void CTurretSkull::LateUpdate_Object()
{
	if (CInputDev::GetInstance()->Key_Down(VK_F7))
	{
		m_tStatInfo.bDead = TRUE;
	}
	if (m_bHit)
		m_bHit = false;

	if (m_pTransformCom->Get_Dir().z <= 0)
		m_iDirZ = 0;
	else
		m_iDirZ = 1;

	if (m_pTransformCom->Get_Dir().x < 0)
	{
		if (m_pTransformCom->Get_Scale().x > 0)
			m_pTransformCom->Reverse();
	}
	else
	{
		if (m_pTransformCom->Get_Scale().x < 0)
			m_pTransformCom->Reverse();
	}

	__super::LateUpdate_Object();
}

void CTurretSkull::Render_Object()
{
	// 피격 시 red
	if (m_bHit)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(HITCOLOR_A, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));
	}
	else
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());


	m_pTextureCom->Render_Texture(m_iDirZ);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object();

	// 원래 색상 상태로 돌리기 
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	__super::Render_Object(); // 콜라이더 출력

}

void CTurretSkull::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);
}

void CTurretSkull::OnCollision_Stay(CGameObject* _pColObj)
{
	__super::OnCollision_Stay(_pColObj);
}

void CTurretSkull::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CTurretSkull::Add_Component()
{
	CComponent* pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Monster_Skull", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}



CTurretSkull* CTurretSkull::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTurretSkull* pInstance = new CTurretSkull(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TurretSkull Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTurretSkull::Free()
{
	__super::Free();
}
