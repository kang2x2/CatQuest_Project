#include "stdafx.h"
#include "..\Header\LoadingThread.h"
#include "Export_Function.h"

CLoadingThread::CLoadingThread(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bFinish(false)
{
	m_pGraphicDev->AddRef();
}


CLoadingThread::~CLoadingThread()
{

}

unsigned int CLoadingThread::Thread_Main(void * pArg)
{
	CLoadingThread*		pLoading = reinterpret_cast<CLoadingThread*>(pArg);

	_uint	iFlag = 0;

	EnterCriticalSection(pLoading->Get_Crt());

	switch (pLoading->Get_LoadingID())
	{
	case Engine::LOADING_THREAD_TYPE::COMPONENT_AND_TEXTURE:
	{
		iFlag = pLoading->Loading_For_ComponentAndTexture();
	}
		break;
	default:
		break;
	}

	LeaveCriticalSection(pLoading->Get_Crt());

	return iFlag;
}

HRESULT CLoadingThread::Ready_Loading(LOADING_THREAD_TYPE eLoadingID)
{
	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);

	m_eID = eLoadingID;

	return S_OK;
}

_uint CLoadingThread::Loading_For_ComponentAndTexture()
{
#pragma region Component

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::CAMERA,
		CCamera::Create(m_pGraphicDev, &g_hWnd)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::TRANSFORM,
		CTransform::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::STATEMACHINE,
		CStateMachine::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::ANIMATOR,
		CAnimator::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::AICOM,
		CAIComponent::Create(m_pGraphicDev)), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::RIGIDBODY,
		CRigidBody::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_TEX,
		CTerrainTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX,
		CTerrainRcTex::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_LINE,
		CLineCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_CIRCLE,
		CCircleCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_RECT,
		CRectCollider::Create(m_pGraphicDev)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Proto(COMPONENT_TYPE::COL_SPHERE,
		CSphereCollider::Create(m_pGraphicDev)), E_FAIL);


#pragma endregion


#pragma region Texture


#pragma region KANG

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Quest",
	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Quest/QuestBoard2.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_World",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_World.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_Dungeon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_Dungeon.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Terrain_Temple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain_Temple.png")), E_FAIL);

#pragma region Building

	// House
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House5",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_House6",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/town_6.png")), E_FAIL);

	// KingHouse
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_KingHouse_In",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/capital_city_interior.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_KingHouse_Out",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/House/capital_city.png")), E_FAIL);

	// Smithy
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Smithy",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/kit_cat_smithy.png")), E_FAIL);

	// Magic Shop
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_MagicShop",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/arcane_temples.png")), E_FAIL);

	// Wall
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wall1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/wall_01.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wall2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/wall_02.png")), E_FAIL);


#pragma endregion

#pragma region Bush

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush5",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush6",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_6.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush7",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_7.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush8",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_8.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush9",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_9.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush10",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_10.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bush11",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/forest_11.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Large_Ice_Bush",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/Big_Forest2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_VLarge_Ice_Bush",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/Big_Forest1.png")), E_FAIL);

	
	// Grass
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Grass1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Bush/grass_1.png")), E_FAIL);

	// Tombstone
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tombstone",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/tombstone.png")), E_FAIL);

	// PirateHideOut
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_PirateHideOut",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Building/pirate_hideout.png")), E_FAIL);

	// Sweets
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sweets1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/sweets_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sweets2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/sweets_2.png")), E_FAIL);


#pragma endregion

#pragma region Mountain

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Mountain_Grass",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Mountain/mountains_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Mountain_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Mountain/mountains_5.png")), E_FAIL);

#pragma endregion

#pragma region Pillar

	// Rock Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock_Pillar3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_3.png")), E_FAIL);

	// Temple Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Temple_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/ruinpillar_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Temple_Pillar2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/ruinpillar_2.png")), E_FAIL);

	// Ice Pillar
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Ice_Pillar1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/rockpillar_4.png")), E_FAIL);

	// TwinPeaks
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Pillar_TwinPeaks",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Pillar/twin_peaks.png")), E_FAIL);


