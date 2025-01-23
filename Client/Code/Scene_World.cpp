#include "stdafx.h"
#include "..\Header\Scene_World.h"

#include "Export_Function.h"

#include "Transform.h"
// 1차 추가 환경
#include "TwinPeaks.h"
#include "DeathTree.h"
#include "TripleDeathTree.h"
#include "WorldTree.h"
#include "Grass1.h"
#include "Tombstone.h"
#include "PirateHideOut.h"
#include "Sweets1.h"
#include "Sweets2.h"

// 2차 추가 환경
// 
// Sign
#include "NoticeBoard.h"
#include "SignAstropaw.h"
#include "SignCattrap.h"
#include "SignFlame.h"
#include "SignFreeze.h"
#include "SignHeal.h"
#include "SignLight.h"
#include "SignPurrserk.h"
#include "SignStop.h"
#include "SignTwinTown.h"
#include "SignFish.h"
#include "SignWoodFish.h"
// Skull
#include "DragonSkull1.h" 
#include "DragonSkull2.h" 
#include "DragonSkull3.h" 
// Wreck
#include "WreckShip.h"
#include "WreckPiece1.h"
#include "WreckPiece2.h"
#include "WreckPiece3.h"
#include "WreckPiece4.h"
// Wall
#include "Wall1.h"
#include "Wall2.h"
// BigBush
#include "LargeIceBush.h"
#include "VLargeIceBush.h"

/////////
// Environment
#include "Terrain.h"
#include "TerrainWorld.h"
#include "Bush.h"
#include "Mountain.h"
#include "Dungeon.h"
// 빌딩
#include "House1.h"
#include "House2.h"
#include "House3.h"
#include "House4.h"
#include "House5.h"
#include "House6.h"
#include "KingHouse.h"
#include "Smithy.h"
#include "MagicShop.h"
// 부쉬
#include "Bush1.h"
#include "Bush2.h"
#include "Bush3.h"
#include "Bush4.h"
#include "Bush5.h"
#include "Bush6.h"
#include "Bush7.h"
#include "Bush8.h"
#include "Bush9.h"
#include "Bush10.h"
#include "Bush11.h"
// 산
#include "Mountain_Grass.h"
#include "Mountain_Ice.h"
// 돌
#include "Rock1.h"
#include "Rock2.h"
#include "Rock3.h"
#include "Rock4.h"
// 기둥
#include "Rock_Pillar1.h"
#include "Rock_Pillar2.h"
#include "Rock_Pillar3.h"
#include "Ice_Pillar1.h"
#include "Temple_Pillar1.h"
#include "Temple_Pillar2.h"
// 던전
#include "Dungeon_Grass.h"
#include "Dungeon_Ice.h"
#include "Dungeon_Temple.h"
// 타워
#include "Tower1.h"
#include "Tower2.h"
#include "Tower3.h"
// 상자
#include "Chest_Cosmetic.h"
#include "Chest_Gold.h"
#include "Chest_Regular.h"

#include "Player.h"
#include "Player_Camera.h"
#include "Tool_Camera.h"
#include "EventMgr.h"
// UI
#include "LevelUI.h"
#include "TabUI.h"
#include "RingUI.h"
#include "ZoomUI.h"
#include "HpUI.h"
#include "ManaUI.h"
#include "DefUI.h"
#include "IndicatorUI.h"
#include "FieldSkillUI.h"
#include "DialogUI.h"
#include "Inventory.h"
#include "FlightUI.h"
#include "DungeonTextUI.h"
#include "QuestUI.h"
#include "Quest_DialogUI.h"

// NPC
#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"

// Monster
#include "ExpUI.h"
#include "EnterUI.h"
#include "CuteMonster.h"
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"
#include "Dragon.h"
#include "Ram.h"
#include "Fox.h"
#include "Wyvern.h"
#include "Squirrel.h"
#include "WyvernRed.h"
#include "Test_Mob.h"
#include "Serpent.h"
#include "Fish.h"
#include "VioletDragon.h"

