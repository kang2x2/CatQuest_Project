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
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL); // ����̽� �ʱ�ȭ

	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL); // ���� Scene, �Ŵ�����Ʈ ����
		
	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	Engine::Update_InputDev();	 // ��ǲ ����̽� ������Ʈ

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
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	NULL_CHECK(m_pManagementClass);
	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	if ((CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::INTRO) || // && !g_FinishLoading)|| // ���� ������ ���
		CManagement::GetInstance()->Is_Start_EndingVideo())
	{
		CEventMgr::GetInstance()->Update_Event();
		return;
	}
	//else if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::INTRO && g_FinishLoading) // ������ ��� + ���� ���̵� �ø���
	//{
	//	CGraphicDev::GetInstance()->Get_GraphicDev()->BeginScene();
	//	NULL_CHECK(m_pManagementClass);

	//	m_pManagementClass->Render_Scene(m_pGraphicDev); // ������ ȣ��
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
	/*--------------------- ! �����̳� �߰��� �ݵ�� ���� ���� !  ---------------------*/

	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass), E_FAIL); // ����̽� �ʱ�ȭ
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();

	// ��ǲ ����̽� �ʱ�ȭ
	FAILED_CHECK_RETURN(Engine::Ready_InputDev(g_hInst, g_hWnd), E_FAIL); // ��ǲ ����̽� �ʱ�ȭ


	// �ĸ� �߷����� ��Ȱ��ȭ
	(*ppGraphicDev)->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �ؽ�ó ������ȭ �����ڵ�
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);

	// �ؽ�ó ���� �����ڵ�
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); 
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	(*ppGraphicDev)->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	// �ؽ�ó ���� (ī�޶� �Ÿ��� ���� ���� ����) 
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// ���� Ȱ��ȭ
	(*ppGraphicDev)->SetRenderState(D3DRS_LIGHTING, TRUE); 

	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagementClass)
{
	// ��Ʈ�ξ� ����
	Engine::CScene* pScene = CScene_Intro::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	// �Ŵ�����Ʈ ����
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
	CTalkMgr::DestroyInstance(); // �ӽ÷� ���⼭ ����.
	CQuestMgr::DestroyInstance(); // �ӽ÷� ���⼭ ����.
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
