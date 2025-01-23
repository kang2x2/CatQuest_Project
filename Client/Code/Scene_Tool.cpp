#include "stdafx.h"
#include "..\Header\Scene_Tool.h"

#include "Export_Function.h"

// 터레인
#include "TerrainWorld.h"
#include "TerrainTool.h"
#include "Terrain_Dungeon.h"
#include "Terrain_Temple.h"

// 빌딩(집)
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
#include "Hedgehog.h"
#include "LineObject.h"
#include "Bat.h"
#include "Dragon.h"
#include "Ram.h"
#include "Fox.h"
#include "Wyvern.h"
#include "WyvernRed.h"
#include "Squirrel.h"
#include "Fish.h"
#include "Serpent.h"
#include "VioletDragon.h"

#include "Player.h"
#include "CuteMonster.h"
#include "Environment.h"
#include "Tool_Camera.h"
#include "CameraTargetObj.h"

// Item
#include "GoldCoin.h"
#include "ExpCoin.h"
#include "Key.h"
#include "WarriorWeapon.h"
#include "MageWeapon.h"
#include "NinjaWeapon.h"


// New Enviorment
#include "TwinPeaks.h"
#include "DeathTree.h"
#include "TripleDeathTree.h"
#include "WorldTree.h"
#include "Grass1.h"
#include "Tombstone.h"
#include "PirateHideOut.h"
#include "Sweets1.h"
#include "Sweets2.h"

// New Environment 2
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

// 그 외
#include "DrakothTable.h"
#include "WorldPotion.h"
#include "TownSanctuary.h"
#include "Paper.h"
#include "Present.h"

#include "ImGuiMgr.h"
#include "Calculator.h"

CScene_Tool::CScene_Tool(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::TOOL)
{
}

CScene_Tool::~CScene_Tool()
{
}