#pragma endregion

#pragma region Tree

	// Death Tree
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_DeathTree",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tree/forest_12.png")), E_FAIL);
	// Triple Death Tree
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Triple_DeathTree",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tree/forest_11.png")), E_FAIL);
	// World Tree
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_World_Tree",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tree/world tree.png")), E_FAIL);


#pragma endregion

#pragma region Rock

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Rock4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Rock/rocks_4.png")), E_FAIL);

#pragma endregion

#pragma region Dungeon

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Grass",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dungeon_Temple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Dungeon/dungeon_3.png")), E_FAIL);
#pragma endregion

#pragma region Tower

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Tower3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Tower/Tower_3.png")), E_FAIL);

#pragma endregion

#pragma region Chest

	// 화장품 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Cosmetic_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_cosmetic.png")), E_FAIL);
	// 황금 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Gold_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_gold.png")), E_FAIL);
	// 기본 상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Regular_Chest",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Chest/chest_regular.png")), E_FAIL);

#pragma region Sign
	// 게시판
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_NoticeBoard",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/notice_board.png")), E_FAIL);
	// 표지판 - Astropaw
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Astropaw",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_astropaw.png")), E_FAIL);
	// 표지판 - Cattrap
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Cattrap",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_cattrap.png")), E_FAIL);
	// 표지판 - Flame
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Flame",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_flamepurr.png")), E_FAIL);
	// 표지판 - Freeze
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Freeze",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_freezepaw.png")), E_FAIL);
	// 표지판 - Heal
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Heal",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_healpaw.png")), E_FAIL);
	// 표지판 - Light
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Light",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_lightnyan.png")), E_FAIL);
	// 표지판 - Purrserk
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Purrserk",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/sign_purrserk.png")), E_FAIL);
	// 표지판 - Stop
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Stop",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/stop_sign.png")), E_FAIL);
	// 표지판 - TwinTown
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_TwinTown",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/town_twintowns.png")), E_FAIL);
	// 표지판 - Fish
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_Fish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/town_eastpawt.png")), E_FAIL);
	// 표지판 - WoodFish
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Sign_WoodFish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Sign/town_westpawt.png")), E_FAIL);
#pragma endregion

#pragma region Skull
	// 드래곤뼈 1
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skull_Dragon1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Skull/dragonskull_1.png")), E_FAIL);
	// 드래곤뼈 2
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skull_Dragon2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Skull/dragonskull_2.png")), E_FAIL);
	// 드래곤뼈 3
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skull_Dragon3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Skull/dragonskull_3.png")), E_FAIL);
#pragma endregion

#pragma region Wreck
	// 난파선 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wreck_Ship",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Wreck/shipwreck.png")), E_FAIL);
	// 난파선 조각1
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wreck_Piece1",
	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Wreck/wreck_1.png")), E_FAIL);
	// 난파선 조각2
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wreck_Piece2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Wreck/wreck_2.png")), E_FAIL);
	// 난파선 조각3
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wreck_Piece3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Wreck/wreck_3.png")), E_FAIL);
	// 난파선 조각4
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Wreck_Piece4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Wreck/wreck_4.png")), E_FAIL);
#pragma endregion

#pragma region 그 외 환경 오브젝트

	// 드라코 테이블
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Other_DrakothTable",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/Use/drakoth_table.png")), E_FAIL);

	// 포션
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Other_WorldPotion",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/Use/potion.png")), E_FAIL);

	// 선물상자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Other_Present",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/Use/present.png")), E_FAIL);

	// 종이
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Other_Paper",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/Use/scrap_paper.png")), E_FAIL);

	// 성소
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Otehr_TownSanctuary",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Object/Other/Use/town_sanctuary.png")), E_FAIL);


#pragma endregion


#pragma endregion

	// ===============================================================
	
	// ============================= NPC =============================
