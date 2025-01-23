#include "stdafx.h"
#include "..\Header\Scene_Dungeon_Temple.h"

#include "Export_Function.h"
#include "Player_Camera.h"
#include "LevelUI.h"
#include "TabUI.h"
#include "ZoomUI.h"
#include "ExpUI.h"
#include "HpUI.h"
#include "DefUI.h"
#include "ManaUI.h"
#include "EnterUI.h"
#include "IndicatorUI.h"
#include "FieldSkillUI.h"
#include "QuestUI.h"
#include "Player.h"
#include "ImGuiMgr.h"
#include "QuestMgr.h"
#include "DungeonTextUI.h"
#include "EffectGenerator.h"

#include "Zeolite.h"
#include "BingoChest.h"
#include "TrapBigFist.h"

CScene_Dungeon_Temple::CScene_Dungeon_Temple(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::DUNGEON_TEMPLE)
{
}

CScene_Dungeon_Temple::~CScene_Dungeon_Temple()
{
}

HRESULT CScene_Dungeon_Temple::Ready_Scene()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/


// OBJ_TYPE별로 선언 필요
	FAILED_CHECK_RETURN(Ready_Layer_Camera(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Effect(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Other(), E_FAIL);
	// 툴 데이터 파싱
	FAILED_CHECK_RETURN(Ready_Load(), E_FAIL);

	// 개인 작업
	FAILED_CHECK_RETURN(Ready_Layer_KSH(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_KJM(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_LHJ(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_YC(), E_FAIL);

	// CTalkMgr::GetInstance()->Init(); // 토크 매니저 초기화

	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_kitcat_theme.wav", BGM_TYPE::ISLAND_TEMPLE);

	return S_OK;
}

Engine::_int CScene_Dungeon_Temple::Update_Scene(const _float& fTimeDelta)
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	if (!m_bStartFade)
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_ENTER_FIELD);
		CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_IN);
		m_bStartFade = TRUE;
	}

	__super::Update_Scene(fTimeDelta);

	CQuestMgr::GetInstance()->Update(m_pGraphicDev); // 퀘스트 매니저 업데이트

	return 0;
}

void CScene_Dungeon_Temple::LateUpdate_Scene()
{
	// 00. 1차 충돌 처리

	// Rect vs Rect
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::PROJECTILE);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PROJECTILE, OBJ_TYPE::PLAYER);


	// Rect vs Line
	CCollisionMgr::GetInstance()->Check_Line_Collision(OBJ_TYPE::PLAYER);

	// Position vs Sphere 
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::MONSTER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::FLAG, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::PLAYER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::SKILL, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::SKILL, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::TRIGGER, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능


	// Player vs Island
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::RANGE_OBJ, OBJ_TYPE::ISLAND, COL_TYPE::RECT, COL_TYPE::SPHERE); // TODO::최적화 가능



	// 01. 레이트 업데이트 -> 2차 충돌 처리
	__super::LateUpdate_Scene();

	// 02. 카메라 포지션 결정
	CCameraMgr::GetInstance()->Set_ViewSpace();

}
void CScene_Dungeon_Temple::Render_Scene()
{
	if (!CManagement::GetInstance()->Is_Debug()) return;
#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject* pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion
	swprintf_s(szBuf, L"%.d FPS", _int(1.f / Engine::Get_TimeDelta(L"Timer_FPS65")));
	SCREEN_MSG(szBuf, rc);

	pObj = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	NULL_CHECK(pObj);
	vPos = pObj->Get_Transform()->Get_Info(INFO_POS);
	swprintf_s(szBuf, L"PLAYER : %.3f,  %.3f,  %.3f", vPos.x, vPos.y, vPos.z);
	SCREEN_MSG(szBuf, rc);

	NULL_CHECK(CCameraMgr::GetInstance()->Get_CurCamera());
	vPos = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewSpace().Eye;
	swprintf_s(szBuf, L"CAMERA : %.3f,  %.3f,  %.3f", vPos.x, vPos.y, vPos.z);
	SCREEN_MSG(szBuf, rc);

	swprintf_s(szBuf, L"C : 속도 증가 \tV : 원래 속도 \tJ : 풀 체력 \t K : 풀 마나");
	SCREEN_MSG(szBuf, rc);
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_Camera()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Camera
	if (nullptr == CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::CAMERA, L"Player_Camera"))
	{
		pGameObject = CPlayer_Camera::Create(m_pGraphicDev);

		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player_Camera", pGameObject), E_FAIL);
		CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
		CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");
	}

	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_UI()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// UI - Level
	pGameObject = CLevelUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Level", pGameObject), E_FAIL);

	// UI - Tab
	pGameObject = CTabUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Tab", pGameObject), E_FAIL);

	// UI - Zoom
	pGameObject = CZoomUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Zoom", pGameObject), E_FAIL);

	//// UI - Exp
	pGameObject = CExpUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Exp", pGameObject), E_FAIL);

	// UI - Hp
	pGameObject = CHpUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Hp", pGameObject), E_FAIL);

	// UI - Def
	pGameObject = CDefUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Def", pGameObject), E_FAIL);

	// UI - Mana
	pGameObject = CManaUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Mana", pGameObject), E_FAIL);

	// UI - Enter
	pGameObject = CEnterUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Enter", pGameObject), E_FAIL);

	// UI - Indicator
	pGameObject = CIndicatorUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Indicator", pGameObject), E_FAIL);

	// UI - FieldSkill
	pGameObject = CFieldSkillUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_FieldSkill", pGameObject), E_FAIL);

	// UI - Inventroy
	// pGameObject = CInventory::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Inventory", pGameObject), E_FAIL);
	// pGameObject->Set_Maintain(true);

	// UI - Quest
	pGameObject = CQuestUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"UI_Quest", pGameObject), E_FAIL);

	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_Player()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PLAYER, pLayer });

	Engine::CGameObject* pGameObject = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");

	if (nullptr == pGameObject)
	{
		// Player
		pGameObject = CPlayer::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player", pGameObject), E_FAIL);
	}
	else
	{
		pGameObject->Get_Transform()->Set_Pos(_vec3{ _float(START_POS_TEMPLE_X)
			, pGameObject->Get_Transform()->Get_Scale().y
			, _float(START_POS_TEMPLE_Z) });
	}
	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_Effect()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::EFFECT, pLayer });
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_Other()
{
	Engine::CLayer* pLayer = nullptr;

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TERRAIN,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::RANGE_OBJ,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::LINE,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::SKILL,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::NPC,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER,		pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ITEM,			pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PROJECTILE,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ISLAND,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::GENERATOR,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::FLAG,	pLayer });

	pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TRIGGER,	pLayer });

	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Load()
{
	TCHAR szLoadPath[MAX_STR] = L"../Bin/Data/Level/Level_Temple.dat";
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetDevice(m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->Load_Scene(szLoadPath), E_FAIL);
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_KSH()
{
	Engine::CGameObject* pGameObject = nullptr;

	pGameObject = CZeolite::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CBingoChest::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_KJM()
{
	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_LHJ()
{
	Engine::CGameObject* pGameObject = nullptr;
	pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject), E_FAIL);

	pGameObject = CEffectGenerator::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Generator", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Dungeon_Temple::Ready_Layer_YC()
{
	return S_OK;
}

void CScene_Dungeon_Temple::Free()
{
	__super::Free();
}

CScene_Dungeon_Temple* CScene_Dungeon_Temple::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Dungeon_Temple* pInstance = new CScene_Dungeon_Temple(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene Dungeon Temple Create Failed");
		return nullptr;
	}

	return pInstance;
}



