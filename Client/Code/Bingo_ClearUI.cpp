#include "stdafx.h"
#include "Bingo_ClearUI.h"
#include "Export_Function.h"

CBingo_ClearUI::CBingo_ClearUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_BINGO_CLEAR)
	, m_iLerpLevel(0), m_fCurSize(0.f) , m_bUp(false)
{
}

CBingo_ClearUI::CBingo_ClearUI(const CBingo_ClearUI& rhs)
	: CUI(rhs)
{
}

CBingo_ClearUI::~CBingo_ClearUI()
{
}

HRESULT CBingo_ClearUI::Ready_Object()
{
	D3DXMatrixIdentity(&m_UImatWorld);

	m_eUIType = UI_TYPE::VIEW;

	m_fSizeX = 115.f;
	m_fSizeY = 115.f;
	m_fPosX = WINCX / 2;
	m_fPosY = WINCY / 2;

	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;

	Ready_Lerp();

	m_bActive = true;

	m_szName = L"Bingo_ClearUI";

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CBingo_ClearUI::Ready_Lerp()
{
	// 등장 러프 세팅
	m_tSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeUpLerp.Set_Lerp(0.5f, 0.f, m_fSizeX * 1.5f);

	m_tSizeReturnLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeReturnLerp.Set_Lerp(0.25f, m_fSizeX * 1.5f, m_fSizeX);

	// 딜리트 러프 세팅(이 러프가 끝나면 UI 사라지게)
	m_tDeleteLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDeleteLerp.Set_Lerp(3.5f, 1.f, 0.f);

	// 부유 러프
	m_tPosUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tPosUpLerp.Set_Lerp(0.5f, m_fPosY - 10.f, m_fPosY + 10.f);
	m_tPosDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tPosDownLerp.Set_Lerp(0.5f, m_fPosY + 10.f, m_fPosY - 10.f);

	// 소멸 러프 세팅
	m_tDelSizeUpLerp.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tDelSizeUpLerp.Set_Lerp(0.25f, m_fSizeX, m_fSizeX * 1.5f);

	m_tDelSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDelSizeDownLerp.Set_Lerp(0.5f, m_fSizeX * 1.5f, 0.f);
}

_int CBingo_ClearUI::Update_Object(const _float& fTimeDelta)
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

	if (!m_bUp)
	{
		m_tPosDownLerp.Update_Lerp(fTimeDelta);
		m_UImatWorld._42 = m_tPosDownLerp.fCurValue;
		if (!m_tPosDownLerp.bActive)
		{
			m_tPosUpLerp.Init_Lerp(LERP_MODE::EXPONENTIAL);
			m_tPosUpLerp.Set_Lerp(0.75f, m_fPosY - 10.f, m_fPosY + 10.f);
			m_bUp = true;
		}
	}
	if (m_bUp)
	{
		m_tPosUpLerp.Update_Lerp(fTimeDelta);
		m_UImatWorld._42 = m_tPosUpLerp.fCurValue;
		if (!m_tPosUpLerp.bActive)
		{
			m_tPosDownLerp.Init_Lerp(LERP_MODE::EXPONENTIAL);
			m_tPosDownLerp.Set_Lerp(0.75f, m_fPosY + 10.f, m_fPosY - 10.f);
			m_bUp = false;
		}
	}

	m_UImatWorld._11 = m_fCurSize;
	m_UImatWorld._22 = m_fCurSize;

	return iExit;
}

void CBingo_ClearUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBingo_ClearUI::Render_Object()
{
	//m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(235, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	//m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CBingo_ClearUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bingo_Succes", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

CBingo_ClearUI* CBingo_ClearUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBingo_ClearUI* pInstance = new CBingo_ClearUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bingo_ClearUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBingo_ClearUI::Free()
{
	__super::Free();
}
