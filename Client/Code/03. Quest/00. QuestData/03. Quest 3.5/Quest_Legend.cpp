#include "stdafx.h"
#include "Quest_Legend.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "IndicatorUI.h"

#include "Dungeon_Temple.h"
#include "BingoChest.h"

#include "Npc_BlackSmith.h"

#include "FlagStart.h"
#include "TrapBigFist.h"
#include "TrapBigFistDust.h"

#include "Skill.h"
#include "Skill_Player_Beam.h"

#include "WarriorWeapon.h"

#include "SkillGetEffect.h"
#include "ShadeUI.h"

#include "MiniGameMgr_Bingo.h"

#include "CameraMgr.h"

#define	 BIGFIST_AMOUNT 4

CQuest_Legend::CQuest_Legend(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest_Legend::~CQuest_Legend()
{
}

void CQuest_Legend::Init(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Item Warrior
	CGameObject* pGameObject = CWarriorWeapon::Create(pGraphicDev);
	CEventMgr::GetInstance()->Add_Obj(L"�ɼ�Ŀ�� ����", pGameObject);
	m_vItemList.push_back(pGameObject);
	pGameObject->Set_Maintain(true);

	// Beam Skill
	CSkill* pSkill = CSkill_Player_Beam::Create(pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"������ġ", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	m_tQuestContent.push_back({ L"1.���� ����", false });
}

_bool CQuest_Legend::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	// ��ȭ ���� ���� ���� Ȯ��
	ePlayerState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState();
	m_bReadyTalk = (ePlayerState == STATE_TYPE::BACK_IDLE ||
		ePlayerState == STATE_TYPE::FRONT_IDLE) ? true : false;

	switch (m_iLevel)
	{
	case 0: // �������̿��� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));

					*_IsAble = true;
				}

				// �������̿��� �� �ɱ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 350, OBJ_ID::NPC_BLACKSMITH))
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
	case 1: // �� ã��
		m_bShowQuestView = true;
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			if (!*_IsAble)
			{
				dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
					dynamic_cast<CDungeon_Temple*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"Dungeon_Temple")));
				*_IsAble = true;
			}
		}
		// 
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_TEMPLE)
		{
			// ���� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite") != nullptr))
			{
				if (!*_IsAble)
				{
					if (!CMiniGameMgr_Bingo::GetInstance()->Get_IsInit())
					{
						CMiniGameMgr_Bingo::GetInstance()->Init(pGraphicDev);
					}

					m_tQuestContent[0].m_bClear = true;
					m_tQuestContent.push_back({ L"2.���� �����ϱ�", false });

					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(nullptr);
					
					*_IsAble = true;
				}

				// ��ȭ
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 360, OBJ_ID::NPC_SPIRIT))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite"), false);

						CMiniGameMgr_Bingo::GetInstance()->Set_GameReady();

						m_tQuestContent[1].m_bClear = true;
						m_tQuestContent.push_back({ L"3.�÷��� ����ϰ�\n������ ȹ���ϱ�", false });

						m_iLevel += 1;
						*_IsAble = false;
						m_bReadyNext = false;

						// Camera Action Bingo Start
						{
							/*cout << 1 << endl;
							_vec3 vPlayerPos = CManagement::GetInstance()->Get_Player()->Get_Transform()->Get_Info(INFO_POS);
							_vec3 vBingoCenterPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::FLAG, L"Flag_Start")->Get_Transform()->Get_Info(INFO_POS);
							vBingoCenterPos.z -= 10.f;

							CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vPlayerPos, vBingoCenterPos, TRUE);*/

							/*CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Lerp_FOV(
								0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tProj.FOV, CAM_FOV_BINGO, LERP_MODE::SMOOTHERSTEP);

							CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tDistanceLerp.Set_Lerp(
								0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance, CAM_DISTANCE_BINGO);*/
						}
						break;
					}
				}
			}
		}
		break;
	case 2: // ���� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_TEMPLE)
		{
			if (!*_IsAble)
			{
				// �� �� �ʱ�ȭ.
				m_pFlagStart = dynamic_cast<CFlagStart*>
					(CManagement::GetInstance()
						->Get_GameObject(OBJ_TYPE::FLAG, L"Flag_Start"));

				m_pFlagStart->Ready_Object();

				if (!m_pFlagStart->Is_Active())
				{
					m_pFlagStart->Set_Active(true);
				}
				// Start Flag Ȱ��.
				if (!dynamic_cast<CFlagStart*>(m_pFlagStart)->Get_IsShow())
					dynamic_cast<CFlagStart*>(m_pFlagStart)->Set_IsShow(true);

				*_IsAble = true;
			}

			CMiniGameMgr_Bingo::GetInstance()->Update(Engine::Get_TimeDelta(L"Timer_FPS65"));
			
			if (m_bReadyNext)
			{
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_BACK_TO_TOP);

				dynamic_cast<CFlagStart*>(m_pFlagStart)->Set_IsShow(false);
				dynamic_cast<CFlagStart*>(m_pFlagStart)->Set_Active(false);

				m_iLevel += 1;
				*_IsAble = false;
				m_bReadyNext = false;
				break;
			}
		}
		break;
	case 3: // ���� ȹ��
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::DUNGEON_TEMPLE)
		{
			if (dynamic_cast<CBingoChest*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"BingoChest"))->Get_IsCol() && 
				!dynamic_cast<CBingoChest*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"BingoChest"))->Get_IsOpen())
			{
				if (CInputDev::GetInstance()->Key_Down('E'))
				{
					// ��� ������
					m_pShadeUI = CShadeUI::Create(pGraphicDev);
					NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
					CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

					// ���� ȹ��
					m_pWeaponGetUI = CWeaponGetEffect::Create(pGraphicDev, m_vItemList[0]);
					NULL_CHECK_RETURN(m_pWeaponGetUI, E_FAIL);
					CEventMgr::GetInstance()->Add_Obj(L"pWeaponGetUI", m_pWeaponGetUI);
				
					// �ٽ� ������
					dynamic_cast<CBingoChest*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::ENVIRONMENT, L"BingoChest"))->Set_IsOpen();
				}
			}
			if (m_bReadyNext)
			{
				dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
					m_vItemList[0]);
				m_iLevel += 1;
				*_IsAble = false;
				m_bStartQuest = true;
				m_bReadyNext = false;
				m_tQuestContent[2].m_bClear = true;
			}
			break;
		}
		break;
	case 4:
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc�� ���� �Ѵٸ�
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith") != nullptr))
			{
				// �ε������� ����
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith")));

					*_IsAble = true;
				}

				// �������̿��� �� �ɱ�
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 351, OBJ_ID::NPC_BLACKSMITH))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						// ��� ������
						m_pShadeUI = CShadeUI::Create(pGraphicDev);
						NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);

						// ��ų ȹ��
						m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
						NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
						CEventMgr::GetInstance()->Add_Obj(L"SkillGetUI", m_pSkillGetUI);
					}
				}
				if (m_bReadyNext)
				{
					dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
						m_vSkillList[0]);
					m_iLevel += 1;
					m_bStartQuest = true;
					m_bReadyNext = false;
				}
				break;
			}
		}
		break;
	case 5:
		CMiniGameMgr_Bingo::GetInstance()->DestroyInstance();
		m_iLevel = 99;
		*_IsAble = false;
		m_bShowQuestView = false;
		return true;
		break;
	}

	return false;
}
