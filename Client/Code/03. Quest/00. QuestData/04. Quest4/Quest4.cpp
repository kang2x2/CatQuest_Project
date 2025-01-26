#include "stdafx.h"
#include "Quest4.h"

#include "Export_Function.h"

#include "TalkMgr.h"
#include "BossSceneMgr.h"
#include "Scene_World.h"

#include "Player.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Citizen1.h"

#include "WeaponGetEffect.h"

CQuest4::CQuest4(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_bBossKill(false), m_bBossIntroScene(false), m_bBossOutScene(false)
	, m_bEndingScene(false)
	, m_iStayEndingTime(0), m_iMonsterCount(0)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest4::~CQuest4()
{
}

void CQuest4::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	m_tQuestContent.push_back({ L"1.바다 위 모든 몬스터 소탕", false });
}

_bool CQuest4::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	// 대화 가능 상태 여부 확인
	ePlayerState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState();
	m_bReadyTalk = (ePlayerState == STATE_TYPE::BACK_IDLE ||
		ePlayerState == STATE_TYPE::FRONT_IDLE) ? true : false;

	switch (m_iLevel)
	{
	case 0: // 대장장이와 대화
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 400, OBJ_ID::NPC_BLACKSMITH))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						multimap<const _tchar*, CGameObject*> tempMap
							= CManagement::GetInstance()->
							Get_CurScene()->
							Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();

						for (auto iter = tempMap.begin(); iter != tempMap.end(); ++iter)
						{
							if(iter->second->Get_Name() == L"Monster_Fish")
								m_iMonsterCount += 1;

							if (iter->second->Get_Name() == L"Monster_Serpent")
								m_iMonsterCount += 1;
						}

						m_iMonsterCount -= 5; // 임의로 빼줌. 5마리 제외

						m_iLevel += 1;
						*_IsAble = false;
						m_bShowQuestView = true;
						break;
					}
				}
			}
		}
		break;
	case 1: // 해상 전투
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 해상 몹 소탕 여부 검사
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Fish")
				{
					m_iMonsterCount -= 1;
				}
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Serpent")
				{
					m_iMonsterCount -= 1;
				}
			}
			// 모든 해상몹들을 잡았다면
			if (m_iMonsterCount <= 0)
			{
				m_tQuestContent[0].m_bClear = true;
				m_tQuestContent.push_back({ L"2. 죽음의 섬에 있는\n 정찰냥 만나기", false });
				m_tQuestContent[0].m_strQuestContent = L"1.바다 위 모든 몬스터 소탕\n완료";
				m_iLevel += 1;
				*_IsAble = false;
				break;
			}
			else
			{
				m_tQuestContent[0].m_strQuestContent = L"1.바다 위 모든 몬스터 소탕\n" 
					+ to_wstring(m_iMonsterCount) + L"마리 생존";

				//m_strQuestContent = L"남은 해상 몬스터 수 : " + to_wstring(m_iMonsterCount);
			}
		}
		break;
	case 2: // 보스전 돌입 전 NPC 대화
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 410, OBJ_ID::NPC_CITIZEN_1))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1"), false);

						m_tQuestContent[1].m_bClear = true;
						m_tQuestContent.push_back({ L"\n3.드래곤 처치", false });
					
						m_iLevel += 1;
						*_IsAble = false;
						m_bReadyNext = false;
						break;
					}
				}
			}
		}
		break;
	case 3: // 보스전
		if (!m_bBossIntroScene)
		{
			m_bBossIntroScene = true;
		}
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// 보스를 처치했다면
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_VioletDragon")
				{
					m_bBossKill = true;
				}
			}
			if (m_bBossKill)
			{
				m_tQuestContent[2].m_bClear = true;
				m_iLevel += 1;
				*_IsAble = false;
				break;
			}
		}

		break;
	case 4: 
		if (!m_bBossOutScene)
		{
			m_bBossOutScene = true;
		}
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(nullptr);
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 500, OBJ_ID::NPC_BLACKSMITH))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						m_tQuestContent.clear();
						m_tQuestContent.push_back({ L"엔딩\n 사자왕에게 가보자.", false });

						m_iLevel += 1;
						*_IsAble = false;
						m_bShowQuestView = true;
						break;
					}
				}
			}
		}
		break;
	case 5: // 엔딩
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")));
					*_IsAble = true;
				}

				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 510, OBJ_ID::NPC_KING))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"), false);

						dynamic_cast<CScene_World*>
							(CManagement::GetInstance()->Get_CurScene())->Finish_Game();
						
						m_iLevel += 1;
						*_IsAble = false;

						break;
					}
				}				
			}
		}
		break;
	}

	return false;
}
