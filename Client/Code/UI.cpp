#include "UI.h"
#include "Export_Function.h"



CUI::CUI(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::UI, _eID)
	, m_pTextureCom(nullptr)
	, m_eUIType(UI_TYPE::TYPEEND)

{
	D3DXMatrixIdentity(&m_UImatWorld);
	m_fPosX = 0.f;
	m_fPosY = 0.f;
	m_fSizeX = 0.f;
	m_fSizeY = 0.f;
	m_fMultipleSizeX = 1.f;
	m_fMultipleSizeY = 1.f;
}

CUI::CUI(const CUI& rhs)
	:Engine::CGameObject(rhs)
{
	m_pTextureCom = rhs.m_pTextureCom;
	m_eUIType = rhs.m_eUIType;
	m_UImatWorld = rhs.m_UImatWorld;
	m_fPosX = rhs.m_fPosX;
	m_fPosY = rhs.m_fPosY;
	m_fSizeX = rhs.m_fSizeX;
	m_fSizeY = rhs.m_fSizeY;
	m_fMultipleSizeX = rhs.m_fMultipleSizeX;
	m_fMultipleSizeY = rhs.m_fMultipleSizeY;
}

CUI::~CUI()
{
}

HRESULT CUI::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CUI::Update_Object(const _float& fTimeDelta)
{

	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_eUIType == UI_TYPE::VIEW)
	{
		Engine::Add_RenderGroup(RENDER_VIEWUI, this);
	}
	else if (m_eUIType == UI_TYPE::WORLD)
	{
		Engine::Add_RenderGroup(RENDER_WDUI, this);
	}

	return iExit;
}

void CUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CUI::Render_Object()
{	
}

void CUI::Free()
{
	__super::Free();
}