#pragma region NPC

	// King
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_King",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/King/%d.png", 8)), E_FAIL);

	// Mage
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Mage/%d.png", 8)), E_FAIL);

	// BlackSmith
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_BlackSmith",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Smith/%d.png", 8)), E_FAIL);

	// Soldier
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Soldier",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/Soldier/%d.png", 8)), E_FAIL);

	// Citizen1
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Citizen1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/TownNpc1/%d.png", 8)), E_FAIL);

	// Citizen2
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Citizen2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Npc/TownNpc2/%d.png", 8)), E_FAIL);


#pragma endregion
	// ===============================================================

	// =========================== Effect ============================
#pragma region EFFECT

	// 구름 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3.png")), E_FAIL);

	// 구름 그림자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud1_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_1_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud3_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_2_shadow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Colud2_Shadow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Cloud/cloud_3_shadow.png")), E_FAIL);

	// 플레이어 이동 효과
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Dust",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/dust/%d.png", 5)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Move_Water",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/watersplash/%d.png", 4)), E_FAIL);

	// 그림자
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Shadow_Creature",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Shadow/cat_shadow.png")), E_FAIL);

	// 꽃가루
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Pollen",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Pollen/Pollen.png")), E_FAIL);

	// 아이템 반짝이
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_ItemSparkle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Item/Sparkle.png")), E_FAIL);

	// 몬스터스피릿
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_MonsterSpirit",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/MonsterSpirit.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritorb",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritorb.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Spiritwave",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/MonstrSpirit/spiritwave.png")), E_FAIL);

	// 플레이어 슬래쉬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Player_Slash_Rising",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/PlayerSlash/Rising/%d.png", 4)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Player_Slash_Chopping",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/PlayerSlash/Chopping/%d.png", 4)), E_FAIL);

	// 몬스터 피격
	// 검
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Monster_Cut_Effect",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/CutEffect/CutEffect.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Monster_CutOrb_Effect",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/CutEffect/CutOrb.png")), E_FAIL);

// ===============================================================

// =========================== Inventory ============================
#pragma region Inventory
	// Inventory - BackGround
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_BKG",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/white_bg.png")), E_FAIL);
	
	// Inventory - Cursor
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Cursor",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_cursor.png")), E_FAIL);

	// Inventory - Tab Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_tab.png")), E_FAIL);

	// Inventory - Tab Armors Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab_Armors_Texture",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_armors.png")), E_FAIL);

	// Inventory - Tab Skill Texture
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Tab_Skill_Texture",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_attackskill.png")), E_FAIL);

	// Inventory - UI Blank Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_blank",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_blank_button.png")), E_FAIL);

	// Inventory - UI Button
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button.png")), E_FAIL);

	//Inventory - UI Button Gold
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_gold.png")), E_FAIL);

	// Inventory - UI button Plain
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Plain",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_plain.png")), E_FAIL);

	// Inventory - UI Cancel 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Button_Cancel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_cancel.png")), E_FAIL);

	// Inventory - UI TabLine
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Line",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_line.png")), E_FAIL);

	// Inventory - UI TabLine
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_TabLine",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_line4px.png")), E_FAIL);

	// Inventory - UI WeaponSelect
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Weapon_Select",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_equipped_weapon.png")), E_FAIL);

	// Inventory - UI Ok
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_OK",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_OK.png")), E_FAIL);

	// Inventory - UI No
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_NO",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_button_NO.png")), E_FAIL);

	// Inventory - UI Fancy
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Fancy",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_fancy.png")), E_FAIL);

	// Inventory - UI Player
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_iconGold.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_HpBar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_HpBar.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_MpBar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_MpBar.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Armor",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statDef.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Heart",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statHeart #145685.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Damage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statDamage.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Player_Magic",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_statMagic.png")), E_FAIL);

	// Inventory - UI Skill
	// Empty
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Empty",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_skill_empty.png")), E_FAIL);
	// Number
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Number1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_PC_1_key.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Number2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_PC_2_key.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Number3",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_PC_3_key.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Number4",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/UI_PC_4_key.png")), E_FAIL);
	// Skill Book
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Inventory_Skill_Book",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory/miniscene_codex.png")), E_FAIL);

