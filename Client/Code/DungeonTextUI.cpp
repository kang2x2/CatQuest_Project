#include "DungeonTextUI.h"
#include "Export_Function.h"

CDungeonTextUI::CDungeonTextUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_ZOOM)
{
}

CDungeonTextUI::CDungeonTextUI(const CDungeonTextUI& rhs)
	: CUI(rhs)
{
}

CDungeonTextUI::~CDungeonTextUI()
{
}

HRESULT CDungeonTextUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	D3DXMatrixIdentity(&m_UImatWorld);

	m_fTranslucent - 0.f;

	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY - 250;

	m_fSizeX = 1162 * 0.4f;
	m_fSizeY = 283 * 0.4f;

	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlpha.Set_Lerp(1.0f, 0.01f, 255);
	
	m_fAcc = 0.f;

	return S_OK;
}

_int CDungeonTextUI::Update_Object(const _float& fTimeDelta)
{
	// 수정시 팀장 보고 필수

	_int iExit = __super::Update_Object(fTimeDelta);

	m_tAlpha.Update_Lerp(fTimeDelta);

	if (m_tAlpha.fCurValue <= 0)
	{
		CEventMgr::GetInstance()->Delete_Obj(this);
		m_fTranslucent = m_tAlpha.fCurValue;
		return iExit;
	}

	if(!m_tAlpha.bActive)
	{
		m_fAcc += fTimeDelta;
		if (2.f < m_fAcc)
		{
			m_tAlpha.Init_Lerp(LERP_MODE::EASE_IN);
			m_tAlpha.Set_Lerp(2.5f, 255, 0);
		}
	}

	m_fTranslucent = m_tAlpha.fCurValue;

	
	return iExit;
}

void CDungeonTextUI::LateUpdate_Object()
{


	__super::LateUpdate_Object();
}

void CDungeonTextUI::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_fTranslucent), 255, 255, 255));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CDungeonTextUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_DungeionText", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CDungeonTextUI* CDungeonTextUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDungeonTextUI* pInstance = new CDungeonTextUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DungeonTextUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDungeonTextUI::Free()
{
	__super::Free();

}
