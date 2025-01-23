#include "Quest_DialogUI.h"
#include "Export_Function.h"

#include "Player.h"

CQuest_DialogUI::CQuest_DialogUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev, OBJ_ID::UI_QUEST_DIALOG), m_bEnd(false)
{
}

CQuest_DialogUI::CQuest_DialogUI(const CQuest_DialogUI& rhs)
	: CUI(rhs)
{
}

CQuest_DialogUI::~CQuest_DialogUI()
{
}

HRESULT CQuest_DialogUI::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eUIType = UI_TYPE::VIEW;
	m_eUILayer = UI_LAYER::LV1;

	D3DXMatrixIdentity(&m_UImatWorld);
	D3DXMatrixIdentity(&m_matUI);

	// 처음 사이즈와 위치
	m_fPosX = WINCX >> 1;
	m_fPosY = WINCY >> 1;
	m_fSizeX = 400;
	m_fSizeY = 124;
	// 텍스트상자의 위치와 사이즈
	m_rcText = { long(m_fPosX - (m_fSizeX / 2.f) - 20) , long(WINCY - m_fPosY - (m_fSizeY / 2.f)),
		long(m_fPosX + (m_fSizeX / 2.f) + 20) , long(WINCY - m_fPosY + m_fSizeY / 2.f) };

	// 스피치박스의 초기 설정
	m_UImatWorld._41 = m_fPosX;
	m_UImatWorld._42 = m_fPosY;
	m_UImatWorld._11 = m_fSizeX;
	m_UImatWorld._22 = m_fSizeY;

	// 텍스트 박스 사이즈 러프 세팅
	m_tSizeUpLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeUpLerpX.Set_Lerp(0.3f, 0.f, m_fSizeX);

	m_tSizeDownLerpX.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeDownLerpX.Set_Lerp(0.3f, m_fSizeX, 0.f);


	// 알파
	m_tAlphaUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaUpLerp.Set_Lerp(0.3f, 0.f, 255.f);
	m_tAlphaDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaDownLerp.Set_Lerp(0.3f, 225.f, 0.f);

	m_fAlpha = 0.f;

	return S_OK;
}

_int CQuest_DialogUI::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	if (m_bDialogType == DIALOG_TYPE::DIALOG_START)
	{
		m_tSizeUpLerpX.Update_Lerp(fTimeDelta);
		m_tSizeUpLerpY.Update_Lerp(fTimeDelta);
		m_tAlphaUpLerp.Update_Lerp(fTimeDelta);

		m_UImatWorld._11 = m_tSizeUpLerpX.fCurValue;
		m_UImatWorld._22 = m_tSizeUpLerpY.fCurValue;
		m_fAlpha = m_tAlphaUpLerp.fCurValue;

		if (!m_tSizeUpLerpX.bActive && !m_tSizeUpLerpY.bActive)
		{
			m_bDialogType = DIALOG_TYPE::DIALOG_NORMAL;
		}
	}

	if (m_bDialogType == DIALOG_TYPE::DIALOG_NORMAL)
	{
		m_fAlpha = 255.f;
		
		m_tAlphaFont.Update_Lerp(fTimeDelta);
		m_fAlphaFont = m_tAlphaFont.fCurValue;

		_float fReach = 1.f;
		if (m_bDown)
		{
			_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_matUI._41, m_matUI._42, 0.f }
			, _vec3{ m_matUI._41, m_matUI._42 - fReach, 0.f }, 0.3f, fTimeDelta, LERP_MODE::SMOOTHSTEP);
			if (vOut.x != -99)
			{
				m_matUI._42 = vOut.y;
			}
			else
			{
				m_bDown = false;
				m_bUp = true;
			}

		}
		if (m_bUp)
		{
			_vec3 vOut = m_pTransformCom->Lerp(_vec3{ m_matUI._41, m_matUI._42, 0.f }
			, _vec3{ m_matUI._41, m_matUI._42 + fReach, 0.f }, 0.3f, fTimeDelta, LERP_MODE::SMOOTHSTEP);
			if (vOut.x != -99)
			{
				m_matUI._42 = vOut.y;
			}
			else
			{
				m_bDown = true;
				m_bUp = false;
			}
		}
	}


	return iExit;
}

void CQuest_DialogUI::LateUpdate_Object()
{
	if (m_bEnd && m_fAlphaFont <= 0)
		m_bDead = true;

	if (m_fAlphaFont >= 200)
		m_bEnd = true;

	

	__super::LateUpdate_Object();
}

