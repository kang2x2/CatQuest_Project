#include "QuestUI.h"
#include "Export_Function.h"

#include "QuestMgr.h"

CQuestUI::CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_QUEST)
	, m_bLeftDownPos(false) , m_bShowFont(false)
{
}

CQuestUI::CQuestUI(const CQuestUI& rhs)
	: CUI(rhs)
	, m_pQuestUITexCom(rhs.m_pQuestUITexCom)
	, m_matQuestUI(rhs.m_matQuestUI)
	, m_QuestTitleRc(rhs.m_QuestTitleRc)
	, m_QuestContentRc(rhs.m_QuestContentRc)
{
}

CQuestUI::~CQuestUI()
{
}

HRESULT CQuestUI::Ready_Object()
{
	m_eUIType = UI_TYPE::VIEW;

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	D3DXMatrixIdentity(&m_matQuestUI);

	// 퀘스트 UI
	m_fPosX = WINCX - 60;
	m_fPosY = WINCY - 60;
	m_fSizeX = 288.f * 0.1f;
	m_fSizeY = 430.f * 0.1f;
	// m_fMultipleSizeX = 0.15f;
	// m_fMultipleSizeY = 0.15f;

	// 제목
	m_QuestTitleRc = { WINCX - 100, WINCY - 665, WINCX - 100, WINCY - 665 };
	
	// 러프
	// X Size Up
	m_tSizeUpLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeUpLerpX.Set_Lerp(0.6f, m_fSizeX, m_fSizeX * 3.f);
	// Y Size Up
	m_tSizeUpLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeUpLerpY.Set_Lerp(0.6f, m_fSizeY, m_fSizeY * 3.f);

	// X Size Down
	m_tSizeDownLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeDownLerpX.Set_Lerp(0.6f, m_fSizeX * 3.f, m_fSizeX);
	// Y Size Down
	m_tSizeDownLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tSizeDownLerpY.Set_Lerp(0.6f, m_fSizeY * 3.f, m_fSizeY);

	// X Left Down
	m_tLeftDownPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tLeftDownPosLerpX.Set_Lerp(0.6f, m_fPosX, m_fPosX - m_fSizeX * 1.5f);
	// Y Left Down
	m_tLeftDownPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tLeftDownPosLerpY.Set_Lerp(0.6f, m_fPosY, m_fPosY - m_fSizeY * 1.5f);

	// X Right Up
	m_tRightUpPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tRightUpPosLerpX.Set_Lerp(0.6f, m_fPosX - m_fSizeX * 1.5f, m_fPosX);
	// Y Right Up
	m_tRightUpPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
	m_tRightUpPosLerpY.Set_Lerp(0.6f, m_fPosY - m_fSizeY * 1.5f, m_fPosY);


	m_matQuestUI._11 = m_fSizeX;
	m_matQuestUI._22 = m_fSizeY;


	return S_OK;
}