#pragma region 아이템, 스킬 획득 관련
	// Skill Glow
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skill_Glow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetSkillUI/Effect/UI_skill_glow.png")), E_FAIL);
	// Skill Shine
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skill_Shine",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetSkillUI/Effect/UI_shine.png")), E_FAIL);
	// Skill Sparkle
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skill_Sparkle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetSkillUI/Effect/VFX_yellow_sparks.png")), E_FAIL);
	// GetSkillUI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Skill_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetSkillUI.png")), E_FAIL);
	// GetSkillFly
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Fly_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetSkillUI/UI/UI_flight.png")), E_FAIL);

	// Weapon Glow
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Warrior_Weapon_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetWeaponUI/EFFECT/thorns_weapon - Glow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Ninja_Weapon_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetWeaponUI/EFFECT/ninja_weapon - Glow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Mage_Weapon_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetWeaponUI/EFFECT/mage_weapon - Glow.png")), E_FAIL);
	// GetWeaponUI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Weapon_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/GetWeaponUI.png")), E_FAIL);
	// GetInvenUI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Get_Inven_UI",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/GetUI/UI_inventory.png")), E_FAIL);

#pragma endregion

#pragma region BINGO

	// npc 비석
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Npc_Zeolite",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Temple_Tablet.png")), E_FAIL);
	// 리스트
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_List",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/%d.png", 9)), E_FAIL);

	// 한개씩
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_China",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/0.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_USA",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/1.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_France",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/2.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Germany",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/3.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Italy",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/4.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Japen",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/5.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Russia",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/6.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Thai",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Flag/7.png")), E_FAIL);
	// 정답 체크
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Flag_Check",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/UI_checkbox_tick.png")), E_FAIL);

	// 빙고 UI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bingo_Clear",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/UI_checkbox_tick.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bingo_Fail",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/UI_no.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bingo_Succes",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/UI_yes.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bingo_Bingo",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/UI_checkbox_tick.png")), E_FAIL);

	// Bingo_Trap
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bingo_Trap_Fist",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/MiniGame/Bingo/Trap/Trap_Fist.png")), E_FAIL);


#pragma endregion

#pragma endregion

#pragma endregion

#pragma region KIM

	//// Monster - test - CuteMonster
	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster",
	//	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/cutscene_intro_sister_01.png")), E_FAIL);

	//// Monster - Bat
	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Bat",
	//	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/bat_idle1.png")), E_FAIL);


	// Monster - TestMob 

	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Front/%d.png" ,17 )), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Back/%d.png", 17)), E_FAIL);
