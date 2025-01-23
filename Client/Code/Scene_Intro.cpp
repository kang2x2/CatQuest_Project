#include "stdafx.h"
#include "..\Header\Scene_Intro.h"

#include "Export_Function.h"

#include "LoadingThread.h"
#include "Scene_World.h"
#include "Scene_Tool.h"
#include "BackGround.h"
#include "SoundMgr.h"
#include "FadeUI.h"

extern _bool g_FinishLoading;

CScene_Intro::CScene_Intro(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::INTRO)
	, m_pLoading(nullptr)
	, m_pUI(nullptr)
{
}

CScene_Intro::~CScene_Intro()
{
}

HRESULT CScene_Intro::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);

	// ������Ʈ �� �ؽ�ó �ε� ������ ����
	m_pLoading = CLoadingThread::Create(m_pGraphicDev, LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE);

	NULL_CHECK_RETURN(m_pLoading, E_FAIL);

	CSoundMgr::GetInstance()->Initialize();

	// ������ 
	m_hVideo = MCIWndCreate(g_hWnd,			// �θ� ������ �ڵ�
		nullptr,		// mci �����츦 ����ϴ� �ν��Ͻ� �ڵ�
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : �ڽ� â, WS_VISIBLE : �� ��� ȭ�鿡 �ÿ�, MCIWNDF_NOPLAYBAR : �÷��� �ٸ� �������� ����
		L"../Bin/Resource/Video/intro.wmv");	// ����� ������ ���

									//MoveWindow : �������� ����� ũ�⸦ ����
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);

	ZeroMemory(&m_tLerpVideoVolume, sizeof(LERP_FLOAT_INFO));


	// ����� ����
	if (FAILED(m_pGraphicDev->CreateRenderTarget(WINCX, WINCY, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pBackBuffer, nullptr)))
		return E_FAIL;

	

	return S_OK;
}

Engine::_int CScene_Intro::Update_Scene(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Scene(fTimeDelta);

	g_FinishLoading = m_pLoading->Get_Finish();

	if (TRUE == m_pLoading->Get_Finish()) // �ε� ����
	{
		CScene* pScene = nullptr;

		if (!m_tLerpVideoVolume.bActive)
		{
			const _float fTime = 1.5f;

			// ���� ����
			m_tLerpVideoVolume.Init_Lerp(LERP_MODE::EASE_IN);
			m_tLerpVideoVolume.Set_Lerp(fTime, 1000, 0.f);

			// ���̵� ����

		/*	Engine::CLayer* pLayer = Engine::CLayer::Create();
			NULL_CHECK_RETURN(pLayer, E_FAIL);
			m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

			m_pUI = CFadeUI::Create(m_pGraphicDev);
			CEventMgr::GetInstance()->Add_Obj(m_pUI->Get_Name(), m_pUI);

			m_pUI->Start_Fade(fTime, 0.f, 255.f, FALSE, LERP_MODE::EASE_IN, FALSE);
			m_pUI->Set_Maintain(FALSE);*/
		}

		m_tLerpVideoVolume.Update_Lerp(fTimeDelta);

		if (m_tLerpVideoVolume.fCurValue <= 0)
		{
			MCIWndSetVolume(m_hVideo, m_tLerpVideoVolume.fCurValue);
			if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
			{
				pScene = CScene_World::Create(m_pGraphicDev); // MCIWndSetVolume
				CEventMgr::GetInstance()->Change_Scene(pScene);
			}
			else if ((PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode()))
			{
				pScene = CScene_Tool::Create(m_pGraphicDev);
				FAILED_CHECK_RETURN(Engine::Set_Scene(pScene), E_FAIL);
			}
		}
		else
		{
			MCIWndSetVolume(m_hVideo, m_tLerpVideoVolume.fCurValue);
		}

		NULL_CHECK_RETURN(pScene, -1);
	}

	return iExit;
}

void CScene_Intro::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CScene_Intro::Render_Scene()
{
#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject* pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion

	if (true == m_pLoading->Get_Finish())
		swprintf_s(szBuf, L"�ε� �Ϸ�! �����̽��� �Է�!.                                                                                    .");
	else
		swprintf_s(szBuf, L"�ε� ��...                                                                 .");

	SCREEN_MSG(szBuf, rc);
}

void CScene_Intro::Free()
{
	Safe_Release(m_pLoading);
	MCIWndClose(m_hVideo);
	m_pBackBuffer->AddRef();
	Safe_Release(m_pBackBuffer); // ����� ����
	__super::Free();
}

CScene_Intro* CScene_Intro::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Intro* pInstance = new CScene_Intro(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Logo Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CScene_Intro::Ready_Prototype()
{
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, CRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Background_Black"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Logo/black.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Background_White"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Logo/white.png")), E_FAIL);

	return S_OK;
}

HRESULT CScene_Intro::Ready_Layer_Environment()
{
	return S_OK;
}