// Effect
//#include "Cloud1.h"
//#include "Cloud2.h"
//#include "Cloud3.h"

#include "Effect_Cast_Blue.h"
#include "Effect_Cast_Yellow.h"
#include "Effect_Cast_Purple.h"

#include "Effect_SpellBurst_Blue.h"
#include "Effect_SpellBurst_Purple.h"
#include "Effect_SpellBurst_Yellow.h"

#include "Effect_FlyLighting.h"

#include "Effect_Range_Quater.h"

// Item
#include "GoldCoin.h"
#include "ExpCoin.h"
#include "Key.h"
#include "WorldFlight.h"
#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"

// Generator
#include "EffectGenerator.h"

#include "ImGuiMgr.h"
#include "TalkMgr.h"
#include "QuestMgr.h"

#include "Scene_Dungeon_Swamp.h"

#include "FadeUI.h"
//Projectile
#include "FoxFire.h"
#include "Chase_Bullet.h"

#include "TerrainTool.h"

#include "BackgroundShade.h"

#include "MiniGameMgr_Jump.h"
#include "SoundMgr.h"
#include "Island_Village.h"


// 국기
#include "FlagOwner.h"
#include "MiniGameMgr_Bingo.h"

#include "BossSceneMgr.h"
#include "BossSceneTriggerObj.h"
#include "FogMgr.h"

CScene_World::CScene_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::WORLD)
	, m_bShowEnding(true)
{
}

CScene_World::~CScene_World()
{
}