*/


	// Monster - Dragon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_fIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Front/Idle/%d.png",5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_fAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Front/Attack/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_bIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Back/Idle/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dragon_bAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Dragon/Back/Attack/%d.png", 6)), E_FAIL);


	// Monster - Hedgehog
 	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Basic/Front/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Basic/Back/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Front/%d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Hedgehog_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Hedgehog/Attack/Back/%d.png", 19)), E_FAIL);


	// Monster - Bat
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Bat",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Basic/Back/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Bat_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Attack/Front/%d.png", 8)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Bat_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Bat/Attack/Back/%d.png", 8)), E_FAIL);



	// Monster - Ram
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Basic/Front/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Ram",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Basic/Back/0.png")), E_FAIL);
	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Ram_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Attack/Front/%d.png", 19)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Ram_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Ram/Attack/Back/%d.png", 19)), E_FAIL);


	// Monster - Wyvern
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Wyvern",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Basic/Back/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Wyvern_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Attack/Front/%d.png", 9)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Wyvern_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Wyvern/Attack/Back/%d.png", 9)), E_FAIL);




	// Monster - Fox
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/Front/%d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Fox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fox/Back/%d.png", 7)), E_FAIL);


	// Monster - Squirrel
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/Front/%d.png",1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Squirrel",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Squirrel/Back/%d.png",1)), E_FAIL);



	// Monster - Wyvern Red
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_WyvernRed",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Basic/Front/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_WyvernRed",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Basic/Back/%d.png",4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_WyvernRed_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Attack/Front/%d.png", 9)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_WyvernRed_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/WyvernRed/Attack/Back/%d.png", 9)), E_FAIL);



	// Monster - Serpent
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Serpent",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Serpent/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Serpent",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Serpent/Back/%d.png", 1)), E_FAIL);



	// Monster - Fish
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Fish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fish/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Fish",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Fish/Back/%d.png", 1)), E_FAIL);



	// Monster - Merlion
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Merlion",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Merlion/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Merlion",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Merlion/Back/%d.png", 1)), E_FAIL);


	// Monster - Cathulu
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_Cathulu",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Cathulu/Front/%d.png", 1)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_Cathulu",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/Cathulu/Back/%d.png", 1)), E_FAIL);


	// Boss Monster - Violet Dragon
	
	// Front
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Basic/Front/%d.png", 8)), E_FAIL);
	// Back
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Basic/Back/%d.png", 8)), E_FAIL);
	// Attack Front
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Front_VioletDragon_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Attack/Front/%d.png", 18)), E_FAIL);
	// Attack Back
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Back_VioletDragon_Attack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Attack/Back/%d.png", 18)), E_FAIL);
	
	// Pattern ========
	// FullDown Fly
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_FullDown_VioletDragon_Fly",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/FullDown/Fly/%d.png", 13)), E_FAIL);
	// FullDown Down
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_FullDown_VioletDragon_Down",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/FullDown/Down/%d.png", 6)), E_FAIL);

	// ConvergingFire Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_ConvergingFire_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/ConvergingFire/%d.png", 11)), E_FAIL);

	// Bloody Thunder Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_BloodyThunder_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/BloodyThunder/%d.png", 10)), E_FAIL);

	// Blue Thunder Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_BlueThunder_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/BlueThunder/%d.png", 10)), E_FAIL);



	// Create Wyvern Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_CreateWyvern_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/CreateWyvern/%d.png", 7)), E_FAIL);

	// SpreadBullet Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_SpreadBullet_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/SpreadBullet/%d.png", 11)), E_FAIL);

	// ShootingStar Cast
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_ShootingStar_VioletDragon_Cast",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/ShootingStar/%d.png", 8)), E_FAIL);

	// Dash - Front
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dash_VioletDragon_Front",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Dash/Front/%d.png", 6)), E_FAIL);

	// Dash - Back
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dash_VioletDragon_Back",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Dash/Back/%d.png", 6)), E_FAIL);

	// Ready Pattern
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_ReadyPattern_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/ReadyPattern/%d.png", 13)), E_FAIL);

	// Intro_Down
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Intro_Down_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Intro_Down/%d.png", 9)), E_FAIL);

	//Intro_Wing
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Intro_Wing_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Intro_Wing/%d.png", 17)), E_FAIL);

	//Intro_Sword
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Intro_Sword_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Intro_Sword/%d.png", 15)), E_FAIL);

	// Dead
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Dead_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/Dead/%d.png", 17)), E_FAIL);



	//// Near
	//// front
	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Near_Front_VioletDragon",
	//	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/NearAttack/Front/%d.png", 16)), E_FAIL);
	//// Back
	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Near_Back_VioletDragon",
	//	CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/NearAttack/Back/%d.png", 16)), E_FAIL);


	// Watch in sky
	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_WatchInSky_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/WatchInSky/%d.png", 17)), E_FAIL);*/

	// Watch Up
	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_WatchUp_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/WatchUp/%d.png", 17)), E_FAIL);*/


	// Watch Down
	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_WatchDown_VioletDragon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/VioletDragon/WatchDown/%d.png", 17)), E_FAIL);*/





	// Projectile ==================================================================

	// Puple_Bullet
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_PupleBullet",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Puple_Bullet.png")), E_FAIL);

	// Red_Bullet
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_RedBullet",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Red_Bullet.png")), E_FAIL);

	// Green_Bullet
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_GreenBullet",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Green_Bullet.png")), E_FAIL);

	// Red_Bullet_Another
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_RedBullet_Another",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Red_Bullet_Another.png")), E_FAIL);

	// Star_Bullet_Another
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_StarBullet_Another",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Star_Bullet_Another2.png")), E_FAIL);

	// Green_Dragger
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_GreenDager",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Green_Dagger.png")), E_FAIL);


	// Blue_Star_bullet_
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_BlueStar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Star_Bullet.png")), E_FAIL);


	// Red_Star_bullet_
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_RedStar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/RedStar_Bullet.png")), E_FAIL);




	// Item ========================================================================

	//  Item - Gold
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Gold.png")), E_FAIL);

	// Item - Exp
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Exp",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Exp.png")), E_FAIL);

	// Item - Key
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_Key",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Object/Key.png")), E_FAIL);

	// Item - WorldFlight
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_WorldFlight",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/QuestItem/World_flight.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_WorldFlight_Ora",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/QuestItem/World_Flight_Ora.png")), E_FAIL);
	

	// Item - Warrior Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_WarriorWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/thorns_weapon.png")), E_FAIL);
		

	// Item - Mage Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_MageWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/mage_weapon.png")), E_FAIL);

	// Item - Ninja Weapon
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Item_NinjaWeapon",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Item/Weapon/ninja_weapon.png")), E_FAIL);



	// Effect =========================================================================
	
	// Circle Stemp
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Circle_Stemp",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/groundwave/basic_shockwave.png")), E_FAIL);

	// Big Circle Stemp
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Big_Circle_Stemp",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/groundwave/Big_shockwave.png")), E_FAIL);

	// Big Range_Skill_Circle_Red
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_BigRangeSkill_Circle_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/range/Big_Range_Skill_Circle_Red.png")), E_FAIL);


	//// Boss Skill =====================================================================
	// Bloody Thunder
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Boss_Thunder",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Boss_Thunder/%d.png", 12)), E_FAIL);

	// Blue Thunder
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Boss_Thunder_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Boss_Thunder_Blue/%d.png", 12)), E_FAIL);


	// Effect Range 
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Small_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Small_Red.png")), E_FAIL);


	//Effect Projectile Hit Purple
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Hit_Purple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Hit_Purple/%d.png", 3)), E_FAIL);

	//Effect Projectile Hit Green
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Hit_Green",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Hit_Green/%d.png", 3)), E_FAIL);


	//Effect Projectile Hit Red
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Hit_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Hit_Red/%d.png", 3)), E_FAIL);

	//Effect Projectile Hit Blue
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Hit_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Hit_Blue/%d.png", 3)), E_FAIL);



	//Effect Projectile Boom Blue
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Boom_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Boom_Blue/%d.png", 3)), E_FAIL);


	//Effect Projectile Boom Red
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Boom_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Boom_Red/%d.png", 3)), E_FAIL);


	//Effect Projectile Boom Green
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Boom_Green",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Boom_Green/%d.png", 3)), E_FAIL);


	//Effect Projectile Boom Purple
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Projectile_Boom_Purple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Battle/Boom_Purple/%d.png", 3)), E_FAIL);


	// Effect Purple Range
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_range_Purple",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Big_Purple.png")), E_FAIL);

	// Effect Boss HellFire
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Boss_HellFire",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Boss_HellFire/%d.png", 8)), E_FAIL);







