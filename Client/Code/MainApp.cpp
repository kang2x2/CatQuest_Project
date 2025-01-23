#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Engine_Define.h"
#include "Export_Function.h"
#include "Scene_Intro.h"
#include "Scene_Tool.h"

#include "EventMgr.h"
#include "QuestMgr.h"
#include "TalkMgr.h"
#include "MiniGameMgr_Jump.h"
#include "MiniGameMgr_Bingo.h"

#include "ImGuiMgr.h"
#include "Calculator.h"
#include "SoundMgr.h"
#include "FogMgr.h"

#include "Scene_Intro.h"
#include "Scene_Tool.h"
#include "Scene_World.h"
#include "Scene_Dungeon_Swamp.h"

extern _bool g_FinishLoading;


CMainApp::CMainApp() : m_pDeviceClass(nullptr), m_pManagementClass(nullptr)
{
	
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL); // 디바이스 초기화

	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL); // 시작 Scene, 매니지먼트 생성
		
	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	Engine::Update_InputDev();	 // 인풋 디바이스 업데이트

	CSoundMgr::GetInstance()->Update(fTimeDelta);

	if (CInputDev::GetInstance()->Key_Down('P'))
	{
		m_pManagementClass->Set_Debug_Toggle();
	}

	NULL_CHECK_RETURN(m_pManagementClass, -1); 
 	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	NULL_CHECK(m_pManagementClass);
	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	if ((CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::INTRO) || // && !g_FinishLoading)|| // 순수 동영상 재생
		CManagement::GetInstance()->Is_Start_EndingVideo())
	{
		CEventMgr::GetInstance()->Update_Event();
		return;
	}
	//else if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::INTRO && g_FinishLoading) // 동영상 재생 + 알파 페이드 올리기
	//{
	//	CGraphicDev::GetInstance()->Get_GraphicDev()->BeginScene();
	//	NULL_CHECK(m_pManagementClass);

	//	m_pManagementClass->Render_Scene(m_pGraphicDev); // 렌더러 호출
	//	CGraphicDev::GetInstance()->Get_GraphicDev()->Present(nullptr, nullptr, nullptr, nullptr);
	//	CEventMgr::GetInstance()->Update_Event();
	//	//CGraphicDev::GetInstance()->Get_GraphicDev()->EndScene();

	//	return;

	//}

	D3DXCOLOR tBackColor;

	_float r = 255.f, g = 255.f, b = 255.f;

	if (SCENE_TYPE::INTRO == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		r = 255.f;
		g = 255.f;
		b = 255.f;
	}
	else if (SCENE_TYPE::WORLD == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		r = 101.f; 
		g = 202.f; 
		b = 173.f;
	}
	else if (SCENE_TYPE::DUNGEON_SWAMP == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		r = 11.f;
		g = 41.f;
		b = 37.f;
	}
	else if (SCENE_TYPE::DUNGEON_TEMPLE == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		r = 0.f;
		g = 0.f;
		b = 0.f;
	}
	else if (SCENE_TYPE::TOOL == CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		r = 125.f;
		g = 125.f;
		b = 125.f;
	}
	tBackColor = { r / 255.f, g / 255.f, b / 255.f, 1.f };

	Engine::Render_Begin(tBackColor);

	NULL_CHECK(m_pManagementClass);
	
	m_pManagementClass->Render_Scene(m_pGraphicDev);

	Engine::Render_End();

	CEventMgr::GetInstance()->Update_Event(); 
}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL); // 디바이스 초기화
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	// 인풋 디바이스 초기화
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL); // 인풋 디바이스 초기화


	// 후면 추려내기 비활성화
	(*ppGraphicDev)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 텍스처 불투명화 설정코드
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	// 텍스처 색상 설정코드
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); 
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	// 텍스처 보간 (카메라 거리에 따른 색깔 보정) 
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// 조명 활성화
	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, TRUE); 

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagementClass)
{
	// 인트로씬 생성
	Engine::CScene* pScene = CScene_Intro::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	// 매니지먼트 생성
	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagementClass), E_FAIL);
	(*ppManagementClass)->AddRef();

	FAILED_CHECK_RETURN((*ppManagementClass)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}


CMainApp * CMainApp::Create()
{
	CMainApp *	pInstance = new	CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}
	
	return pInstance;
}

void CMainApp::Free()
{
	CManagement::GetInstance()->Get_CurScene()->Release_MaintainObj();
	CTalkMgr::DestroyInstance(); // 임시로 여기서 지움.
	CQuestMgr::DestroyInstance(); // 임시로 여기서 지움.
	CImGuiMgr::GetInstance()->DestroyInstance();
	CMiniGameMgr_Jump::GetInstance()->DestroyInstance();
	CSoundMgr::GetInstance()->DestroyInstance();
	CFogMgr::GetInstance()->DestroyInstance();

	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pManagementClass);

	Engine::Release_Utility();
	Engine::Release_System();
}
