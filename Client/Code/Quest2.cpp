#include "stdafx.h"
#include "Quest2.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Citizen2.h"
#include "Dungeon_Grass.h"

#include "NinjaWeapon.h"
#include "Skill_Player_Thunder.h"
#include "Key.h"

#include "SkillGetEffect.h"
#include "ItemGetEffect.h"
#include "ShadeUI.h"


CQuest2::CQuest2(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest2::~CQuest2()
{
}

void CQuest2::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fire Skill
	CSkill* pSkill = CSkill_Player_Thunder::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"라이트 냥", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Item Ninja
	CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"닌자냥이 세트", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1.던전 내 모든 몬스터 소탕", false });
	m_tQuestContent.push_back({ L"2.모두 소탕 후 던전 내 \n조사냥이 찾기", false });
}

_bool CQuest2::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
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

				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol())
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 200, OBJ_ID::NPC_BLACKSMITH)) {
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);
						
						m_iLevel += 1;
						*_IsAble = false;
						m_bReadyNext = false;
						break;
					}
				}
			}
		}
		break;
	case 1: // 던전 몬스터 모두 소탕하기!
		m_bShowQuestView = true;
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (!*_IsAble)
			{
				dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
					dynamic_cast<CDungeon_Grass*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Grass")));
				*_IsAble = true;
			}
		}

		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			if (CManagement::GetInstance()->
				Get_CurScene()->
				Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().empty())
			{
				m_tQuestContent[0].m_strQuestContent = L"1.던전 내 모든 몬스터 소탕\n완료";
				m_tQuestContent[0].m_bClear = true;
				// Npc가 존재 한다면
				if ((CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2") != nullptr))
				{
					// 인디케이터 설정
					if (!*_IsAble)
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"), true);

						dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
							dynamic_cast<CNpc*>(CManagement::GetInstance()->
								Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2")));
						
						*_IsAble = true;
					}
					// 대화 후 보상
					if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"))->Get_IsCol()
						&&m_bReadyTalk)
					{
						if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 201, OBJ_ID::NPC_CITIZEN_1))
						{
							Set_ReadyTalk(CManagement::GetInstance()->
								Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen2"), false);

							// 배경 검은색
							m_pShadeUI = CShadeUI::Create(pGraphicDev);
							NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
							CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

							// 스킬 획득 연출
							m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
							NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
							CEventMgr::GetInstance()->Add_Obj(L"pSkillGetUI", m_pSkillGetUI);							
						}
					}
					if (m_bReadyNext)
					{
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
							m_vSkillList[0]);
						m_bReadyNext = false;
						m_bStartQuest = true;
						m_iLevel += 1;
						break;
					}
				}
			}
			else
			{
				m_tQuestContent[0].m_strQuestContent = L"1.던전 내 모든 몬스터 소탕\n" + to_wstring(CManagement::GetInstance()->
					Get_CurScene()->
					Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap().size()) + L"마리 생존";
			}

		}
		break;
	case 2: // 아이템 1 획득
		if (m_bStartQuest)
		{
			// 배경 검은색
			m_pShadeUI = CShadeUI::Create(pGraphicDev);
			NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

			// 무기 획득 연출
			m_pWeaponGetUI = CWeaponGetEffect::Create(pGraphicDev, m_vItemList[0]);
			NULL_CHECK_RETURN(m_pWeaponGetUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"pWeaponGetUI", m_pWeaponGetUI);

			m_bStartQuest = false;
		}

		if (m_bReadyNext)
		{
			dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
				m_vItemList[0]);
			m_bReadyNext = false;
			m_bStartQuest = true;
			m_iLevel += 1;
		}
		break;
	case 3:
		m_iLevel = 99;
		*_IsAble = false; 
		m_bShowQuestView = false;
		return true;
		break;
	}

	return false;
}
