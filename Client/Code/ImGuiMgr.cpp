#define _CRT_SECURE_NO_WARNINGS


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#include "ImGuiMgr.h"

#include <iostream>
#include <Windows.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi")

#include "Export_Function.h"

#include "stdafx.h"
#include "MainApp.h"
#include "InputDev.h"
#include "Calculator.h"

#include "Tool_Camera.h"
#include "CameraTargetObj.h"
#include "TerrainTool.h"
#include <iostream>



// Environment
#include "Terrain.h"
#include "TerrainWorld.h"
#include "Terrain_Dungeon.h"
#include "Terrain_Temple.h"

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
#include "Squirrel.h"
#include "Fish.h"
#include "Serpent.h"
#include "VioletDragon.h"

// Effect
#include "Cloud1.h"
#include "Cloud2.h"
#include "Cloud3.h"

#include "Effect_Cast_Blue.h"
#include "Effect_Cast_Yellow.h"
#include "Effect_Cast_Purple.h"

#include "Effect_SpellBurst_Blue.h"
#include "Effect_SpellBurst_Purple.h"
#include "Effect_SpellBurst_Yellow.h"

#include "Effect_Lightning.h"

#include "Effect_Fire.h"
#include "Effect_Thunder.h"

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

// Generator
#include "EffectGenerator.h"


TCHAR szLoadPath[MAX_STR] = L"../Bin/Data/Level/Level_Temple.dat";
TCHAR szSavePath[MAX_STR] = L"../Bin/Data/Level/Level_Temple.dat"; 

#pragma region Global

// 이벤트 매니저 생성 전 초기화 관련

static _bool			g_bInit = false;

static _bool			g_bPathInit = false; 

// 열거체
enum class				IMG_OBJ_TYPE { TERRAIN, ENVIRONMENT, MONSTER, NPC, ITEM, LINE, TYPEEND };

static const char*		arr_ImgObjType[(UINT)IMG_OBJ_TYPE::TYPEEND] = { "Trrain", "Environment", "Monster", "Npc", "Item", "Line" };


// 공용 변수 관련

static _int				g_iSelLayer = 0; // 현재 선택된 f레이어 인덱스

static IMG_OBJ_TYPE     g_eSelObjType = IMG_OBJ_TYPE::TERRAIN; // 현재 선택된 오브젝트 타입 인덱스

static _int				g_iSelObj = -1; // 현재 선택된 오브젝트 인덱스

// 저장 관련
typedef vector<map<OBJ_TYPE, CLayer*>>	_vecMapLayer; // == Scene List

vector<CGameObject*>	g_vecCloneObj; // 현재 씬에서 추가된 모든 오브젝트 저장


// 기타
vector<ImTextureID>		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TYPEEND]; // 이미지 아이디 경로 저장 벡터 배열

vector<CGameObject*>	g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TYPEEND]; // 원본 객체 최초 저장 배열 (저장할 때 얘네는 레이어에서 뺴줘야 한다)

CGameObject*			g_pVtxTerrain = nullptr; // 피킹처리를 위한 버텍스 터레인 (여기서 생성하고 여기서 삭제한다)

static const _int		g_iImagPerRow = 4; // 한줄당 나열할 이미지 수

#pragma endregion


IMPLEMENT_SINGLETON(CImGuiMgr)

CImGuiMgr::CImGuiMgr()
	: m_pGraphicDev(nullptr)
{
}

CImGuiMgr::~CImGuiMgr()
{
	Free();
}

HRESULT CImGuiMgr::ImGui_SetUp(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX9_Init(pGraphicDev);

	// 그리드 버텍스는 여기서 생성
	g_pVtxTerrain = CTerrainTool::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(g_pVtxTerrain, E_FAIL);
	

	return S_OK;
}

HRESULT CImGuiMgr::ImGui_SetDevice(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();

	return S_OK;
}

