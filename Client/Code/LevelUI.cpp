#include "LevelUI.h"
#include "Export_Function.h"

#include "Player.h"

CLevelUI::CLevelUI(LPDIRECT3DDEVICE9 pGraphicDev)
     :CUI(pGraphicDev, OBJ_ID::UI_LEVEL), m_pPlayer(nullptr)
{
}

CLevelUI::CLevelUI(const CLevelUI& rhs)
	: CUI(rhs)
{
	m_pPlayer = rhs.m_pPlayer;
	m_strPlayerLevel = rhs.m_strPlayerLevel;
}

CLevelUI::~CLevelUI()
{
}

HRESULT CLevelUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV0;
	
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = 68;
	m_fPosY = 72;

	m_fSizeX =  48 * 0.8;
	m_fSizeY =  64 * 0.8;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = WINCY - m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	m_rcLevel.left = m_fPosX - m_fSizeX + 1;
	m_rcLevel.right = m_fPosX + m_fSizeX + 1;
	m_rcLevel.top = m_fPosY - m_fSizeY + 8;
	m_rcLevel.bottom = m_fPosY + m_fSizeY + 8;
	
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CLevelUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (nullptr == m_pPlayer)
		m_pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
		
	if (nullptr != m_pPlayer)
		m_strPlayerLevel = to_wstring(m_pPlayer->Get_StatInfo().iLevel);

	return iExit;
}

void CLevelUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CLevelUI::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	CGraphicDev::GetInstance()->Get_LevelFont()->DrawTextW(NULL, m_strPlayerLevel.c_str(), -1, 
		&m_rcLevel, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(200, 0, 0, 0));

	__super::Render_Object();
}

HRESULT CLevelUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Level", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CLevelUI* CLevelUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLevelUI* pInstance = new CLevelUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("LevelUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLevelUI::Free()
{
	__super::Free();

}
