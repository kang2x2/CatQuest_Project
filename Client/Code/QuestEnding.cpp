#include "stdafx.h"
#include "QuestEnding.h"

#include "Export_Function.h"

#include "TalkMgr.h"
#include "Scene_World.h"

#include "Player.h"
#include "Management.h"
#include "GraphicDev.h"

#include "Npc_King.h"

#include "IndicatorUI.h"

CQuestEnding::CQuestEnding(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
	: m_bEndingScene(false), m_iStayEndingTime(0)
{
	m_strQuestName = _QuestName;
	Init(m_pGraphicDev, _pPlayer);
}

CQuestEnding::~CQuestEnding()
{
}

void CQuestEnding::Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;

	m_tQuestContent.push_back({ L"사자왕에게 가자.", false });
}

_bool CQuestEnding::Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble)
{
	// 대화 가능 상태 여부 확인
	ePlayerState = dynamic_cast<CPlayer*>(m_pPlayer)->Get_StateM()->Get_CurState();
	m_bReadyTalk = (ePlayerState == STATE_TYPE::BACK_IDLE ||
		ePlayerState == STATE_TYPE::FRONT_IDLE) ? true : false;

	switch (m_iLevel)
	{
	case 0: // 사자왕에게 가기
		if (CManagement::GetInstance()->Get_CurScene()->Get_SceneType() == SCENE_TYPE::WORLD)
		{
			// Npc가 존재 한다면
			if ((CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::NPC, L"Npc_King") != nullptr))
			{
				// 인디케이터 설정
				if (!*_IsAble)
				{
					Set_ReadyTalk(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"), true);

					dynamic_cast<CIndicatorUI*>(_pIndicator)->Set_IndicTarget(
						dynamic_cast<CNpc*>(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King")));

					*_IsAble = true;
				}

				// 사자왕에게 말 걸기
				if (dynamic_cast<CNpc*>(CManagement::GetInstance()->
					Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"))->Get_IsCol()
					&& m_bReadyTalk)
				{
					if (CTalkMgr::GetInstance()->Get_Talk(pGraphicDev, 510, OBJ_ID::NPC_KING))
					{
						Set_ReadyTalk(CManagement::GetInstance()->
							Get_GameObject(OBJ_TYPE::NPC, L"Npc_King"), false);

						m_iLevel += 1;
						*_IsAble = false;
						m_iStayEndingTime = GetTickCount64() + 1200;
						break;
					}
				}
			}
		}
		break;
	case 1:
		dynamic_cast<CScene_World*>
			(CManagement::GetInstance()->Get_CurScene())->Finish_Game();
		break;
	}

	return false;
}
