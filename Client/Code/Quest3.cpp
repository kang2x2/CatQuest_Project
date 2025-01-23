#include "stdafx.h"
#include "Quest3.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"
#include "IndicatorUI.h"

#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Mage.h"
// 현재는 빌딩 나중에는 포탈을 추가해야 한다.
#include "Tower2.h"

#include "MageWeapon.h"
#include "Skill_Player_Ice.h"
#include "Skill_Player_Fly.h"
#include "Key.h"
#include "WorldFlight.h"

#include "MiniGameMgr_Jump.h"
#include "SkillGetEffect.h"
#include "WeaponGetEffect.h"
#include "ShadeUI.h"

CQuest3::CQuest3(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest3::~CQuest3()
{
	if (m_pWorldFlight)
	{
		Safe_Release(m_pWorldFlight);
	}
}

void CQuest3::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fly Skill
	CSkill* pSkill = CSkill_Player_Fly::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"냥다람쥐", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Ice Skill
	pSkill = CSkill_Player_Ice::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"꽁꽁 꾹꾹이", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// Item Mage
	CGameObject* pGameObject = CMageWeapon::Create(m_pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"매직냥 스태프", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1.경비냥 만나기.", false });

	m_bCreateQItem = false;
	m_pWorldFlight = nullptr;
}

_bool CQuest3::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	// 대화 가능 상태 여부 확인
	ePlayerState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState();
	m_bReadyTalk = (ePlayerState == STATE_TYPE::BACK_IDLE ||
		ePlayerState == STATE_TYPE::FRONT_IDLE) ? true : false;


	// 퀘스트 아이템
	// 퀘스트 단계가 4단계이고 월드에 키가 생성이 안됐을 때 + (중복 생성 방지)
	if (m_iLevel == 3 && !m_bCreateQItem &&
		CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
	{
		m_pWorldFlight = CWorldFlight::Create(pGraphicDev);
		CEventMgr::GetInstance()->Add_Obj(L"Item_WorldFlight", m_pWorldFlight);
		m_bCreateQItem = true;
	}
	// 씬 이동시 m_bCreateKey false로 변경. 차피 알아서 지워줌.
	if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() != SCENE_TYPE::WORLD)
	{
		m_bCreateQItem = false;
	}
	///////////////////////////////////////


	switch (m_iLevel)
	{
	case 0: // 대장장이와 대화(군인 캠 이벤트)
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_SWAMP)
		{
			if (!*_IsAble)
			{
				dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
					dynamic_cast<CTower2*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Tower2")));
				*_IsAble = true;
			}
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

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));
					*_IsAble = true;
				}

				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
					_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier")->Get_Transform()->Get_Info(INFO_POS);

					if (CTalkMgr::GetInstance()->Get_CamTalk(
						pGraphicDev, 300, OBJ_ID::NPC_BLACKSMITH, 3, vPlayerPos, vTargetPos))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 1: // 군인과 대화
		m_bShowQuestView = true;
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier") != nullptr))
			{
				// 인디케이터 설정
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier")));
					*_IsAble = true;
				}
				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					_vec3 vPlayerPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player")->Get_Transform()->Get_Info(INFO_POS);
					_vec3 vTargetPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")->Get_Transform()->Get_Info(INFO_POS);

					if (CTalkMgr::GetInstance()->Get_CamTalk(
						pGraphicDev, 310, OBJ_ID::NPC_SOLLIDER, 2, vPlayerPos, vTargetPos))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier"), false);

						m_tQuestContent[0].m_bClear = true;
						m_tQuestContent.push_back({ L"2.점프맵 통과하여\n마법냥 만나기.", false });
						m_iLevel += 1;
						*_IsAble = false;
						// 시작
						CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_TOP_TO_BACK);
						CMiniGameMgr_Jump::GetInstance()->Start_MiniGame(); // 미니게임 시작
						break;
					}
				}
			}
		}
		break;
	case 2: // 마법사에게 향하기
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage") != nullptr))
			{
				// 인디케이터 설정
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")));
					*_IsAble = true;
				}
				// 대화 후 다음 단계
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 320, OBJ_ID::NPC_MAGE))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"), false);

						m_tQuestContent[1].m_bClear = true;
						m_tQuestContent.push_back({ L"\n3.마법냥의 열쇠 찾아주기.", false });
						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
				}
			}
		}
		break;
	case 3: // 열쇠 찾기
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (m_pWorldFlight)
			{
				if (dynamic_cast<CWorldFlight*>(m_pWorldFlight)->Get_IsCol()
					&& CInputDev::GetInstance()->Key_Down('E'))
				{
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveQuestItem(true);
					dynamic_cast<CWorldFlight*>(m_pWorldFlight)->Set_IsDelete();
					m_iLevel += 1;
					break;
				}
			}
		}	

		break;
	case 4:
		// 마법사에게 열쇠 가져다 주기
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage") != nullptr))
			{
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage")));
					*_IsAble = true;
				}
		
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"))->Get_IsCol() &&
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Get_HaveKey() >= 1
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 321, OBJ_ID::NPC_MAGE)) {
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Mage"), false);

						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Set_HaveQuestItem(false);
						// 배경 검은색
						m_pShadeUI = CShadeUI::Create(pGraphicDev);
						NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

						// 스킬 획득
						m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
						NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"SkillGetUI", m_pSkillGetUI);
					}
				}
				if (m_bReadyNext)
				{
					dynamic_cast<CPlayer*>(dynamic_cast<CPlayer*>(m_pPlayer))->Set_HasFlight(true);
					m_iLevel += 1;
					m_bStartQuest = true;
					m_bReadyNext = false;
					*_IsAble = false;
					break;
				}
			}
		}
		break;
	case 5: // 대장장이에게 복귀
		m_tQuestContent[2].m_bClear = true;

		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				// 인디케이터 설정
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
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 301, OBJ_ID::NPC_BLACKSMITH))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						// 배경 검은색
						m_pShadeUI = CShadeUI::Create(pGraphicDev);
						NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

						// 스킬 획득
						m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[1]);
						NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"SkillGetUI", m_pSkillGetUI);
					}
				}
			}
			if (m_bReadyNext)
			{
				dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
					m_vSkillList[1]);
				m_iLevel += 1;
				m_bStartQuest = true;
				m_bReadyNext = false;
			}
			break;
		}

		break;

	case 6:// 아이템 1 획득
		if (m_bStartQuest)
		{
			// 배경 검은색
			m_pShadeUI = CShadeUI::Create(pGraphicDev);
			NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

			// 무기 획득
			m_pWeaponGetUI = CWeaponGetEffect::Create(pGraphicDev, m_vItemList[0]);
			NULL_CHECK_RETURN(m_pWeaponGetUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"pWeaponGetUI", m_pWeaponGetUI);

			m_bStartQuest = false;

		}
		if (m_bReadyNext)
		{
			dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
				m_vItemList[0]);
			m_iLevel += 1;
			m_bStartQuest = true;
			m_bReadyNext = false;
		}
		break;

	case 7:
		m_iLevel = 99;
		*_IsAble = false;
		m_bShowQuestView = false;
		return true;
		break;
	}

	return false;
}