_int CQuestUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	

	if (CQuestMgr::GetInstance()->Get_Quest()->Get_ShowQuestView())
	{
		m_tSizeUpLerpX.Update_Lerp(fTimeDelta);
		m_tSizeUpLerpY.Update_Lerp(fTimeDelta);

		m_tLeftDownPosLerpX.Update_Lerp(fTimeDelta);
		m_tLeftDownPosLerpY.Update_Lerp(fTimeDelta);

		if (!m_tSizeUpLerpX.bActive && !m_tSizeUpLerpY.bActive &&
			!m_tLeftDownPosLerpX.bActive && !m_tLeftDownPosLerpY.bActive)
		{
			m_bShowFont = true;

			// X Size Down
			m_tSizeDownLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tSizeDownLerpX.Set_Lerp(0.6f, m_fSizeX * 3.f, m_fSizeX);
			// Y Size Down
			m_tSizeDownLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tSizeDownLerpY.Set_Lerp(0.6f, m_fSizeY * 3.f, m_fSizeY);

			// X Right Up
			m_tRightUpPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tRightUpPosLerpX.Set_Lerp(0.6f, m_fPosX - m_fSizeX * 1.5f, m_fPosX);
			// Y Right Up
			m_tRightUpPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tRightUpPosLerpY.Set_Lerp(0.6f, m_fPosY - m_fSizeY * 1.5f, m_fPosY);
		}
	}
	else
	{
		m_bShowFont = false;
		if (!m_bShowFont)
		{
			m_tSizeDownLerpX.Update_Lerp(fTimeDelta);
			m_tSizeDownLerpY.Update_Lerp(fTimeDelta);

			m_tRightUpPosLerpX.Update_Lerp(fTimeDelta);
			m_tRightUpPosLerpY.Update_Lerp(fTimeDelta);
		}

		if (!m_tSizeDownLerpX.bActive && !m_tSizeDownLerpY.bActive &&
			!m_tRightUpPosLerpX.bActive && !m_tRightUpPosLerpY.bActive)
		{
			// X Size Up
			m_tSizeUpLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tSizeUpLerpX.Set_Lerp(0.6f, m_fSizeX, m_fSizeX * 3.f);
			// Y Size Up
			m_tSizeUpLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tSizeUpLerpY.Set_Lerp(0.6f, m_fSizeY, m_fSizeY * 3.f);

			// X Left Down
			m_tLeftDownPosLerpX.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tLeftDownPosLerpX.Set_Lerp(0.6f, m_fPosX, m_fPosX - m_fSizeX * 1.5f);
			// Y Left Down
			m_tLeftDownPosLerpY.Init_Lerp(LERP_MODE::SMOOTHERSTEP);
			m_tLeftDownPosLerpY.Set_Lerp(0.6f, m_fPosY, m_fPosY - m_fSizeY * 1.5f);
		}
	}

	if (CQuestMgr::GetInstance()->Get_Quest()->Get_ShowQuestView())
	{
		m_matQuestUI._41 = m_tLeftDownPosLerpX.fCurValue;
		m_matQuestUI._42 = m_tLeftDownPosLerpY.fCurValue - 5.f;
		m_matQuestUI._11 = m_tSizeUpLerpX.fCurValue;
		m_matQuestUI._22 = m_tSizeUpLerpY.fCurValue;
	}
	else
	{
		m_matQuestUI._41 = m_tRightUpPosLerpX.fCurValue;
		m_matQuestUI._42 = m_tRightUpPosLerpY.fCurValue;
		m_matQuestUI._11 = m_tSizeDownLerpX.fCurValue;
		m_matQuestUI._22 = m_tSizeDownLerpY.fCurValue;
	}


	return iExit;
}

void CQuestUI::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CQuestUI::Render_Object()
{
	if (m_bShowFont)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(235, 255, 255, 255));
	}

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matQuestUI);

	m_pQuestUITexCom->Render_Texture();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 보고 싶을 때만
	if (m_bShowFont)
	{
		CGraphicDev::GetInstance()->Get_QuestTitleFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestName().c_str(), -1,
			&m_QuestTitleRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 102, 051, 0));

		for (_int i = 0; i < CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent().size(); ++i)
		{
			m_QuestContentRc = { WINCX - 135, WINCY - 635 + (i * 40), WINCX - 70, WINCY - 635 + (i * 40) };

			if (!CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_bClear)
			{
				CGraphicDev::GetInstance()->Get_QuestContentFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_strQuestContent.c_str(), -1,
					&m_QuestContentRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 153, 102, 0));
			}
			else
			{
				CGraphicDev::GetInstance()->Get_QuestContentFont()->DrawTextW(NULL, CQuestMgr::GetInstance()->Get_Quest()->Get_QuestContent()[i].m_strQuestContent.c_str(), -1,
					&m_QuestContentRc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 051, 051, 153));
			}
		}
	}



	__super::Render_Object();
}

HRESULT CQuestUI::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pQuestUITexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_Quest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

CQuestUI* CQuestUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CQuestUI* pInstance = new CQuestUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("QuestUI Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CQuestUI::Free()
{
	__super::Free();

}