void CImGuiMgr::ImGui_Update()
{
	// Init (이벤트 매니저 생성 전)
	if (!g_bPathInit)
	{
		g_bPathInit = !g_bPathInit;
		Set_ImgPath();			// 맵 및 오브젝트 이미지 경로 셋업
		Set_UnActive_Origin();	// 모든 프리팹 오브젝트 비활성화

		// DB 로드
		Load_Scene(szLoadPath);
	}

	// ImGui
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Tool Tab");

	if (ImGui::CollapsingHeader("Level"))
	{
		Show_Header_Scene();
	}
	if (ImGui::CollapsingHeader("Object"))
	{
		Show_Header_Object();
	}
	if (ImGui::CollapsingHeader("Light"))
	{
		Show_Header_Light();
	}

	ImGui::End();

	// Grid Vertex
	Engine::Add_RenderGroup(RENDER_NONALPHA, g_pVtxTerrain);

	// Input 
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) return;

	if (CInputDev::GetInstance()->Key_Down(MK_LBUTTON))
	{
		_vec3 vPickPos = Get_ClickPos();

		if(vec3.zero != vPickPos) // 터레인 영역을 벗어난 피킹에 대한 예외 처리
			Clone_Object(vPickPos);
	}
	else if (CInputDev::GetInstance()->Key_Down(MK_RBUTTON))
	{
		_vec3 vPickPos = Get_ClickPos();

		if (vec3.zero != vPickPos) // 터레인 영역을 벗어난 피킹에 대한 예외 처리
			Delete_Object(vPickPos);
	}

}

void CImGuiMgr::ImGui_Render()
{
	// 이벤트 매니저 생성 전 임시 처방
	if (!g_bInit)
	{
		g_bInit = true;
		return;
	}
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CImGuiMgr::Show_Header_Scene()
{	
	// 01. Button (Action)
	ImGui::SeparatorText("Action Button");
	if (ImGui::Button("New"))
	{
	}
	ImGui::SameLine();
	if (ImGui::Button("Save"))
	{
		Save_Scene();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
	}

	// 02. List Box (Level Image)
	ImGui::SeparatorText("Level Prefab List");

	int			iCurIdxRow		= 0; // 줄 맞추기 위한 변수
	static int	iCurIdx_Scene	= 0; // 현재 선택된 인덱스

	wstring strImgPath = L"../Bin/Resource/Texture/Object/Bush/forest_5.png";
	ImTextureID image = LoadImageFile(wstring_to_utf8(strImgPath).c_str());

	if (ImGui::BeginListBox(" ", ImVec2(280.f, 180.f)))
	{
		//for (int i = 0; i < 1; ++i) // 맵의 사이즈로 바뀌어야 한다.
		//{
		//	CGameObject* pTerrain = nullptr;
		//	wstring imgPath;

		//	for (auto& iter : g_vecCloneObj)
		//	{
		//		if (OBJ_TYPE::TERRAIN == iter->Get_Type())
		//		{
		//			imgPath = dynamic_cast<CTexture*>(iter->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		//			
		//			if (ImGui::ImageButton(LoadImageFile(wstring_to_utf8(imgPath).c_str()), ImVec2(50.f, 50.f))) // 이미지 출력
		//			{
		//				iCurIdx_Scene = i;
		//				g_iSelLayer = iCurIdx_Scene;
		//			}

		//			break;
		//		}
		//	}

		//

		//	if (iCurIdxRow < g_iImagPerRow - 1) // 정렬
		//	{
		//		ImGui::SameLine();
		//		iCurIdxRow++;
		//	}
		//	else
		//		iCurIdxRow = 0;
		//}
		ImGui::EndListBox();
	}
}

void CImGuiMgr::Show_Header_Object()
{
	// 01. Combo (Object Type)
	ImGui::SeparatorText("Object Type");
	static int iCurIdx_Object_Type = 0; // 현재 선택된 인덱스
	static ImGuiComboFlags flags = 0;

	const char* combo_preview_value = arr_ImgObjType[iCurIdx_Object_Type];

	if (ImGui::BeginCombo("  ", combo_preview_value, flags))
	{
		for (int n = 0; n < IM_ARRAYSIZE(arr_ImgObjType); n++)
		{
			const bool is_selected = (iCurIdx_Object_Type == n);
			if (ImGui::Selectable(arr_ImgObjType[n], is_selected))
			{
				iCurIdx_Object_Type = n;
				g_eSelObjType = (IMG_OBJ_TYPE)iCurIdx_Object_Type;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	// 02. List Box (Object Image)
	int			iCurIdxRow		= 0; // 줄 맞추기 위한 변수
	static int	iCurIdx_Object	= 0; // 현재 선택된 인덱스

	ImGui::SeparatorText("Object Prefab List");

	if (ImGui::BeginListBox("  ", ImVec2(280.f, 480.f)))
	{
		for (int i = 0; i < g_vecObjImgPath[iCurIdx_Object_Type].size(); ++i)
		{
			if (ImGui::ImageButton(g_vecObjImgPath[iCurIdx_Object_Type][i], ImVec2(45.f, 45.f))) // 이미지 출력
			{
				iCurIdx_Object = i;

				g_iSelObj = iCurIdx_Object;
			}

			if (iCurIdxRow < g_iImagPerRow - 1) // 정렬
			{
				ImGui::SameLine();
				iCurIdxRow++;
			}
			else
				iCurIdxRow = 0;
		}
		ImGui::EndListBox();
	}
}

void CImGuiMgr::Show_Header_Light()
{
}

HRESULT CImGuiMgr::Set_ImgPath()
{
	multimap<const _tchar*, CGameObject*> mapObj;
	
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::TERRAIN)->Get_ObjectMap();

	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
			continue;
		
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Environment
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::ENVIRONMENT)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::ENVIRONMENT].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::ENVIRONMENT].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Npc
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::NPC)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::NPC].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::NPC].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Monster
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();
	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::MONSTER].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))
			continue;
	
		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::MONSTER].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	// Item
	mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::ITEM)->Get_ObjectMap();
	if (mapObj.empty())  return E_FAIL;	

	for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	{
		g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::ITEM].push_back(iter->second);

		if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
			continue;

		wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
		g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::ITEM].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	}

	//// Line
	//mapObj = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::LINE)->Get_ObjectMap();
	//if (mapObj.empty())  return E_FAIL;

	//for (auto iter = mapObj.begin(); iter != mapObj.end(); ++iter)
	//{		
	//	g_vecObjOrigin[(UINT)IMG_OBJ_TYPE::TERRAIN].push_back(iter->second);

	//	if (nullptr == iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC)) 
	//		continue;

	//	wstring imgPath = dynamic_cast<CTexture*>(iter->second->Get_Component(COMPONENT_TYPE::TEXTURE, ID_STATIC))->Get_TexturePath();
	//	g_vecObjImgPath[(UINT)IMG_OBJ_TYPE::LINE].push_back(LoadImageFile(wstring_to_utf8(imgPath).c_str()));
	//}
	
	return S_OK;
}