#pragma endregion

#pragma region LEE

	// 플레이어 텍스처
	// 노말
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Idle/Normal/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWalk",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Walk/Normal/%d.png", 12)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fHit",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Hit/Normal/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fRoll",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Roll/Normal/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack0/Normal/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack1/Normal/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack2/Normal/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fDie",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Die/Normal/%d.png", 14)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWake",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Wake/Normal/%d.png", 21)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fSleep",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Sleep/Normal/Sleep.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fFlight",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Flight/Normal/%d.png", 10)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bIdle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Idle/Normal/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bWalk",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Walk/Normal/%d.png", 15)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bRoll",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Roll/Normal/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack0/Normal/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack1",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack1/Normal/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack2",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack2/Normal/%d.png", 6)), E_FAIL);

	// 성기사

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bIdle_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Idle/Thorn/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bWalk_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Walk/Thorn/%d.png", 15)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bRoll_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Roll/Thorn/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack0/Thorn/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack1_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack1/Thorn/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack2_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack2/Thorn/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fIdle_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Idle/Thorn/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWalk_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Walk/Thorn/%d.png", 12)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fHit_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Hit/Thorn/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fRoll_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Roll/Thorn/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack0/Thorn/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack1_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack1/Thorn/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack2_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack2/Thorn/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fDie_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Die/Thorn/%d.png", 14)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWake_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Wake/Thorn/%d.png", 21)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fSleep_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Sleep/Thorn/Sleep.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fFlight_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Flight/Thorn/%d.png", 10)), E_FAIL);


	// 닌자

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bIdle_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Idle/Ninja/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bWalk_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Walk/Ninja/%d.png", 15)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bRoll_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Roll/Ninja/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack0/Ninja/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack1_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack1/Ninja/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack2_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack2/Ninja/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fIdle_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Idle/Ninja/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWalk_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Walk/Ninja/%d.png", 12)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fHit_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Hit/Ninja/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fRoll_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Roll/Ninja/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack0/Ninja/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack1_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack1/Ninja/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack2_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack2/Ninja/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fDie_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Die/Ninja/%d.png", 14)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWake_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Wake/Ninja/%d.png", 21)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fSleep_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Sleep/Ninja/Sleep.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fFlight_Ninja",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Flight/Ninja/%d.png", 10)), E_FAIL);

	// 마법새

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bIdle_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Idle/Mage/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bWalk_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Walk/Mage/%d.png", 15)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bRoll_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Roll/Mage/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack0/Mage/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack1_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack1/Mage/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_bAttack2_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Back/Attack/Attack2/Mage/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fIdle_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Idle/Mage/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWalk_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Walk/Mage/%d.png", 12)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fHit_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Hit/Mage/0.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fRoll_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Roll/Mage/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack0/Mage/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack1_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack1/Mage/%d.png", 5)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack2_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack2/Mage/%d.png", 6)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fDie_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Die/Mage/%d.png", 14)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fWake_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Wake/Mage/%d.png", 21)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fSleep_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Sleep/Mage/Sleep.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fFlight_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Flight/Mage/%d.png", 10)), E_FAIL);

	// UI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Ring",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Ring.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Zoom",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Zoom/%d.png", 2)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Tab",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Inventory.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Level",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_Level.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Enter",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Enter/%d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Bar",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Bar/%d.png", 16)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Indicator",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Indicator.png")), E_FAIL);
	// 쉐이드느낌
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Shade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Shade.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Dropshade",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Dropshade.png")), E_FAIL);
	//  스킬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Skill",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Skill/%d.png", 7)), E_FAIL);
	// 마나서클
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_MpCircle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/MpCircle.png")), E_FAIL);
	// 작은화살표
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SmallArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SmallArrow.png")), E_FAIL);
	// 다이얼로그 박스
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpeechBox",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpeechBox.png")), E_FAIL);
	// 다이얼로그 화살표
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_ScrollArrow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/ScrollArrow/%d.png", 3)), E_FAIL);
	// NPC스탠드
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_NpcStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/NpcStand/%d.png", 7)), E_FAIL);
	// 스피릿스탠드
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_SpiritStand",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/SpiritStand/%d.png", 5)), E_FAIL);

	// 힐 이펙트
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Heal",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/EffectHeal/%d.png", 12)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_HealDrop",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/HealDrop.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_HealPaw",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/PawPink.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_HealSpark",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/Heal/PawSpark.png")), E_FAIL);
	// 플라이 스킬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Flight",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/UI_flight.png")), E_FAIL);
	// 마법사 불렛
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_Mage",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Projectile/Mage_Ball.png")), E_FAIL);

	// 플라이 스킬 장판?
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skill_Flight_Target",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Skill/Flight/Target.png")), E_FAIL);

	// 플라이 스킬 번개
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Skill_Flight_Lighting",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Skill/Flight/Lighting/%d.png", 7)), E_FAIL);

	// 던전UI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_DungeionText",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/DungeonText.png")), E_FAIL);

	// 기사용
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Ora",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Knight/Ora.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_YellowSparkle",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Knight/Yellow_Spark.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_ThornAttack",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Knight/Solar/%d.png", 4)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Player_fAttack3_Thorn",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Front/Attack/Attack3/Thorn/%d.png", 12)), E_FAIL);
	// 기사스킬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_BlueFire",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/BlueFire/%d.png", 29)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_GoldThunder",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/GoldThunder/%d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_CrystalIce",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/CrystalIce/%d.png", 13)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_GoldenBeam",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Completed/GoldenBeam/%d.png", 20)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Gold",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Gold.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Gold"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Gold.png")), E_FAIL);
	// 레벨업 이펙트
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Banner_Blue"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/LevelUp/banner_blue.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Glow"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/LevelUp/glow.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Shine"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/LevelUp/shine.png")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Shine02"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/LevelUp/shine_02.png")), E_FAIL);

	// 눈 이펙트
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Snow"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Snow/Snow.png")), E_FAIL);
	// 비 이펙트
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Rain"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Rain/RainDrop/%d.png", 7)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_RainRipple"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Effect/Environment/Rain/RainRipple/%d.png", 5)), E_FAIL);
	// 마법사 겨냥 스킬
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_Arrow"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Arrow.png")), E_FAIL);

	// 퀘스트용 멋들어진 Box UI
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_UI_QuestBox"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/UI/Quest_Box.png")), E_FAIL);

	// 용가리 터렛
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Monster_Skull"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/DragonSkull/Skull/%d.png", 2)), E_FAIL);

	// 용가리 터렛 발사체
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Projectile_Pile"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Monster/DragonSkull/Pile_Purple.png")), E_FAIL);

