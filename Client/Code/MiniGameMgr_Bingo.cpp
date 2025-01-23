#include "stdafx.h"
#include "..\Header\MiniGameMgr_Bingo.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "SoundMgr.h"

#include "FlagOwner.h"
#include "Bingo_Launcher.h"

#include "Bingo_SuccesUI.h" // UI
#include "Bingo_Succes.h" // Effect
#include "Bingo_FailUI.h"
#include "Bingo_ClearUI.h"

#include "QuestMgr.h"
#include "Zeolite.h"
#include "CameraMgr.h"

#include "TrapFist.h"


IMPLEMENT_SINGLETON(CMiniGameMgr_Bingo)

CMiniGameMgr_Bingo::CMiniGameMgr_Bingo()
	: m_bActive(false), m_bInit(false), m_bStart(false), m_bShuffle(false)
	, m_bShowFlag(false), m_bShowAgain(false), m_bFirstSound(false)
	, m_bPushVec(false), m_bGameClear(false), m_bGameOver(false)
	, m_bGameReady(false), m_bDropFist(false)
	, m_iIndex(0), m_iLevel(1), m_iShowIndex(0), m_iBingoCount(0), m_iSetIndex(7)
{
}

CMiniGameMgr_Bingo::~CMiniGameMgr_Bingo()
{

}

HRESULT CMiniGameMgr_Bingo::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_pGraphicDev = _pGraphicDev;

	// 국기 주인
	m_pFlagOwner = CFlagOwner::Create(m_pGraphicDev, OBJ_ID::FLAG_OWNER);
	NULL_CHECK_RETURN(m_pFlagOwner, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pFlagOwner->Get_Name(), m_pFlagOwner), E_FAIL);
	
	//// 빙고 장치
	//m_pLauncher = CBingo_Launcher::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(m_pLauncher, E_FAIL);
	//FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(m_pLauncher->Get_Name(), m_pLauncher), E_FAIL);


	// 국기들 저장.
	m_FlagVector = m_pFlagOwner->Get_FlagVector();
	// 가운데 칸만 따로 저장.
	m_pStartFlag = dynamic_cast<CFlagStart*>(m_FlagVector.back());

	// 원할한 진행을 위해 국기 저장 벡터에서 마지막 요소(가운데 칸) 제거.
	m_FlagVector.pop_back();

	m_tGameOverLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tGameOverLerp.Set_Lerp(5.5f, 0.1f, 1.f);

	m_bInit = true;

	return S_OK;
}

