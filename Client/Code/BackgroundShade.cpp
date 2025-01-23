#include "BackgroundShade.h"
#include "Export_Function.h"



CBackgroundShade::CBackgroundShade(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev, OBJ_ID::UI_BACKGROUND)
{
}

CBackgroundShade::CBackgroundShade(const CBackgroundShade& rhs)
	: CUI(rhs)
{
}

CBackgroundShade::~CBackgroundShade()
{
}

HRESULT CBackgroundShade::Ready_Object()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;

	m_eUILayer = UI_LAYER::LV1;

	m_szName = L"Background_Shdae";

	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld._41 = (WINCX >> 1);
	m_matWorld._42 = (WINCY >> 1);
	m_matWorld._11 = WINCX;
	m_matWorld._22 = WINCY;

	return S_OK;
}

_int CBackgroundShade::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);


	return iExit;
}

void CBackgroundShade::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBackgroundShade::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(50, 255, 255, 255));

	//m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pTextureCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();

}


HRESULT CBackgroundShade::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Background_White", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CBackgroundShade* CBackgroundShade::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackgroundShade* pInstance = new CBackgroundShade(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Background Shade Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBackgroundShade::Free()
{
	__super::Free();
}