HRESULT CScene_World::Ready_Scene()
{
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/
	FAILED_CHECK_RETURN(Ready_Layer_Camera(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_UI(),		E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Player(),	E_FAIL); // 퀘스트 매니저 Init 실행.
	FAILED_CHECK_RETURN(Ready_Layer_Effect(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Other(),	E_FAIL);

	FAILED_CHECK_RETURN(Ready_Load(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_KSH(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_KJM(),	E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_LHJ(),	E_FAIL);

	if (!CMiniGameMgr_Jump::GetInstance()->Is_Init()) CMiniGameMgr_Jump::GetInstance()->Init(m_pGraphicDev);

	FAILED_CHECK_RETURN(Ready_Layer_YC(),	E_FAIL); // 아일랜드 생성

	if (!CTalkMgr::GetInstance()->Get_IsInit()) CTalkMgr::GetInstance()->Init(); 
	if (!CBossSceneMgr::GetInstance()->Is_Ready()) CBossSceneMgr::GetInstance()->Ready_BossSceneMgr(m_pGraphicDev);
	//if (!CFogMgr::GetInstance()->Is_Ready_FogMgr()) CFogMgr::GetInstance()->Ready_FogMgr(m_pGraphicDev);
	m_bEndingFade = FALSE;
	m_bFinish = FALSE;
	m_fAcc = 0.f;

	//SetupVertexFog(D3DCOLOR_ARGB(40, 255, 255, 255), D3DFOG_LINEAR, TRUE, 0.5f);

	ZeroMemory(&m_tLerpVideoVolume, sizeof(LERP_FLOAT_INFO));

	return S_OK;
}

Engine::_int CScene_World::Update_Scene(const _float& fTimeDelta)
{

	// Ending
	if (m_bFinish)
	{
		m_fAcc += fTimeDelta;

		if (3.f <= m_fAcc)
		{
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_EXIT_INGAME);
			CPlayer_Camera* pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
			if (nullptr != pCam)
			{
				pCam->Get_FadeUI()->Start_Fade(4.5f, 0.f, 255.f, TRUE, LERP_MODE::EASE_OUT, FALSE);

				CPlayer* pPlayer = static_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());
				pPlayer->Block_Input(TRUE);
			}
			CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EASE_IN, 4.5f, SOUND_VOLUME_BGM, 0.f);
			m_bFinish = FALSE;
			m_bEndingFade = TRUE;
		}
	}
	if (m_bEndingFade) 
	{
		if (!CCameraMgr::GetInstance()->Is_Fade())
		{
			CFadeUI* pUI = static_cast<CFadeUI*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"FadeUI"));
			pUI->Set_Alpha(255.f);

			// 게임 종료 - 페이드 완료

			if (!CManagement::GetInstance()->Is_Start_EndingVideo())
			{
				CManagement::GetInstance()->Set_Start_EndingVideo();


				// 동영상 
				m_hVideo = MCIWndCreate(g_hWnd,			// 부모 윈도우 핸들
					nullptr,		// mci 윈도우를 사용하는 인스턴스 핸들
					WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // WS_CHILD : 자식 창, WS_VISIBLE : 그 즉시 화면에 시연, MCIWNDF_NOPLAYBAR : 플레이 바를 생성하지 않음
					L"../Bin/Resource/Video/ending.wmv");	// 재생할 파일의 경로

												//MoveWindow : 동영상을 재생할 크기를 설정
				MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

				MCIWndPlay(m_hVideo);

				// 백버퍼 생성
				if (FAILED(m_pGraphicDev->CreateRenderTarget(WINCX, WINCY, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pBackBuffer, nullptr)))
					return E_FAIL;

				m_bShowEnding = false;

				const _float fTime = 1.5f;

				// 볼륨 보간
				m_tLerpVideoVolume.Init_Lerp(LERP_MODE::EASE_IN);
				m_tLerpVideoVolume.Set_Lerp(fTime, 0.f, 1000);
			}

			m_tLerpVideoVolume.Update_Lerp(fTimeDelta);
			MCIWndSetVolume(m_hVideo, m_tLerpVideoVolume.fCurValue);
		}
	}


	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	CSoundMgr::GetInstance()->Update(fTimeDelta);
	CBossSceneMgr::GetInstance()->Update_BossSceneMgr(fTimeDelta);
	//CFogMgr::GetInstance()->Update_FogMgr(fTimeDelta);

	if (!m_bStartFade)
	{
		if (!CManagement::GetInstance()->Is_Enter_InGame())
		{
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_ENTER_INGAME);
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::ENTER_WORLD);
			CManagement::GetInstance()->Set_Enter_InGame(TRUE);
		}
		else
		{
			CGameObject* pPlayer = CManagement::GetInstance()->Get_Player();
			if (nullptr != pPlayer)
			{
				_vec3 vPos{};
				
				if (SCENE_TYPE::DUNGEON_SWAMP == CManagement::GetInstance()->Get_PrevSceneType())
				{
					vPos = { WORLD_DUNGEON_ENTERANCE_X, pPlayer->Get_Transform()->Get_Info(INFO_POS).y, WORLD_DUNGEON_ENTERANCE_Z };
				}
				else if (SCENE_TYPE::DUNGEON_TEMPLE == CManagement::GetInstance()->Get_PrevSceneType())
				{
					vPos = { WORLD_TEMPLE_ENTERANCE_X, pPlayer->Get_Transform()->Get_Info(INFO_POS).y, WORLD_TEMPLE_ENTERANCE_Z };
				/*	CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_FOV(CAM_FOV_DEFAULT);
					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_Distance(CAM_DISTANCE_DEFAULT);
					CCameraMgr::GetInstance()->Set_Projection();*/
					CSoundMgr::GetInstance()->ChangeBGM(L"catquest_overworld_theme.wav", BGM_TYPE::ISLAND_VILLAGE);

				}

				pPlayer->Get_Transform()->Set_Pos(vPos);
			}

			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::SCENE_ENTER_FIELD);
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_IN);

			//CFogMgr::GetInstance()->Start_Lerp_Near(2.5f, 100, 40, LERP_MODE::EASE_IN);
			//CFogMgr::GetInstance()->Start_Lerp_Far(2.5f, 190, 130, LERP_MODE::EASE_IN);
		}
		m_bStartFade = TRUE;
	}

	__super::Update_Scene(fTimeDelta);

	CQuestMgr::GetInstance()->Update(m_pGraphicDev); // 퀘스트 매니저 업데이트

	CMiniGameMgr_Jump::GetInstance()->Update(fTimeDelta);

	return 0;
}