void CQuest_DialogUI::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fAlpha, 255, 255, 255));

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_UImatWorld);
	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();

	if (m_bDialogType == DIALOG_TYPE::DIALOG_NORMAL)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matUI);
		m_pUITextureCom->Render_Texture(1);
		m_pBufferCom->Render_Buffer();
	}

	if (m_bDialogType == DIALOG_TYPE::DIALOG_NORMAL)
	{
		CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strDialog.c_str(), -1,
			&m_rcText, DT_CENTER, D3DCOLOR_ARGB((_uint)m_fAlphaFont, 0, 0, 0));
	}



	// 텍스트박스 테스트렉트
	/*HDC hDC = GetDC(g_hWnd);
	Rectangle(hDC, m_rcText.left, m_rcText.top, m_rcText.right, m_rcText.bottom);*/

	__super::Render_Object();
}

HRESULT CQuest_DialogUI::Add_Component()
{

	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_QuestBox", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_UI_ScrollArrow", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pUITransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);


	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);


	return S_OK;
}

HRESULT CQuest_DialogUI::Ready_Dialog(wstring strDialog, DIALOG_TYPE _bDialogType)
{
	if (0 >= strDialog.size())
		return E_FAIL;

	m_bEnd = false;
	m_bDead = false;


	m_strDialog = strDialog;
	m_bDialogType = _bDialogType;
	m_fAcc = 0.f;
	m_iTextCnt = 0.f;

	// 들어간 다이얼로그 길이에 따라 텍스트박스크기 변경
	CGraphicDev::GetInstance()->Get_InGameFont()->DrawTextW(NULL, m_strDialog.c_str(), -1,
		&m_rcText, DT_CENTER | DT_CALCRECT, D3DCOLOR_ARGB(200, 0, 0, 0));

	// 변경된 크기를 가지고 스피치박스 재설정
	_int textWidth = m_rcText.right - m_rcText.left;
	_int textHeight = m_rcText.bottom - m_rcText.top;

	m_fSizeY = _float(textHeight);
	m_fPosY = (_float(m_rcText.top) + _float(m_rcText.bottom)) / 2.f;

	m_UImatWorld._42 = WINCY - m_fPosY - 15;
	m_UImatWorld._22 = m_fSizeY + 20;

	// 텍스트 박스 Y값 사이즈 러프세팅 
	m_tSizeUpLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeUpLerpY.Set_Lerp(0.3f, 0.f, m_UImatWorld._22);

	m_tSizeDownLerpY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tSizeDownLerpY.Set_Lerp(0.3f, m_UImatWorld._22, 0.f);


	// 이에따라 화살표 설정
	m_matUI._41 = m_UImatWorld._41 + 280;
	m_matUI._42 = (m_UImatWorld._42 - (m_UImatWorld._22 / 2.f) + 15);
	m_matUI._11 = 20.8f;
	m_matUI._22 = 12.4f;
	m_bDown = true;
	m_bUp = false;

	m_fAlphaFont = 0;
	m_tAlphaFont.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tAlphaFont.Set_Lerp(2.f, 0, 200);


	return S_OK;
}

void CQuest_DialogUI::End_Dialog()
{
	m_tAlphaFont.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tAlphaFont.Set_Lerp(2.f, m_fAlphaFont, 0);
}

_bool CQuest_DialogUI::EndLerp_Dialog()
{
	m_bDialogType = DIALOG_TYPE::DIALOG_END;

	m_tSizeDownLerpX.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tSizeDownLerpY.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
	m_tAlphaDownLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

	m_UImatWorld._11 = m_tSizeDownLerpX.fCurValue;
	m_UImatWorld._22 = m_tSizeDownLerpY.fCurValue;
	m_fAlpha = m_tAlphaDownLerp.fCurValue;

	if (!m_tSizeDownLerpX.bActive && !m_tSizeDownLerpY.bActive)
	{
		return true;
	}

	return false;
}



void CQuest_DialogUI::Typing_Effect(const _float& fTimeDelta)
{
	if (m_strDialog.length() <= m_iTextCnt)
	{
		m_bEnd = true;
		return;
	}


	m_fAcc += fTimeDelta;

	if (0.04f < m_fAcc)
	{
		if (m_iTextCnt % 3 == 0 && m_strDialog.length() - 4 >= m_iTextCnt)
			CSoundMgr::GetInstance()->PlaySoundW(L"dialogue.wav", CHANNEL_ID::UI_3, VOLUME_PLAYER_UI);

		m_strTyping += m_strDialog[m_iTextCnt];
		m_iTextCnt++;

		m_fAcc = m_fAcc - 0.04f;
	}
}

CQuest_DialogUI* CQuest_DialogUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring strDialog, DIALOG_TYPE _bDialogType)
{
	CQuest_DialogUI* pInstance = new CQuest_DialogUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Quest_DialogUI Create Failed");
		return nullptr;
	}
	if (FAILED(pInstance->Ready_Dialog(strDialog, _bDialogType)))
	{
		Safe_Release(pInstance);

		MSG_BOX("Quest_DialogUI Create Failed");
		return nullptr;
	}


	return pInstance;
}

void CQuest_DialogUI::Free()
{
	__super::Free();

}