void CMiniGameMgr_Bingo::Update(const _float& _fDelta)
{
	if (m_bGameClear && !m_bGameOver)
	{
		m_tGameOverLerp.Update_Lerp(_fDelta);
		if (!m_tGameOverLerp.bActive)
		{
			m_iLevel += 1;
			m_bGameOver = true; // 지금 if문 무한 반복 방지
		}
	}

	// 다시 보여주기
	if (m_bShowAgain)
	{
		m_tShowAgainLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));
		if (!m_tShowAgainLerp.bActive)
		{
			if (m_bFirstSound)
			{
				CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
				m_bFirstSound = false;
			}
			ShowFlag();
		}
	}

	// 다채로운 랜덤 값
	srand(unsigned int(time(0)));

	// 스위치 켜지면 한 번만 초기화.
	if (m_bActive && !m_bStart)
	{
		if (!m_bPushVec)
		{
			for (_int i = 0; i < m_FlagVector.size(); ++i)
			{
				m_FlagVector[i]->Ready_Object();
				m_FlagVector[i]->Set_Active(true);
			}

			m_bPushVec = true;
		}

		// 알파 보간 등장
		if (!m_FlagVector[m_iSetIndex]->Get_Create())
		{
			CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
			m_FlagVector[m_iSetIndex]->Set_Create();
		}
		if (m_FlagVector[m_iSetIndex]->Get_Translucent() >= 255.f)
		{
			m_iSetIndex -= 1;
			if (m_iSetIndex < 0)
			{
				// 최초 시작
				m_tShowAgainLerp.Init_Lerp(LERP_MODE::EASE_IN);
				m_tShowAgainLerp.Set_Lerp(3.5f, 1.f, 0.f);
				m_bShowAgain = true;
				m_bFirstSound = true;
				m_iSetIndex = 0;

				m_bStart = true;

				// Camera Action Bingo Start
				{
					_vec3 vPlayerPos = CManagement::GetInstance()->Get_Player()->Get_Transform()->Get_Info(INFO_POS);
					_vec3 vBingoCenterPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::FLAG, L"Flag_Start")->Get_Transform()->Get_Info(INFO_POS);
					vBingoCenterPos.z -= 10.f;

					//CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vPlayerPos, vBingoCenterPos, TRUE);
					
					CCameraMgr::GetInstance()->Get_CurCamera()->Set_FlightView(TRUE);

					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Lerp_FOV(
						0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tProj.FOV, CAM_FOV_BINGO, LERP_MODE::SMOOTHERSTEP);

					CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tDistanceLerp.Set_Lerp(
						0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance, CAM_DISTANCE_BINGO);
				}
			}
		}
	}

	// 게임 실행 
	if (m_bActive)
	{
		// 한번 삽입.
		if (!m_bShuffle)
		{
			// 레벨에 따른 빙고카운트
			switch (m_iLevel)
			{
			case 1:
				m_iBingoCount = 1;
				break;
			case 2:
				m_iBingoCount = 3;
				break;
			case 3:
				m_iBingoCount = 5;
				break;
			case 4:
				m_iBingoCount = 7;
				break;
			}

			// 빙고 카운트만큼 담기
			if (!m_bGameClear)
			{
				for (_int i = 0; i < m_iBingoCount; ++i)
				{
					int iRand = rand() % m_FlagVector.size();
					m_BingoVector.push_back(m_FlagVector[iRand]);
				}
				m_bShuffle = true;

				m_tFlagShowLerp.Init_Lerp(LERP_MODE::EASE_IN);
				m_tFlagShowLerp.Set_Lerp(1.f, 1.f, 0.f);
			}
		}

		if (m_bGameOver)
		{
			// 알파 보간 소멸
			if (!m_FlagVector[m_iSetIndex]->Get_Delete())
			{
				CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
				m_FlagVector[m_iSetIndex]->Set_Delete();
			}

			if (m_FlagVector[m_iSetIndex]->Get_Translucent() <= 0.f)
			{
				m_iSetIndex += 1;
				if (m_iSetIndex >= m_FlagVector.size())
				{
					// 게임 종료
					for (_int i = 0; i < m_FlagVector.size(); ++i)
					{
						m_FlagVector[i]->Ready_Object();
						m_FlagVector[i]->Set_Active(false);
					}

					m_bStart = false;
					m_bActive = false;
					// Start Flag 비표시
					m_pStartFlag->Set_IsShow(false);

					// 막고 있는 장애물 지우기
					if (!dynamic_cast<CZeolite*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite"))->
						Get_IsDelete())
					{
						dynamic_cast<CZeolite*>(CManagement::GetInstance()->
						Get_GameObject(OBJ_TYPE::NPC, L"Npc_Zeolite"))->
						Set_IsDelete();
					}

					// Camera Action  Bingo End
					{
						
						_vec3 vPlayerPos = CManagement::GetInstance()->Get_Player()->Get_Transform()->Get_Info(INFO_POS);
						_vec3 vBingoCenterPos = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::FLAG, L"Flag_Start")->Get_Transform()->Get_Info(INFO_POS);
						vBingoCenterPos.z -= 10.f;
						
						//CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, vBingoCenterPos, vPlayerPos, FALSE);

						CCameraMgr::GetInstance()->Get_CurCamera()->Set_FlightView(FALSE);

						CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Lerp_FOV(
							0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tProj.FOV, CAM_FOV_DEFAULT, LERP_MODE::SMOOTHERSTEP);

						CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_tDistanceLerp.Set_Lerp(
							0.8f, CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance, CAM_DISTANCE_DEFAULT);
					}

					// CQuestMgr::GetInstance()->Set_ReadyNext();
				}
			}
		}

		// 주먹 연타
		if (m_bDropFist && !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"Bingo_FailUI"))
		{
			m_tFistWaveLerp.Update_Lerp(_fDelta);
			m_tFistCreateLerp.Update_Lerp(_fDelta);
			if (!m_tFistCreateLerp.bActive)
			{
				CSoundMgr::GetInstance()->PlaySound(L"woosh.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_DROP_FIST);
				CGameObject* m_pFist = CTrapFist::Create(m_pGraphicDev);
				NULL_CHECK(m_pFist, E_FAIL);
				CEventMgr::GetInstance()->Add_Obj(L"TrapFist", m_pFist);
				m_tFistCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
				m_tFistCreateLerp.Set_Lerp(0.05f, 1.f, 0.f);
			}

			if (!m_tFistWaveLerp.bActive)
			{
				m_tShowAgainLerp.Init_Lerp(LERP_MODE::EASE_IN);
				m_tShowAgainLerp.Set_Lerp(4.5f, 1.f, 0.f);
				m_bShowAgain = true;
				m_bFirstSound = true;
				m_bDropFist = false;
			}
		}

		if (m_bShowFlag && !m_bGameClear)
		{
			ShowFlag();
		}
	}
}

