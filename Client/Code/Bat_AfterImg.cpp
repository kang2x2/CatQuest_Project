#include "stdafx.h"
#include "Bat_AfterImg.h"
#include "Bat.h"
#include "Export_Function.h"

CBat_AfterImg::CBat_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CGameObject(pGraphicDev, OBJ_TYPE::MONSTER, _eID)
{
}

CBat_AfterImg::CBat_AfterImg(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CGameObject(pGraphicDev, OBJ_TYPE::EFFECT, OBJ_ID::BAT_AFTERIMG), m_pOwner(_pOwnerObject)
{
}

CBat_AfterImg::CBat_AfterImg(const CBat_AfterImg& rhs)
    : Engine::CGameObject(rhs)
{
}

CBat_AfterImg::~CBat_AfterImg()
{
}

HRESULT CBat_AfterImg::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	NULL_CHECK_RETURN(m_pOwner, E_FAIL);

	CBat* pBat = static_cast<CBat*>(m_pOwner);
	
	m_eCurState = pBat->Get_StateM()->Get_CurState();
	m_iCurFrame = pBat->Get_StateM()->Get_Animator()->Get_CurAniamtion()->Get_CurFrame();
	m_vCurPos = pBat->Get_Transform()->Get_Info(INFO::INFO_POS);
	m_vCurPos.z += 0.01f;
	m_pTransformCom->Set_Pos(m_vCurPos);
	m_pTransformCom->Set_Scale(pBat->Get_Transform()->Get_Scale());

	//m_iAlpha = pBat->Get_ClockAlpha();
	m_tAlpha.Init_Lerp();
	m_tAlpha.Set_Lerp(0.3, m_iAlpha, 0);
	m_tAlpha.fCurValue = m_tAlpha.fStartValue;

	m_bActive = false;
	m_bOff = false;

    return S_OK;
}

_int CBat_AfterImg::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_iAlpha <= 0)
		CEventMgr::GetInstance()->Delete_Obj(this);


	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_tAlpha.Update_Lerp(fTimeDelta);


	return iExit;
}

void CBat_AfterImg::LateUpdate_Object()
{
	m_iAlpha = m_tAlpha.fCurValue;

	__super::LateUpdate_Object();
}

void CBat_AfterImg::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pTextureCom[_uint(m_eCurState)]->Render_Texture(m_iCurFrame);
	m_pBufferCom->Render_Buffer();


	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CBat_AfterImg::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


#pragma region Texture
	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Bat", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion

	
    return S_OK;
}

CBat_AfterImg* CBat_AfterImg::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CBat_AfterImg* pInstance = new CBat_AfterImg(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bat_AfterImg Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBat_AfterImg::Free()
{
	__super::Free();
}