void CImGuiMgr::Set_UnActive_Origin()
{
	for (int i = 0; i < (UINT)IMG_OBJ_TYPE::TYPEEND; ++i)
	{
		for (auto& iter : g_vecObjOrigin[i])
			iter->Set_Active(false);
	}
}

HRESULT CImGuiMgr::Clone_Object(const _vec3 _vPickPos)
{
	// 예외처리
	if (IMG_OBJ_TYPE::TYPEEND == g_eSelObjType || 0 > g_iSelObj || g_vecObjOrigin[(UINT)g_eSelObjType].size() < g_iSelObj)
		return E_FAIL;

	// 클론
	CGameObject* pClone = nullptr;
	
	pClone = Clone(g_vecObjOrigin[(UINT)g_eSelObjType][g_iSelObj]->Get_ID());

	NULL_CHECK_RETURN(pClone, E_FAIL);

	// 포지션 세팅
	_vec3 vClonePos;

	if (OBJ_TYPE::TERRAIN == pClone->Get_Type())
		vClonePos = { pClone->Get_Transform()->Get_Scale().x, pClone->Get_Transform()->Get_Scale().y, pClone->Get_Transform()->Get_Scale().z };
	else
		vClonePos = { _vPickPos.x, pClone->Get_Transform()->Get_Info(INFO_POS).y, _vPickPos.z };

	pClone->Get_Transform()->Set_Pos(vClonePos); 

	// 매니지먼트에 추가 (렌더용)
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(g_vecObjOrigin[(UINT)g_eSelObjType][g_iSelObj]->Get_Name(), pClone), E_FAIL);

	// 저장 단위에 추가 (저장용)
	g_vecCloneObj.push_back(pClone);

	return S_OK;
}

HRESULT CImGuiMgr::Delete_Object(const _vec3 _vPickPos)
{
	// 검사 반경
	_float fRadius = VTXITV * 2.f;
	
	// 검사 결과 오브젝트
	CGameObject* pNearObj = nullptr;

	for (vector<CGameObject*>::iterator iter = g_vecCloneObj.begin(); iter != g_vecCloneObj.end(); ++iter)
	{
		_vec3 vNearObjPos{ (*iter)->Get_Transform()->Get_Info(INFO_POS).x, 0.f, (*iter)->Get_Transform()->Get_Info(INFO_POS).z };

		if (fRadius > D3DXVec3Length(&(_vPickPos - vNearObjPos)))
		{
			// 삭제 처리

			CEventMgr::GetInstance()->Delete_Obj((*iter)); // 저장용
												 								  
			g_vecCloneObj.erase(iter); // 렌더용

			return S_OK;
		}
	}
	return S_OK;
}