void CMiniGameMgr_Bingo::ShowFlag()
{
	if (m_iShowIndex < m_iBingoCount)
	{
		m_tFlagShowLerp.Update_Lerp(Engine::Get_TimeDelta(L"Timer_FPS65"));

		m_pStartFlag->Set_Texture(
			dynamic_cast<CFlag*>(m_BingoVector[m_iShowIndex])->Get_FlagTag());

		if (!m_tFlagShowLerp.bActive)
		{
			m_pStartFlag->Set_Texture(FLAG_TAG::FLAG_START);
			m_tFlagShowLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFlagShowLerp.Set_Lerp(0.8f, 1.f, 0.f);
			m_iShowIndex += 1;

			if (m_iShowIndex < m_iBingoCount)
			{
				CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_SHOW_SOUND);
			}
		}
	}
	else
	{
		m_pStartFlag->Set_Texture(FLAG_TAG::FLAG_START);
		m_bShowFlag = false;
		m_bShowAgain = false;
		m_iShowIndex = 0;
	}

}

HRESULT CMiniGameMgr_Bingo::Flag_Check(const OBJ_ID& _eID)
{
	if (m_bStart)
	{
		if (m_BingoVector[m_iIndex]->Get_ID() == _eID)
		{
			// 전부 맞추면 
			if (m_iIndex >= m_iBingoCount - 1)
			{
				if (m_iLevel < 4) // 클리어하자마자 레벨이 바로 오르는게 아님
				{
					CSoundMgr::GetInstance()->PlaySound(L"Bingo_AllSucces.mp3", CHANNEL_ID::ENVIRONMENT_0, BINGO_CLEAR_SOUND);

					CGameObject* pUI = CBingo_SuccesUI::Create(m_pGraphicDev);
					NULL_CHECK_RETURN(pUI, E_FAIL);
					CEventMgr::GetInstance()->Add_Obj(L"Bingi_SuccesUI", pUI);

					m_tShowAgainLerp.Init_Lerp(LERP_MODE::EASE_IN);
					m_tShowAgainLerp.Set_Lerp(4.5f, 1.f, 0.f);
					m_bShowAgain = true;
					m_bFirstSound = true;

					// m_pLauncher->Set_ShowReady(true);

					m_iIndex = 0;
					m_iLevel += 1;
					m_BingoVector.clear();
					m_bShuffle = false;
				}
				else if (m_iLevel >= 4) // 클리어 시점에 4레벨이라면
				{
					CSoundMgr::GetInstance()->PlaySound(L"Quest Complete.wav", CHANNEL_ID::ENVIRONMENT_0, BINGO_ALLCLEAR_SOUND);

					CGameObject* pUI = CBingo_ClearUI::Create(m_pGraphicDev);
					NULL_CHECK_RETURN(pUI, E_FAIL);
					CEventMgr::GetInstance()->Add_Obj(L"Bingo_ClearUI", pUI);

					m_bGameClear = true;
				}
			}
			else
			{
				// Effect Create
				CGameObject* pSucces = CBingoSucces::Create(m_pGraphicDev,
					CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));
				NULL_CHECK_RETURN(pSucces, E_FAIL);
				CEventMgr::GetInstance()->Add_Obj(L"SuccesEffect", pSucces);

				CSoundMgr::GetInstance()->PlaySound(L"Bingo_Succes.mp3", CHANNEL_ID::ENVIRONMENT_1, BINGO_SUCCES_SOUND);
				m_iIndex += 1;
			}
		}
		else
		{
			m_tFistWaveLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFistWaveLerp.Set_Lerp(5.f, 1.f, 0.f);
			m_tFistCreateLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tFistCreateLerp.Set_Lerp(0.05f, 1.f, 0.f);
			m_bDropFist = true;

			CSoundMgr::GetInstance()->PlaySound(L"Bingo_Fail.mp3", CHANNEL_ID::ENVIRONMENT_2, BINGO_FAIL_SOUND);
			CGameObject* pUI = CBingo_FailUI::Create(m_pGraphicDev);
			NULL_CHECK_RETURN(pUI, E_FAIL);
			CEventMgr::GetInstance()->Add_Obj(L"Bingo_FailUI", pUI);

			// m_pLauncher->Set_ShowReady(true);
			m_iIndex = 0;
		}
	}

	return S_OK;
}

void CMiniGameMgr_Bingo::Free()
{
}