void CScene_World::LateUpdate_Scene()
{
	
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	// 00. 1차 충돌 처리
	
	// Rect vs Rect
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENVIRONMENT);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::NPC);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::MONSTER, OBJ_TYPE::PROJECTILE);
	CCollisionMgr::GetInstance()->Check_Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE); // 두 매개변수 순서 변경


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

void CScene_World::Render_Scene()
{
	if (!CManagement::GetInstance()->Is_Debug()) return;
#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject*	pObj = nullptr;
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

void CScene_World::Free()
{
	CIsland* pVillage = dynamic_cast<CIsland_Village*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::ISLAND, L"Island_Village"));
	
	if (nullptr != pVillage)
		pVillage->Change_Scene();

	__super::Free();
}

CScene_World* CScene_World::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_World*	pInstance = new CScene_World(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Scene_World Create Failed");
		return nullptr;
	}

	return pInstance;
}


HRESULT CScene_World::Ready_Load()
{
	TCHAR szLoadPath[MAX_STR] = L"../Bin/Data/Level/Level_World.dat";
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetDevice(m_pGraphicDev), E_FAIL);
	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->Load_Scene(szLoadPath), E_FAIL);
}

void CScene_World::Finish_Game()
{
	m_bFinish = TRUE;
}

HRESULT CScene_World::Ready_Layer_Camera()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

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


HRESULT CScene_World::Ready_Layer_UI()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::UI, pLayer });

	Engine::CGameObject*		pGameObject = nullptr;

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

HRESULT CScene_World::Ready_Layer_Player()
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::PLAYER, pLayer });

	Engine::CGameObject* pGameObject = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");

	if (nullptr == pGameObject)
	{
		// Player
		pGameObject = CPlayer::Create(m_pGraphicDev);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Player", pGameObject), E_FAIL);
	
		if (!CQuestMgr::GetInstance()->Get_IsInit()) 
			CQuestMgr::GetInstance()->Init(m_pGraphicDev, pGameObject); // 퀘스트 매니저 초기화
	}
	else
	{
		pGameObject->Get_Transform()->Set_Pos(_vec3{ _float(START_POS_WORLD_X)
			, pGameObject->Get_Transform()->Get_Scale().y
			, _float(START_POS_WORLD_Z) });
	}
	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Effect()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::EFFECT, pLayer });

	// Cloud
	/*pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_1", pGameObject), E_FAIL);

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_1", pGameObject), E_FAIL);

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_1", pGameObject), E_FAIL);*/


	/*pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_2", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 190.f, 12.f, 172.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_3", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 200.f, 12.f, 212.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_4", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 150.f, 10.f, 170.f });

	pGameObject = CCloud1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud1_5", pGameObject), E_FAIL);

	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 140.f, 11.f, 210.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 110.f, 12.f, 140.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_3", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 220.f, 12.f, 140.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_4", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 225.f, 12.f, 250.f });

	pGameObject = CCloud3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud3_5", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 245.f, 12.f, 230.f });

	pGameObject = CCloud2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cloud2_2", pGameObject), E_FAIL);
	dynamic_cast<CTransform*>
		(pGameObject->Get_Component(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC))->
		Set_Pos({ 245.f, 12.f, 170.f });*/

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_Other()
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



