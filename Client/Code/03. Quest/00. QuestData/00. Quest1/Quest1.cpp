#include "stdafx.h"
#include "Quest1.h"

#include "Export_Function.h"

#include "Player.h"
#include "TalkMgr.h"
#include "Management.h"
#include "GraphicDev.h"

#include "IndicatorUI.h"

#include "Skill.h"
#include "Npc_BlackSmith.h"
#include "Skill_Player_Fire.h"

#include "SkillGetEffect.h"
#include "ShadeUI.h"

// test
#include "WeaponGetEffect.h"
#include "NinjaWeapon.h"

CQuest1::CQuest1(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_iKillCount(0)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuest1::~CQuest1()
{
}

void CQuest1::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	// Fire Skill
	CSkill* pSkill = CSkill_Player_Fire::Create(m_pGraphicDev, m_pPlayer);
	CEventMgr::GetInstance()->Add_Obj(L"������ �÷���", pSkill);
	m_vSkillList.push_back(pSkill);
	pSkill->Set_Maintain(true);

	// test
	// Item Ninja
	// CGameObject* pGameObject = CNinjaWeapon::Create(m_pGraphicDev);
	// CEventMgr::GetInstance()->Add_Obj(L"���ڳ��� ��Ʈ", pGameObject);
	// m_vItemList.push_back(pGameObject);
	// pGameObject->Set_Maintain(true);


	m_tQuestContent.push_back({ L"1. ����ġ 5���� óġ", false });

	m_iKillCount = 0;
}

_bool CQuest1::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
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
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 100, OBJ_ID::NPC_BLACKSMITH)) 
					{
						// test
						// ��� ������
						//m_pShadeUI = CShadeUI::Create(pGraphicDev);
						//NULL_CHECK_RETURN(m_pShadeUI, E_FAIL);
						//CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", m_pShadeUI);
						//
						//// ���� ȹ�� ����
						//m_pWeaponGetUI = CWeaponGetEffect::Create(pGraphicDev, m_vItemList[0]);
						//NULL_CHECK_RETURN(m_pWeaponGetUI, E_FAIL);
						//CEventMgr::GetInstance()->Add_Obj(L"pWeaponGetUI", m_pWeaponGetUI);

						//// ��ų
						//m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
						//NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
						//CEventMgr::GetInstance()->Add_Obj(L"pSkillGetUI", m_pSkillGetUI);

						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

						m_iLevel += 1;
						*_IsAble = false;
						break;
					}
					break;
				}
				// test
				//if (m_bReadyNext)
				//{
				//	//dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Item(
				//	//	m_vItemList[0]);
				//	dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
				//		m_vSkillList[0]);
				//
				//	m_bReadyNext = false;
				//	m_bStartQuest = true;
				//	m_iLevel += 1;
				//	break;
				//}


			}
		}
		break;

	case 1: // ����ġ 5���� ����
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			m_bShowQuestView = true;
			// ����ġ 5������ ��Ҵٸ�
			for (_int i = 0; i < CEventMgr::GetInstance()->Get_VecDeleteObj().size(); ++i)
			{
				if (CEventMgr::GetInstance()->Get_VecDeleteObj()[i]->Get_Name() == L"Monster_Hedgehog")
				{
					m_iKillCount += 1;
				}
			}
			if (m_iKillCount <= 5)
			{
				m_tQuestContent[0].m_strQuestContent = L"1.����ġ 5���� óġ  \n" + to_wstring(m_iKillCount) + L" / 5";
			}
			if (m_iKillCount >= 5)
			{
				{
					m_tQuestContent[0].m_strQuestContent = L"1. ����ġ 5���� óġ  \n�Ϸ�";
					m_tQuestContent[0].m_bClear = true;
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

						// ��ȭ �� ����
						if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"))->Get_IsCol()
							&& m_bReadyTalk)
						{
							if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 101, OBJ_ID::NPC_BLACKSMITH))
							{
								Set_ReadyTalk(CManagement::GetInstance()->
									Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith"), false);

								// ��� ������
								CShadeUI* pShadeUI = CShadeUI::Create(pGraphicDev);
								NULL_CHECK_RETURN(pShadeUI, E_FAIL);
								CEventMgr::GetInstance()->Add_Obj(L"ShadeUI", pShadeUI);

								// ��ų ȹ�� ����
								m_pSkillGetUI = CSkillGetEffect::Create(pGraphicDev, m_vSkillList[0]);
								NULL_CHECK_RETURN(m_pSkillGetUI, E_FAIL);
								CEventMgr::GetInstance()->Add_Obj(L"pSkillGetUI", m_pSkillGetUI);							
							}
						}
					}
					if (m_bReadyNext)
					{
						// ���� ��ų �κ��丮�� �߰�.
						dynamic_cast<CInventory*>(dynamic_cast<CPlayer*>(m_pPlayer)->Get_Inventory())->Add_Skill(
							m_vSkillList[0]);
						m_bStartQuest = true;
						m_bReadyNext = false;
						m_iLevel += 1;
					}
					break;
				}
			}
		}
		break;
	case 2:
			m_iLevel = 99;
			*_IsAble = false;
			m_bShowQuestView = false;
			return true;
		break;
	}

	return false;
}