#pragma endregion
	 
#pragma region YUN

	// 이펙트-스킬

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Fire",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Fire/%d.png", 29)), E_FAIL); 

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Thunder",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Thunder/%d.png", 11)), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Ice",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Ice/%d.png", 13)), E_FAIL); 
	
	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Skill_Beam",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/Completed/Beam/%d.png", 20)), E_FAIL); 



	// 이펙트 - 스킬 - 장판 (쿼터)

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Big_Red.png")), E_FAIL); 

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Yellow",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Big_Yellow.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Attack_Circle_Red",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Attack_Red.png")), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Vertical_Arrow_Red"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Vertical_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Vertical_Arrow_Blue",
		CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Arrow_Vertical_Blue.png")), E_FAIL);


	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Purple"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Purple.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Red"
			, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Square_Red.png")), E_FAIL);


	// 이펙트 - 스킬 - 장판 (일반)

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Ritual_Circle_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Ritual_Circle_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_RitualBroken_Circle_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_RitualBroken_Circle_Red.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_RitualBroken_Circle_Blue"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_RitualBroken_Circle_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Ritual_Circle_Blue"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Ritual_Circle_Blue.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Small_Purple"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Small_Purple.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Small_Red"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Effect/All/range/Range_Skill_Circle_Small_Red.png")), E_FAIL);

	// Logo
	/*FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Background_Black"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Logo/black.png")), E_FAIL);

	FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_Background_White"
		, CTexture::Create(m_pGraphicDev, TEX_NORMAL
			, L"../Bin/Resource/Texture/Logo/white.png")), E_FAIL);*/

	//FAILED_CHECK_RETURN(Engine::Ready_Texture(L"Proto_Texture_BackgroundShade"
	//	, CTexture::Create(m_pGraphicDev, TEX_NORMAL
	//		, L"../Bin/Resource/Texture/Logo/BackgroundShade.png")), E_FAIL);

#pragma endregion


#pragma endregion

	m_bFinish = true;

	return 0;
}


CLoadingThread * CLoadingThread::Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADING_THREAD_TYPE eID)
{
	CLoadingThread*		pInstance = new CLoadingThread(pGraphicDev);

	if (FAILED(pInstance->Ready_Loading(eID)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Loading Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLoadingThread::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	DeleteCriticalSection(&m_Crt);

	Safe_Release(m_pGraphicDev);
}

