#include "stdafx.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

CPlayerSlash::CPlayerSlash(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, _bool _IsRising)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_PLAYERSLASH)
{
	m_pOwnerobject = _pOwnerObject;
	m_bRisign = _IsRising;

	if (_pOwnerObject->Get_Transform()->Get_Scale().x > 0) m_bRight = true;
	if (_pOwnerObject->Get_Transform()->Get_Scale().x < 0) m_bRight = false;
}

CPlayerSlash::CPlayerSlash(const CPlayerSlash& rhs)
	: CEffect(rhs),
	m_pTexRisingCom(rhs.m_pTexRisingCom),
	m_pTexChoppingCom(rhs.m_pTexChoppingCom)
{
}

CPlayerSlash::~CPlayerSlash()
{
}

HRESULT CPlayerSlash::Ready_Object()
{
	__super::Ready_Object();

	// CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// 애니메이션 세팅
	if (m_bRisign)
		m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTexRisingCom, STATE_TYPE::FRONT_IDLE, 0.05f, true);
	if (!m_bRisign)
		m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTexChoppingCom, STATE_TYPE::FRONT_IDLE, 0.05f, true);

	m_bActive = true;
	m_eUILayer = UI_LAYER::LV2;

	return S_OK;
}

_int CPlayerSlash::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_WDUI, this);

	// 좌 우 세팅 (이상할 시 Ready에서 만들자)
	if (m_bRight)
	{
		m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x + m_pOwnerobject->Get_Transform()->Get_Scale().x * 0.35f,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
		m_pTransformCom->Set_Scale(_vec3{ 2.5f, 2.5f, 2.5f });
	}
	if (!m_bRight)
	{
		m_pTransformCom->Set_Pos(_vec3{ m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).x - (m_pOwnerobject->Get_Transform()->Get_Scale().x * -0.35f),
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).y,
		m_pOwnerobject->Get_Transform()->Get_Info(INFO_POS).z });
		m_pTransformCom->Set_Scale(_vec3{ -2.5f, 2.5f, 2.5f });
	}

	m_pAnimation->Update_Animation(fTimeDelta);


	if (m_pAnimation->Is_End())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
	}

	if (!m_pOwnerobject->Is_Active())
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		return iExit;
	}


	return iExit;
}

void CPlayerSlash::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CPlayerSlash::Render_Object()
{
	m_pAnimation->Render_Animation();

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
}

HRESULT CPlayerSlash::Add_Component()
{
	CComponent* pComponent = nullptr;

	// 라이징
	pComponent = m_pTexRisingCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Player_Slash_Rising", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	// 쵸핑
	pComponent = m_pTexChoppingCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Player_Slash_Chopping", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CPlayerSlash::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CPlayerSlash* CPlayerSlash::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, _bool _IsRising)
{
	CPlayerSlash* pInstance = new CPlayerSlash(pGraphicDev, _pOwnerObject, _IsRising);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player_Slash Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerSlash::Free()
{
	m_pAnimation->Release();
	__super::Free();
}
