#include "stdafx.h"
#include "ShadeUI.h"
#include "Export_Function.h"

#include "Player.h"

CShadeUI::CShadeUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev, OBJ_ID::UI_SHADE_UI)
	, m_iTranslucent(0)
{
}

CShadeUI::CShadeUI(const CShadeUI& rhs)
	: CUI(rhs)
{
}

CShadeUI::~CShadeUI()
{
}

HRESULT CShadeUI::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matBack);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV2;

	// 배경
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = WINCX;
	m_fSizeY = WINCY;
	m_matBack._41 = m_fPosX;
	m_matBack._42 = m_fPosY;
	m_matBack._11 = m_fSizeX;
	m_matBack._22 = m_fSizeY;

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	m_tTranslucentLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tTranslucentLerp.Set_Lerp(0.5f, 0.f, 255.f);

	return S_OK;
}

_int CShadeUI::Update_Object(const _float& fTimeDelta)
{
	m_tTranslucentLerp.Update_Lerp(fTimeDelta);
	m_iTranslucent = (_int)m_tTranslucentLerp.fCurValue;

	_int iExit = __super::Update_Object(fTimeDelta);

	return iExit;
}

void CShadeUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CShadeUI::Render_Object()
{
	// 초기 세팅
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	// 배경
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matBack);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();


	__super::Render_Object();
}


HRESULT CShadeUI::Add_Component()
{

	CComponent* pComponent = nullptr;
	// 배경
	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Shade", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, m_pTextureCom);

	// 버퍼
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CShadeUI* CShadeUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CShadeUI* pInstance = new CShadeUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("ShadeUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CShadeUI::Free()
{
	__super::Free();

}