HRESULT CScene_Tool::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Layer_Camera(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Terrain(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Environment(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Monster(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Npc(), E_FAIL);
	FAILED_CHECK_RETURN(Ready_Layer_Item(), E_FAIL);

	FAILED_CHECK_RETURN(CImGuiMgr::GetInstance()->ImGui_SetUp(m_pGraphicDev), E_FAIL);

	ShowCursor(TRUE);

	return S_OK;
}

Engine::_int CScene_Tool::Update_Scene(const _float& fTimeDelta)
{
	__super::Update_Scene(fTimeDelta);

	CImGuiMgr::GetInstance()->ImGui_Update();

	return 0;
}

void CScene_Tool::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();

	CCameraMgr::GetInstance()->Set_ViewSpace();
}

void CScene_Tool::Render_Scene()
{
	CImGuiMgr::GetInstance()->ImGui_Render(); 

#pragma region Stack

	RECT	rc{};
	_vec3	vPos{};
	CGameObject* pObj = nullptr;
	TCHAR	szBuf[MAX_STR] = L"";
	GetClientRect(g_hWnd, &rc);

#pragma endregion
	swprintf_s(szBuf, L"%.d FPS", _int(1.f / Engine::Get_TimeDelta(L"Timer_FPS65")));
	SCREEN_MSG(szBuf, rc);
}

void CScene_Tool::Free()
{
	CCalculator::GetInstance()->DestroyInstance();

	__super::Free();
}

CScene_Tool* CScene_Tool::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScene_Tool* pInstance = new CScene_Tool(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);
		
		MSG_BOX("Scene_Tool Create Failed");

		return nullptr;
	}

	return pInstance;
}
HRESULT CScene_Tool::Ready_Layer_Terrain()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::TERRAIN, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	 pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain_World", pGameObject), E_FAIL);

	 pGameObject = CTerrainDungeon::Create(m_pGraphicDev);
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain_Dungeon", pGameObject), E_FAIL);

	 pGameObject = CTerrainTemple::Create(m_pGraphicDev);
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain_Temple", pGameObject), E_FAIL);

	 /* pGameObject = CTerrainIceDungeon::Create(m_pGraphicDev);
	 NULL_CHECK_RETURN(pGameObject, E_FAIL);
	 FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainDungeon_Ice", pGameObject), E_FAIL);*/

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Environment()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::ENVIRONMENT, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Terrain
	pGameObject = CTerrainWorld::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"TerrainWorld", pGameObject), E_FAIL);

	// House
	pGameObject = CHouse1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House1", pGameObject), E_FAIL);

	pGameObject = CHouse2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House2", pGameObject), E_FAIL);

	pGameObject = CHouse3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House3", pGameObject), E_FAIL);

	pGameObject = CHouse4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House4", pGameObject), E_FAIL);

	pGameObject = CHouse5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House5", pGameObject), E_FAIL);

	pGameObject = CHouse6::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"House6", pGameObject), E_FAIL);

	// King House
	pGameObject = CKingHouse::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"KingHouse", pGameObject), E_FAIL);

	// Smithy
	pGameObject = CSmithy::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Smithy", pGameObject), E_FAIL);

	// Magic Shop
	pGameObject = CMagicShop::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MagicShop", pGameObject), E_FAIL);


	// Bush
	pGameObject = CBush1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush1", pGameObject), E_FAIL);

	pGameObject = CBush2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush2", pGameObject), E_FAIL);

	pGameObject = CBush3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush3", pGameObject), E_FAIL);

	pGameObject = CBush4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush4", pGameObject), E_FAIL);

	pGameObject = CBush5::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush5", pGameObject), E_FAIL);

	pGameObject = CBush6::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush6", pGameObject), E_FAIL);

	pGameObject = CBush7::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush7", pGameObject), E_FAIL);

	pGameObject = CBush8::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush8", pGameObject), E_FAIL);

	pGameObject = CBush9::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush9", pGameObject), E_FAIL);

	pGameObject = CBush10::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush10", pGameObject), E_FAIL);

	pGameObject = CBush11::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Bush11", pGameObject), E_FAIL);

	// Mountain
	pGameObject = CMountain_Grass::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Grass", pGameObject), E_FAIL);

	pGameObject = CMountain_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Mountain_Ice", pGameObject), E_FAIL);

	// Rock
	pGameObject = CRock1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock1", pGameObject), E_FAIL);

	pGameObject = CRock2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock2", pGameObject), E_FAIL);

	pGameObject = CRock3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock3", pGameObject), E_FAIL);

	pGameObject = CRock4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock4", pGameObject), E_FAIL);

	// Rock Pillar
	pGameObject = CRock_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar1", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar2", pGameObject), E_FAIL);

	pGameObject = CRock_Pillar3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Rock_Pillar3", pGameObject), E_FAIL);

	// Temple Pillar
	pGameObject = CTemple_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar1", pGameObject), E_FAIL);

	pGameObject = CTemple_Pillar2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Temple_Pillar2", pGameObject), E_FAIL);

	// Ice Pillar
	pGameObject = CIce_Pillar1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Ice_Pillar1", pGameObject), E_FAIL);

	// Dungeon
	pGameObject = CDungeon_Grass::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Grass", pGameObject), E_FAIL);

	// Enterance
	pGameObject = CDungeon_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Ice", pGameObject), E_FAIL);

	pGameObject = CDungeon_Temple::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Dungeon_Temple", pGameObject), E_FAIL);

	// Tower
	pGameObject = CTower1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower1", pGameObject), E_FAIL);

	pGameObject = CTower2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower2", pGameObject), E_FAIL);

	pGameObject = CTower3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Tower3", pGameObject), E_FAIL);

	// Cosmetic Chest
	pGameObject = CChest_Cosmetic::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Cosmetic_Chest", pGameObject), E_FAIL);

	// Gold Chest
	pGameObject = CChest_Gold::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Gold_Chest", pGameObject), E_FAIL);

	// Regular Chest
	pGameObject = CChest_Regular::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Regular_Chest", pGameObject), E_FAIL);


	// New

	// TwinPeaks
	pGameObject = CTwinPeaks::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TwinPeaks", pGameObject), E_FAIL);

	// Death Tree
	pGameObject = CDeathTree::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"DeathTree", pGameObject), E_FAIL);

	// Triple Death Tree
	pGameObject = CTripleDeathTree::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"TripleDeathTree", pGameObject), E_FAIL);

	// World Tree
	pGameObject = CWorldTree::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"WorldTree", pGameObject), E_FAIL);

	// Grass
	pGameObject = CGrass1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Grass1", pGameObject), E_FAIL);

	// Tombstone
	pGameObject = CTombstone::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Tombstone", pGameObject), E_FAIL);

	// PirateHideOut
	pGameObject = CPirateHideOut::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"PirateHideOut", pGameObject), E_FAIL);

	// Sweets
	pGameObject = CSweets1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"CSweets1", pGameObject), E_FAIL);

	pGameObject = CSweets2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"CSweets2", pGameObject), E_FAIL);


	// New 2 

	// 2차 추가본
	pGameObject = CNoticeBoard::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 표지판
	pGameObject = CSignAstropaw::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignCattrap::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignFlame::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignFreeze::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignHeal::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignLight::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignPurrserk::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignStop::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignTwinTown::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignFish::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CSignWoodFish::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 뼈
	pGameObject = CDragonSkull1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CDragonSkull2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CDragonSkull3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// 난파선 조각
	pGameObject = CWreckShip::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWreckPiece1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWreckPiece2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWreckPiece3::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWreckPiece4::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	// WALL
	pGameObject = CWall1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWall2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	
	
	
	
	// Other
	pGameObject = CDrakothTable::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CPaper::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CPresent::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CTownSanctuary::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	pGameObject = CWorldPotion::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);

	
	
	
	
	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Camera()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::CAMERA, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Camera
	pGameObject = CTool_Camera::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Camera", pGameObject), E_FAIL);
	CCameraMgr::GetInstance()->Add_Camera(L"MainCamera", static_cast<CCameraObject*>(pGameObject));
	CCameraMgr::GetInstance()->Set_MainCamera(L"MainCamera");

	// Camera Target Obj -> Player
	pGameObject = CCameraTargetObj::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"CameraTargetObj", pGameObject), E_FAIL);


	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Monster()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::MONSTER, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// Hedgehog
	pGameObject = CHedgehog::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog", pGameObject), E_FAIL);

	// Ram
	pGameObject = CRam::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Ram", pGameObject), E_FAIL);

	// Fox
	pGameObject = CFox::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fox", pGameObject), E_FAIL);

	//Bat
	pGameObject = CBat::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Bat", pGameObject), E_FAIL);

	// Wyvern
	pGameObject = CWyvern::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Wyvern", pGameObject), E_FAIL);

	// Wyvern Red
	pGameObject = CWyvernRed::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_WyvernRed", pGameObject), E_FAIL);

	// Fish
	pGameObject = CFish::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Fish", pGameObject), E_FAIL);

	// Serpent
	pGameObject = CSerpent::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Serpent", pGameObject), E_FAIL);

	// Dragon
	pGameObject = CDragon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Dragon", pGameObject), E_FAIL);

	// Violet Dragon
	pGameObject = CVioletDragon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_VioletDragon", pGameObject), E_FAIL);

	//// Squirrel
	//pGameObject = CSquirrel::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Monster_Squirrel", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Npc()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	m_mapLayer.insert({ OBJ_TYPE::NPC, pLayer });

	Engine::CGameObject* pGameObject = nullptr;

	// King
	pGameObject = CNpc_King::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_King", pGameObject), E_FAIL);

	// Mage
	pGameObject = CNpc_Mage::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Mage", pGameObject), E_FAIL);

	// BlackSmith
	pGameObject = CNpc_BlackSmith::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_BlackSmith", pGameObject), E_FAIL);

	// Soldier
	pGameObject = CNpc_Soldier::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Soldier", pGameObject), E_FAIL);

	// Citizen1
	pGameObject = CNpc_Citizen1::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen1", pGameObject), E_FAIL);

	// Citizen2
	pGameObject = CNpc_Citizen2::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Npc_Citizen2", pGameObject), E_FAIL);

	return S_OK;
}

HRESULT CScene_Tool::Ready_Layer_Item()
{
	Engine::CLayer* pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pGameObject = nullptr;
	m_mapLayer.insert({ OBJ_TYPE::ITEM, pLayer });

	// Object ==================
	
	// Gold
	pGameObject = CGoldCoin::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", pGameObject), E_FAIL);


	// Exp
	pGameObject = CExpCoin::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_ExpCoin", pGameObject), E_FAIL);

	// Key
	pGameObject = CKey::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_Key", pGameObject), E_FAIL);

	// Weapon ================
	
	// Warrior
	pGameObject = CWarriorWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_WarriorWeapon", pGameObject), E_FAIL);

	// Mage
	pGameObject = CMageWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_MageWeapon", pGameObject), E_FAIL);

	// Ninja
	pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Item_NinjaeWeapon", pGameObject), E_FAIL);

	return S_OK;
}