HRESULT CImGuiMgr::Create_Scene()
{


	return S_OK;
}

HRESULT CImGuiMgr::Delete_Scene()
{

	return S_OK;
}

HRESULT CImGuiMgr::Change_Scene()
{
	return E_NOTIMPL;
}

HRESULT CImGuiMgr::Load_All_Scene()
{

	return S_OK;
}

HRESULT CImGuiMgr::Load_Scene(TCHAR* filePath)
{
	// 파일에 저장되어 있는 데이터를 통해 오브젝트를 생성하여 g_vecCloneObj 및 매니지먼트 레이어에 추가(이벤트매니저)한다.

	// 파일 생성
	HANDLE	hFile = CreateFile(filePath,
		GENERIC_READ, 
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// 생성 여부 검사
	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return E_FAIL;
	}

	DWORD		dwByte = 0;

	_vec3		vPos{};
	OBJ_TYPE	eType = OBJ_TYPE::TYPEEND;
	OBJ_ID		eID = OBJ_ID::TYPEEND;

	while (true)
	{
		ReadFile(hFile, &vPos, sizeof(_vec3), &dwByte, nullptr);
		ReadFile(hFile, &eType, sizeof(OBJ_TYPE), &dwByte, nullptr);
		ReadFile(hFile, &eID, sizeof(OBJ_ID), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		
		CGameObject* pClone = Clone(eID);
		
		if (nullptr == pClone) continue;
		
		// 벡터와 매니지먼트 모두 푸시
		if(PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())
			g_vecCloneObj.push_back(pClone); // 저장용

		CEventMgr::GetInstance()->Add_Obj(pClone->Get_Name(), pClone); // 렌더용
		
		// 저장된 포지션으로 세팅
		pClone->Get_Transform()->Set_Pos(vPos);
	}

	CloseHandle(hFile);

	return S_OK;
}


HRESULT CImGuiMgr::Save_Scene()
{
	// 현재 씬에서 추가한 오브젝트들은 전부 g_vecCloneObj에 저장되어 있다.
	// g_vecCloneObj를 모두 파일로 저장한다.

	// 파일 생성
	HANDLE	hFile = CreateFile(szSavePath,
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// 생성 여부 검사
	if (INVALID_HANDLE_VALUE == hFile)	
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return E_FAIL;
	}

	DWORD		dwByte = 0;

	_vec3		vPos{}; 
	OBJ_TYPE	eType = OBJ_TYPE::TYPEEND;
	OBJ_ID		eID = OBJ_ID::TYPEEND;
	//wchar_t* szName = L"";


	// 저장
	for (auto& iter : g_vecCloneObj)
	{
		eType = iter->Get_Type();
		eID = iter->Get_ID();
		//wcscpy(szName, iter->Get_Name());

		WriteFile(hFile, &(iter->Get_Transform()->Get_Info(INFO_POS)), sizeof(_vec3), &dwByte, nullptr);
		WriteFile(hFile, &(eType), sizeof(OBJ_TYPE), &dwByte, nullptr);
		WriteFile(hFile, &(eID), sizeof(OBJ_ID), &dwByte, nullptr);
		//WriteFile(hFile, &(szName), sizeof(wcslen(szName) * sizeof(wchar_t)), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	return S_OK;
}

LPDIRECT3DTEXTURE9 CImGuiMgr::LoadImageFile(const char* filePath)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	D3DXIMAGE_INFO imageInfo;
	HRESULT hr = D3DXGetImageInfoFromFileA(filePath, &imageInfo);

	if (FAILED(hr)) return nullptr;

	hr = D3DXCreateTextureFromFileA(m_pGraphicDev, filePath, &pTexture);
	Safe_Release(m_pGraphicDev); 

	if (FAILED(hr)) return nullptr;

	return pTexture;
}

string CImGuiMgr::wstring_to_utf8(const std::wstring& str)
{
	string result;
	int size = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (size > 0)
	{
		result.resize(size);
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, &result[0], size, nullptr, nullptr);
	}
	return result;
}

const _vec3& CImGuiMgr::Get_ClickPos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	_vec3 vPickPos;
	ZeroMemory(&vPickPos, sizeof(_vec3));

	CCalculator::GetInstance()->Mouse_Picking(m_pGraphicDev, pt, &vPickPos, g_pVtxTerrain);

	return vPickPos;

}

