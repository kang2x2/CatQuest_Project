#include "stdafx.h"
#include "QuestData.h"

#include "IndicatorUI.h"
#include "EnterUI.h"
#include "Npc.h"

#include "Export_Function.h"

CQuestData::CQuestData() 
	: m_iLevel(0)
	, m_strQuestName(L"")
	, m_pPlayer(nullptr)
	, m_bShowQuestView(false)
	, m_bReadyNext(false)
	, m_bStartQuest(false)
	, m_bReadyTalk(false)
{
}

CQuestData::~CQuestData()
{
	Free();
}

void CQuestData::Set_ReadyTalk(CGameObject* _pNpc, _bool isTalk)
{
	if (isTalk)
	{
		dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, _pNpc->Get_Name()))->
			Set_ReadyTalk(true);
	}
	else
	{
		dynamic_cast<CNpc*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::NPC, _pNpc->Get_Name()))->
			Set_ReadyTalk(false);
		//if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"))
		//{
		//	dynamic_cast<CEnterUI*>
		//		(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"))
		//		->EnterUI_Off();
		//}
	}
}

void CQuestData::Free()
{
}