HRESULT CScene_World::Ready_Layer_KSH()
{
	Engine::CGameObject* pGameObject = nullptr;

	//// 2차 추가본
	//pGameObject = CNoticeBoard::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//// 표지판
	//pGameObject = CSignAstropaw::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	//
	//pGameObject = CSignCattrap::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignFlame::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignFreeze::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignHeal::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignLight::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignPurrserk::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignStop::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignTwinTown::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignFish::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CSignWoodFish::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//// 뼈
	//pGameObject = CDragonSkull1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CDragonSkull2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	//
	//pGameObject = CDragonSkull3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//// 난파선 조각
	//pGameObject = CWreckShip::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CWreckPiece1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CWreckPiece2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CWreckPiece3::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CWreckPiece4::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//// WALL
	//pGameObject = CWall1::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	//pGameObject = CWall2::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// rock
	/*pGameObject = CRock1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CRock2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CRock3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CRock4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);*/

	//// 사자
	//pGameObject = CNpc_King::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 열쇠
	//pGameObject = CKey::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 퀘스트 아이템 - 월드 플라이
	// pGameObject = CWorldFlight::Create(m_pGraphicDev);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CLargeIceBush::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CVLargeIceBush::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 국기
	// pGameObject = CFlagOwner::Create(m_pGraphicDev, OBJ_ID::FLAG_OWNER);
	// NULL_CHECK_RETURN(pGameObject, E_FAIL);
	// FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_World::Ready_Layer_KJM()
{
	Engine::CGameObject* pGameObject = nullptr;


	//// Test Boss
	//pGameObject = CVioletDragon::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Boss Test VioletDragon", pGameObject), E_FAIL);





	return S_OK;
}

HRESULT CScene_World::Ready_Layer_LHJ()
{
	Engine::CGameObject* pGameObject = nullptr;

	pGameObject = CTerrainTool::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Terrain_Tool", pGameObject), E_FAIL);

	//pGameObject = CDungeonTextUI::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Text_UI", pGameObject), E_FAIL);

	pGameObject = CEffectGenerator::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Generator", pGameObject), E_FAIL);

	

	
	return S_OK;
}

HRESULT CScene_World::Ready_Layer_YC()
{
	Engine::CGameObject* pGameObject = nullptr;
	
	CMiniGameMgr_Jump::GetInstance()->Create_Islands();

	/*_vec3 vStartPos{ START_POS_WORLD_X, 0.2f, START_POS_WORLD_Z };
	_vec3 vEndPos = vStartPos + _vec3{ 10.f , 0.2f, -10.f };

	pGameObject = CLineObject::Create(m_pGraphicDev, vStartPos, vEndPos);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_01", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, vEndPos, vEndPos + _vec3{ 10.f, 0.f, 0.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_02", pGameObject), E_FAIL);

	pGameObject = CLineObject::Create(m_pGraphicDev, vEndPos + _vec3{ 10.f, 0.f, 0.f }, vEndPos + _vec3{ 10.f, 0.f, -10.f });
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Line Obj_03", pGameObject), E_FAIL);*/


	/*pGameObject = CBackgroundShade::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);*/


	
	pGameObject = CBossSceneTriggerObj::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	return S_OK;
}

void CScene_World::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{
	//return;
	float Start = 40; // 50.f;   // Linear fog distances
	float End = 125; //  130.f;

	// Enable fog blending. d w ddda
	m_pGraphicDev->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	m_pGraphicDev->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (D3DFOG_LINEAR == Mode)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FOGTABLEMODE, Mode); // D3DRS_FOGVERTEXMODE
		m_pGraphicDev->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
		m_pGraphicDev->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
	}
	else
	{
		m_pGraphicDev->SetRenderState(D3DRS_FOGTABLEMODE, Mode); // D3DRS_FOGVERTEXMODE
		m_pGraphicDev->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
		//m_pGraphicDev->SetRenderState(D3DRS_FOGDENSITY, 0.66f);
	}

	// Enable range-based fog if desired (only supported for
	//   vertex fog).  For this example, it is assumed that UseRange
	//   is set to a nonzero value only if the driver exposes the 
	//   D3DPRASTERCAPS_FOGRANGE capability.
	// Note: This is slightly more performance intensive
	//   than non-range-based fog.
	if (UseRange)
		m_pGraphicDev->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}