void CImGuiMgr::Free()
{
	Safe_Release(m_pGraphicDev);
	
	if (g_bInit)
	{
		Safe_Release(g_pVtxTerrain);

		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}

CGameObject* CImGuiMgr::Clone(const OBJ_ID& _eID)
{

	CGameObject* pClone = nullptr;
	switch (_eID)
	{

	/* ========================================= Terrain ========================================*/


	// Terrain
	case Engine::OBJ_ID::TERRAIN_WORLD:
		pClone = CTerrainWorld::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::TERRAIN_DUNGEON:
		pClone = CTerrainDungeon::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::TERRAIN_TEMPLE:
		pClone = CTerrainTemple::Create(m_pGraphicDev); break;




	/* ========================================= Environment ========================================*/


	// Environment - Chest
	case Engine::OBJ_ID::ENVIRONMENT_CHEST_COSMETIC:
		pClone = CChest_Cosmetic::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_CHEST_GOLD:
		pClone = CChest_Gold::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_CHEST__REGULAR:
		pClone = CChest_Regular::Create(m_pGraphicDev); break;

	// Environment - Building - House
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_1:
		pClone = CHouse1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_2:
		pClone = CHouse2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_3:
		pClone = CHouse3::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_4:
		pClone = CHouse4::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_5:
		pClone = CHouse5::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_HOUSE_6:
		pClone = CHouse6::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_KINGHOUSE:
		pClone = CKingHouse::Create(m_pGraphicDev); break;

	// Environment - Building - Tower
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_TOWER_1:
		pClone = CTower1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_TOWER_2:
		pClone = CTower2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_TOWER_3:
		pClone = CTower3::Create(m_pGraphicDev); break;

	// Environment - Natural - Bush
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_1:
		pClone = CBush1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_2:
		pClone = CBush2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_3:
		pClone = CBush3::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_4:
		pClone = CBush4::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_5:
		pClone = CBush5::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_6:
		pClone = CBush6::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_7:
		pClone = CBush7::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_8:
		pClone = CBush8::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_9:
		pClone = CBush9::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_10:
		pClone = CBush10::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_BUSH_11:
		pClone = CBush11::Create(m_pGraphicDev); break;

	// Environment - Natural - Mountain
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_MOUNTAIN_GRASS:
		pClone = CMountain_Grass::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_MOUNTAIN_ICE:
		pClone = CMountain_Ice::Create(m_pGraphicDev); break;

	// Environment - Natural - Pillar
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_ICE:
		pClone = CIce_Pillar1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_ROCK_1:
		pClone = CRock_Pillar1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_ROCK_2:
		pClone = CRock_Pillar2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_ROCK_3:
		pClone = CRock_Pillar3::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_TEMPLE_1:
		pClone = CTemple_Pillar1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_TEMPLE_2:
		pClone = CTemple_Pillar2::Create(m_pGraphicDev); break;

	// Environment - Natural - Rock
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_ROCK_1:
		pClone = CRock1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_ROCK_2:
		pClone = CRock2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_ROCK_3:
		pClone = CRock3::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_ROCK_4:
		pClone = CRock4::Create(m_pGraphicDev); break;

	// Environment - Enterance
	case Engine::OBJ_ID::ENVIRONMENT_ENTERANCE_SMITHY:
		pClone = CSmithy::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_ENTERANCE_MAGICSHOP:
		pClone = CMagicShop::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_ENTERANCE_DUNGEON_GRASS:
		pClone = CDungeon_Grass::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_ENTERANCE_DUNGEON_ICE:
		pClone = CDungeon_Ice::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_ENTERANCE_DUNGEON_TEMPLE:
		pClone = CDungeon_Temple::Create(m_pGraphicDev); break;

	
	// Environment - New
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_TWINPEAKS:
		pClone = CTwinPeaks::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_DEATH_TREE:
		pClone = CDeathTree::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_TRIPLE_DEATH_TREE:
		pClone = CTripleDeathTree::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURAL_WORLD_TREE:
		pClone = CWorldTree::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_SWEETS1:
		pClone = CSweets1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_SWEETS2:
		pClone = CSweets2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURE_TOMBSTONE:
		pClone = CTombstone::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_NATURE_GRASS:
		pClone = CGrass1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_PIRATE_HIDEOUT:
		pClone = CPirateHideOut::Create(m_pGraphicDev); break;

	
	// Environment - Wall
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_WALL1:
		pClone = CWall1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_BUILDING_WALL2:
		pClone = CWall2::Create(m_pGraphicDev); break;


	// Environment - Sign
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_NOTICE:
		pClone = CNoticeBoard::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_ASTROPAW:
		pClone = CSignAstropaw::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_CATTRAP:
		pClone = CSignCattrap::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_FALME:
		pClone = CSignFlame::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_FREEZE:
		pClone = CSignFreeze::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_HEAL:
		pClone = CSignHeal::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_LIGHT:
		pClone = CSignLight::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_PURRSERK:
		pClone = CSignPurrserk::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_STOP:
		pClone = CSignStop::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_TWINTOWN:
		pClone = CSignTwinTown::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_FISH:
		pClone = CSignFish::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SIGN_WOODFISH:
		pClone = CSignWoodFish::Create(m_pGraphicDev); break;

	// Environment - Skull
	case Engine::OBJ_ID::ENVIRONMENT_SKULL_DRAGON1:
		pClone = CDragonSkull1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SKULL_DRAGON2:
		pClone = CDragonSkull2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_SKULL_DRAGON3:
		pClone = CDragonSkull3::Create(m_pGraphicDev); break;

	// Environment - Wreak
	case Engine::OBJ_ID::ENVIRONMENT_WRECK_SHIP:
		pClone = CWreckShip::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_WRECK_PIECE1:
		pClone = CWreckPiece1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_WRECK_PIECE2:
		pClone = CWreckPiece2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_WRECK_PIECE3:
		pClone = CWreckPiece3::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_WRECK_PIECE4:
		pClone = CWreckPiece4::Create(m_pGraphicDev); break;

	// Environment - Other
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_DRAKOTH_TABLE:
		pClone = CDrakothTable::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_POTION:
		pClone = CWorldPotion::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_PRESENT:
		pClone = CPresent::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_PAPER:
		pClone = CPaper::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ENVIRONMENT_OTHER_TOWN_SANCTUARY:
		pClone = CTownSanctuary::Create(m_pGraphicDev); break;

	
	/* ========================================= Monster ========================================*/


	// Monster
	case Engine::OBJ_ID::MONSTER_HEDGEHOG:
		pClone = CHedgehog::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::MONSTER_DRAGON:
		pClone = CDragon::Create(m_pGraphicDev);	 break;
	case Engine::OBJ_ID::MONSTER_BAT:
		pClone = CBat::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::MONSTER_RAM:
		pClone = CRam::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::MONSTER_FOX:
		pClone = CFox::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::MONSTER_SQUIRREL:
		pClone = CSquirrel::Create(m_pGraphicDev);	 break;
	case Engine::OBJ_ID::MONSTER_WYVERN:
		pClone = CWyvern::Create(m_pGraphicDev);	 break;

	case Engine::OBJ_ID::MONSTER_SERPENT:
		pClone = CSerpent::Create(m_pGraphicDev);	 break;
	case Engine::OBJ_ID::MONSTER_FISH:
		pClone = CFish::Create(m_pGraphicDev);	 break;
	case Engine::OBJ_ID::MONSTER_VIOLETDRAGON:
		pClone = CVioletDragon::Create(m_pGraphicDev);	 break;
	case Engine::OBJ_ID::MONSTER_WYVERNRED:
		pClone = CWyvernRed::Create(m_pGraphicDev);	 break;




	/* ========================================= Npc ========================================*/


	// Npc

	case Engine::OBJ_ID::NPC_BLACKSMITH:
		pClone = CNpc_BlackSmith::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::NPC_CITIZEN_1:
		pClone = CNpc_Citizen1::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::NPC_CITIZEN_2:
		pClone = CNpc_Citizen2::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::NPC_KING:
		pClone = CNpc_King::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::NPC_MAGE:
		pClone = CNpc_Mage::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::NPC_SOLLIDER:
		pClone = CNpc_Soldier::Create(m_pGraphicDev); break;


	case Engine::OBJ_ID::ITEM_GOLD:
		pClone = CGoldCoin::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ITEM_EXP:
		pClone = CExpCoin::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ITEM_KEY:
		pClone = CKey::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ITEM_WARRIOR:
		pClone = CWarriorWeapon::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ITEM_NINJA:
		pClone = CNinjaWeapon::Create(m_pGraphicDev); break;
	case Engine::OBJ_ID::ITEM_MAGE:
		pClone = CMageWeapon::Create(m_pGraphicDev); break;

	/* ========================================= Line ========================================*/


	// Line

	case Engine::OBJ_ID::LINE:
		pClone = CTerrainWorld::Create(m_pGraphicDev); break;

	default:
		break;
	}

	return pClone;
}