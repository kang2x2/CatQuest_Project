#include "stdafx.h"
#include "..\Header\Player_AfterImg.h"
#include "..\Header\Player.h"
#include "Export_Function.h"

CPlayer_AfterImg::CPlayer_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CGameObject(pGraphicDev, OBJ_TYPE::PLAYER, _eID)
{
}

CPlayer_AfterImg::CPlayer_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CGameObject(pGraphicDev, OBJ_TYPE::EFFECT, OBJ_ID::PLAYER_AFTERIMG), m_pOwner(_pOwnerObject)
{
}

CPlayer_AfterImg::CPlayer_AfterImg(const CPlayer_AfterImg& rhs)
    : Engine::CGameObject(rhs)
{
}

CPlayer_AfterImg::~CPlayer_AfterImg()
{
}

HRESULT CPlayer_AfterImg::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	NULL_CHECK_RETURN(m_pOwner, E_FAIL);

	CPlayer* pPlayer = static_cast<CPlayer*>(m_pOwner);
	
	m_eCurState = pPlayer->Get_StateM()->Get_CurState();
	m_iCurFrame = pPlayer->Get_StateM()->Get_Animator()->Get_CurAniamtion()->Get_CurFrame();
	m_vCurPos = pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);
	m_vCurPos.z += 0.01f;
	m_pTransformCom->Set_Pos(m_vCurPos);
	m_pTransformCom->Set_Scale(pPlayer->Get_Transform()->Get_Scale());

	m_iAlpha = pPlayer->Get_ClockAlpha();
	m_tAlpha.Init_Lerp();
	m_tAlpha.Set_Lerp(0.3, m_iAlpha, 0);
	m_tAlpha.fCurValue = m_tAlpha.fStartValue;

	m_bActive = false;
	m_bOff = false;

    return S_OK;
}

_int CPlayer_AfterImg::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_iAlpha <= 0)
		CEventMgr::GetInstance()->Delete_Obj(this);


	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_tAlpha.Update_Lerp(fTimeDelta);


	return iExit;
}

void CPlayer_AfterImg::LateUpdate_Object()
{
	m_iAlpha = m_tAlpha.fCurValue;

	__super::LateUpdate_Object();
}

void CPlayer_AfterImg::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pNinjaTextureCom[_uint(m_eCurState)]->Render_Texture(m_iCurFrame);
	m_pBufferCom->Render_Buffer();


	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CPlayer_AfterImg::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


#pragma region Texture
	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
#pragma endregion

	
    return S_OK;
}

CPlayer_AfterImg* CPlayer_AfterImg::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CPlayer_AfterImg* pInstance = new CPlayer_AfterImg(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player_AfterImg Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayer_AfterImg::Free()
{
	__super::Free();
}
