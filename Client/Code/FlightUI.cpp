#include "FlightUI.h"
#include "Export_Function.h"

#include "Player.h"

CFlightUI::CFlightUI(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer)
     :CUI(pGraphicDev, OBJ_ID::UI_FLIGHT), m_pPlayer(pPlayer)
{
}

CFlightUI::CFlightUI(const CFlightUI& rhs)
	: CUI(rhs)
{
	m_pPlayer = rhs.m_pPlayer;
}

CFlightUI::~CFlightUI()
{
}

HRESULT CFlightUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = 98;
	m_fPosY = 140;

	m_fSizeX = 32.76 * 0.9;
	m_fSizeY = 39.69 * 0.9;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = WINCY - m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	return S_OK;
}

_int CFlightUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
		
	return iExit;
}

void CFlightUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFlightUI::Render_Object()
{
	if(!m_pPlayer->Has_Flight())
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 100, 100, 100));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();


	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CFlightUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Flight", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CFlightUI* CFlightUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer)
{
	CFlightUI* pInstance = new CFlightUI(pGraphicDev, pPlayer);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlightUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CFlightUI::Free()
{
	__super::Free();

}
