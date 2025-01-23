#include "stdafx.h"
#include "TabUI.h"
#include "Export_Function.h"

CTabUI::CTabUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_TAB)
	,m_bPick(false)
{
}

CTabUI::CTabUI(const CTabUI& rhs)
	: CUI(rhs)
	, m_bPick(rhs.m_bPick)
{
	// 그냥 텍스쳐 cpp 터레인 띠우는 리소스
}

CTabUI::~CTabUI()
{
}

HRESULT CTabUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CTabUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Picking_UI();

	return iExit;
}

void CTabUI::LateUpdate_Object()
{

	// 새로운 뷰포트에서 쓸 월드스페이스 구성
	D3DXMatrixIdentity(&m_UImatWorld);

	m_fPosX = 82;
	m_fPosY = WINCY - 650;

	m_fSizeX = 66.5 * 0.9f;;
	m_fSizeY = 54.5 * 0.9f;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	m_rcUI = { long(m_fPosX - m_fSizeX / 2.f) , long(m_fPosY - m_fSizeY / 2.f) , long(m_fPosX + m_fSizeX / 2.f) , long(m_fPosY + m_fSizeY / 2.f) };
	
	

	__super::LateUpdate_Object();
}

void CTabUI::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	if (m_bPick)
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));
	}
	else
	{
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	}

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

void CTabUI::Picking_UI()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	D3DVIEWPORT9 ViewPort;

	m_pGraphicDev->GetViewport(&ViewPort);

	pt.y = WINCY - pt.y;  

	if (PtInRect(&m_rcUI, pt))
	{
		m_bPick = true;
	
	}
	else
	{
		m_bPick = false;
	}

}

HRESULT CTabUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Tab", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CTabUI* CTabUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTabUI* pInstance = new CTabUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TabUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTabUI::Free()
{
	__super::Free();

}
