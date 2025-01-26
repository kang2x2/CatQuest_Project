#include "stdafx.h"
#include "Bingo_FailUI.h"
#include "Export_Function.h"

CBingo_FailUI::CBingo_FailUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_BINGO_FAIL)
	, m_iLerpLevel(0), m_fCurSize(0.f)
{
}

CBingo_FailUI::CBingo_FailUI(const CBingo_FailUI& rhs)
	: CUI(rhs)
{
}

CBingo_FailUI::~CBingo_FailUI()
{
}

HRESULT CBingo_FailUI::Ready_Object()
{
	D3DXMatrixIdentity(&m_UImatWorld);

	m_eUIType = UI_TYPE::VIEW;

	m_fSizeX = 90.f;
	m_fSizeY = 90.f;
	m_fPosX = WINCX / 2;
	m_fPosY = WINCY - 150;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	Ready_Lerp();

	m_bActive = true;

	m_szName = L"Bingo_FailUI";

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CBingo_FailUI::Ready_Lerp()
{
	// 등장 러프 세팅
	m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeUpLerp.Set_Lerp(0.5f, 0.f, m_fSizeX * 1.5f);

	m_tSizeReturnLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeReturnLerp.Set_Lerp(0.25f, m_fSizeX * 1.5f, m_fSizeX);

	// 딜리트 러프 세팅(이 러프가 끝나면 UI 사라지게)
	m_tDeleteLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDeleteLerp.Set_Lerp(1.f, 1.f, 0.f);

	// 소멸 러프 세팅
	m_tDelSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tDelSizeUpLerp.Set_Lerp(0.25f, m_fSizeX, m_fSizeX * 1.5f);

	m_tDelSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDelSizeDownLerp.Set_Lerp(0.5f, m_fSizeX * 1.5f, 0.f);
}

_int CBingo_FailUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	switch (m_iLerpLevel)
	{
	case 0:
		m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_fCurSize = m_tSizeUpLerp.fCurValue;

		if (!m_tSizeUpLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 1:
		m_tSizeReturnLerp.Update_Lerp(fTimeDelta);
		m_fCurSize = m_tSizeReturnLerp.fCurValue;

		if (!m_tSizeReturnLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 2:
		m_tDeleteLerp.Update_Lerp(fTimeDelta);

		if (!m_tDeleteLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 3:
		m_tDelSizeUpLerp.Update_Lerp(fTimeDelta);
		m_fCurSize = m_tDelSizeUpLerp.fCurValue;

		if (!m_tDelSizeUpLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 4:
		m_tDelSizeDownLerp.Update_Lerp(fTimeDelta);
		m_fCurSize = m_tDelSizeDownLerp.fCurValue;

		if (!m_tDelSizeDownLerp.bActive)
			m_iLerpLevel += 1;
		break;
	case 5:
		CEventMgr::GetInstance()->Delete_Obj(this);
		break;
	}

	m_UImatWorld._11 = m_fCurSize;
	m_UImatWorld._22 = m_fCurSize;

	return iExit;
}

void CBingo_FailUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBingo_FailUI::Render_Object()
{
	//m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(235, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CBingo_FailUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bingo_Fail", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CBingo_FailUI* CBingo_FailUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBingo_FailUI* pInstance = new CBingo_FailUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bingo_FailUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBingo_FailUI::Free()
{
	__super::Free();
}
