#include "stdafx.h"
#include "TalkMgr.h"

#include "Export_Function.h"

#include "DialogUI.h"
#include "EventMgr.h"
#include "QuestMgr.h"
#include "SoundMgr.h"

#include "Npc_King.h"
#include "Npc_Mage.h"
#include "Npc_BlackSmith.h"
#include "Npc_Soldier.h"
#include "Npc_Citizen1.h"
#include "Npc_Citizen2.h"

#include "EnterUI.h"

#include "MiniGameMgr_Jump.h"
#include "Player.h"


#define TALK_SOUND 1.f
#define MEOW_SOUND 1.f


IMPLEMENT_SINGLETON(CTalkMgr)


CTalkMgr::CTalkMgr()
	:m_bTargetCam(false), m_bStaySet(false), m_bReturnCam(false), m_bTalkEnd(false), m_iStayTime(0)
{
}

CTalkMgr::~CTalkMgr()
{
}

void CTalkMgr::Init()
{
	m_iTalkIndex = 0;

#pragma region Quest1 : 대장장이의 부탁
	// Quest1 : 대장장이의 부탁
	// 대장장이
	m_mapTalkData.insert(make_pair(100, vector<wstring>{
		{ L"안녕! \n우리 마을에 잘 왔어!"},
		{ L"너도 드래곤의 소문을 듣고 물리치러 온거야? \n그렇다면 환영이야." },
		{ L"하루 빨리 처치하지 않으면 다시 재앙이 \n찾아올테니까!"},
		{ L"아. 나는 앞으로 너를 도와줄 제임스라고 해!"},
		{ L"아쉽게도 드래곤에 대한 정보는 \n아직 모으고 있는 중이야."},
		{ L"그동안 저 아래쪽에 있는 고슴도치들을 \n혼내줬으면 좋겠어!"}
		}));
	// 대장장이
	m_mapTalkData.insert(make_pair(101, vector<wstring>{
		{ L"고슴도치들을 혼내줬구나!"},
		{ L"이걸로 녀석들도 이전처럼 활개치진 못 할거야." },
		{ L"고마워! 이건 우리집에 대대로 있던 스킬북이야." },
		{ L"니가 가져가주면 드래곤을 처치하는 데 \n도움이 되겠지!"}
	}));
#pragma endregion
#pragma region Quest2 : 던전 정리
// Quest2 : 던전 정리
// 대장장이
	m_mapTalkData.insert(make_pair(200, vector<wstring>{
		{ L"다음은 던전에 들어가서 몬스터들을 \n모두 소탕해주지 않을래?"},
		{ L"연구냥이 안에서 생태를 조사 중인데 \n 몬스터가 너무 많아서 쉽지 않나봐."},
		{ L"모두 소탕하면 안에서 조사중인 \n연구냥에게 보고해줘."},
		{ L"그동안 나는 드래곤에 관한 정보를 모아둘게."}
	}));

	// 시티즌(2)
	m_mapTalkData.insert(make_pair(201, vector<wstring>{
		{ L"몬스터를 모두 소탕하셨네요!"},
		{ L"정말 감사합니다. 조사하기 편해졌네요."},
		{ L"그리고 이것들은 이곳에서 사라져버린\n 어떤 고양이의 유품일까요?" },
		{ L"이런게 떨어져 있더라구요." },
		{ L"저보단 당신께 더 도움이 될 거 같으니 \n가져가세요!" }
	}));
	//

#pragma endregion
#pragma region Quest3 : 드래곤에게 향하기 위해서
// Quest3 : 드래곤에게 향하기 위해서
	// 대장장이
	m_mapTalkData.insert(make_pair(300, vector<wstring>{
		{ L"드래곤 수색대에게 연락이 왔어!"},
		{ L"드래곤은 죽음의섬에 있고 죽음의 섬에 \n 가기 위해선 날 수 있어야 해!"},
		{ L"얼음섬에 살고 있는 검은 마법냥라면 \n날 수 있는 방법을 알고 있을 것 같아."},
		{ L"얼음섬으로 가는 방법은 북쪽 해안가에 있는 \n경비냥이 알고 있을거야."},
		{ L"힘내!" }
	}));

	m_mapTalkData.insert(make_pair(301, vector<wstring>{
		{ L"니가 날아서 오는게 여기서도 보이던데!"},
		{ L"역시 너라면 해낼 줄 알았어!" },
		{ L"그리고 니가 얼음섬에 가 있는 동안 \n이런걸 찾았어." },
		{ L"부디 요긴하게 써줘!" }
	}));


	// 군인
	m_mapTalkData.insert(make_pair(310, vector<wstring>{
		{ L"검은 마법냥을 만나러 얼음섬에 가신다구요?"},
		{ L"검은 마법냥은 얼음섬에 있긴 합니다만.." },
		{ L"보시다시피 정상적인 길은 없고 뛰어서 가셔야 됩니다." },
		{ L"조심해서 다녀오세요!" }
	}));
	// 마법사
	m_mapTalkData.insert(make_pair(320, vector<wstring>{
		{ L"손님이 찾아오다니.. 반갑네."},
		{ L"하늘을 날고 싶다고? \n하늘을 날기위해선 플라잉 오브가 필요해." },
		{ L"얼음섬 어딘가에 있는 플라잉 오브를 찾아와." },
		{ L"그럼 날 수 있게 해주지." }
	}));
	m_mapTalkData.insert(make_pair(321, vector<wstring>{
		{ L"진짜로 찾아왔군."},
		{ L"좋아. 하늘을 날 수 있게 해주지." },
		{ L"이제 하늘을 마음껏 날아보도록!"}
	}));
	//

#pragma endregion
#pragma region Quest3.5 : 전설
// Quest3.5 : 전설
	// 대장장이
	m_mapTalkData.insert(make_pair(350, vector<wstring>{
		{ L"또 다른 정보를 얻었는데 고대의 드래곤 블러드가 \n사용하던 보물이 동쪽 섬의 사원에 잠들어 있나봐!"},
		{ L"그 보물을 얻는다면 과거 드래곤 블러드의 \n강력한 힘을 얻을 수 있을거야!" },
		{ L"고양이들은 물을 싫어해서 건너질 못하는데. \n너는 날 수 있으니까 갈 수 있을거야!"},
		{ L"실제로 존재하는 진 모르겠지만 얻게 되면 \n나에게도 보여 달라구!"}
	}));

	m_mapTalkData.insert(make_pair(351, vector<wstring>{
		{ L"그게 전설의 보물인거야? \n실제로 존재했구나. 멋진걸?"},
		{ L"니가 유적에 가 있는 동안 새로운 스킬북을 찾았어! \n이것도 너한테 줄게."},
		{ L"좋아. 나도 죽음의 섬에 잠복 중인 정찰냥에게 \n연락을 해볼테니 잠시 뒤에 와줘!" }
	}));

	// 고대 문구
	m_mapTalkData.insert(make_pair(360, vector<wstring>{
		{ L"보물을 얻기 위해서는 힘과 지혜가 필요하다."},
		{ L"여기까지 왔다면 힘은 증명 된 것이다."},
		{ L"지혜를 증명해 보아라. 그럼 문이 열릴지니." }
	}));
#pragma endregion
#pragma region Quest4 : 죽음의 섬으로
// Quest4 : 죽음의 섬으로
// 대장장이
	m_mapTalkData.insert(make_pair(400, vector<wstring>{
		{ L"드디어 모든 준비가 끝났구나."},
		{ L"마침 정찰병에게 연락을 받았어. \n드래곤이 죽음의 섬 둥지에 있는 모양이야."},
		{ L"이제 죽음의 섬으로 날아가서 \n정찰냥을 만나면 될거야."},
		{ L"아마 가는 도중 해상에 있는 \n몬스터들의 방해가 있을거야."},
		{ L"해상 위의 모든 몬스터를 처치하고 \n정찰병에게 가줘."},
		{ L"꼭 살아서 다시 만나자!"}
	}));

	// 시티즌(1)
	m_mapTalkData.insert(make_pair(410, vector<wstring>{
		{ L"기다리고 있었습니다."},
		{ L"이 앞에 사악한 드래곤이 있습니다."},
		{ L"많은 고양이들이 희생 됐습니다. \n부디 조심하십시오."},
		{ L"건투를 빕니다!"}
	}));
	//

#pragma endregion
#pragma region Quest5 : 엔딩
// Quest5 : 엔딩
	// 대장장이
	m_mapTalkData.insert(make_pair(500, vector<wstring>{
		{ L"드래곤을 물리쳤구나!"},
		{ L"정말 고마워! \n덕분에 마을에 평화가 찾아왔어!" },
		{ L"여기서 아래쪽에 있는 작은 섬에서 사자왕께서 \n기다리고 소식을 기다리고 계서."},
		{ L"사자왕께 얼른 가봐!" }
	}));

	// 사자왕
	m_mapTalkData.insert(make_pair(510, vector<wstring>{
		{ L"그대가 드래곤 블러드인가."},
		{ L"덕분에 나라가 평화를 찾을 수 있게 되었구나."},
		{ L"우리는 그대의 활약을 절대 잊지 않을 것이네."},
		{ L"다시 한번 감사를 표하네. \n위대한 드래곤 블러드여."}
	}));
	//

#pragma endregion

	m_bInit = true;
}

_bool CTalkMgr::Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID)
{	
	auto iter = m_mapTalkData.find(_iTalkID);

	if (&iter)
	{
		if (CInputDev::GetInstance()->Key_Down('E')
			&& !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"ShadeUI"))
		{
			if(m_iTalkIndex != 0)
				CSoundMgr::GetInstance()->PlaySound(L"button_press.wav", CHANNEL_ID::UI_0, TALK_SOUND);
			else 
				CSoundMgr::GetInstance()->PlaySound(L"npc_greet.wav", CHANNEL_ID::UI_1, MEOW_SOUND);

			// 대화 중 움직일 수 없게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// 마법사 대화 시작하자마자 카메라 탑뷰로 바꾸기
			// 종료
			if (_iTalkID == 320)
			{
				if (CCameraMgr::GetInstance()->Get_CurCameraAction()
					!= CAMERA_ACTION::PLAYER_BACK_TO_TOP)
				{
					CMiniGameMgr_Jump::GetInstance()->End_MiniGame(); // 미니게임 종료
				}
			}
			// 마지막 대사까지 다 출력했다면
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::END_NPC_TALK);

			}
			if(m_iTalkIndex < iter->second.size())
			{
				// 이미 있으면 지워라
				if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
				{
					CEventMgr::GetInstance()->Delete_Obj
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				}
				// 생성
				if (m_iTalkIndex == 0)
				{
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex], DIALOG_TYPE::DIALOG_START));

					CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::START_NPC_TALK);
				}
				else
				{
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex]));
				}
				++m_iTalkIndex;
			}
		}
	}

	if (m_bTalkEnd)
	{
		if (dynamic_cast<CDialogUI*>(CManagement::GetInstance()->
			Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))->EndLerp_Dialog())
		{
			CEventMgr::GetInstance()->Delete_Obj
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
		
			// 다시 움직일 수 있게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(false);
			
			m_iTalkIndex = 0;
			m_bTalkEnd = false;
			return true;
		}
	}

	return false;
}

_bool CTalkMgr::Get_CamTalk(LPDIRECT3DDEVICE9 pGraphicDev,
	_int _iTalkID, OBJ_ID _eObjID, _int _EventIndex,
	_vec3 _StartPos, _vec3 _TargetPos)
{
	auto iter = m_mapTalkData.find(_iTalkID);
	
	if (&iter)
	{
		if (CInputDev::GetInstance()->Key_Down('E')
			&& !CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"ShadeUI"))
		{
			if (m_iTalkIndex != 0)
				CSoundMgr::GetInstance()->PlaySound(L"button_press.wav", CHANNEL_ID::UI_0, TALK_SOUND);
			else
				CSoundMgr::GetInstance()->PlaySound(L"npc_greet.wav", CHANNEL_ID::UI_1, MEOW_SOUND);

			// 대화 중 움직일 수 없게
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// 이벤트 인덱스라면
			if (m_iTalkIndex == _EventIndex)
			{
				m_pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, _StartPos, _TargetPos, TRUE);
				CSoundMgr::GetInstance()->PlaySoundW(L"map_transition.wav", CHANNEL_ID::UI_3, 1.f);

				m_bTargetCam = true;
			}

			// 마지막 대사까지 다 출력했다면
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::END_NPC_TALK);
			}
			if (m_iTalkIndex < iter->second.size())
			{
				if (m_iTalkIndex != _EventIndex)
				{
					// 이미 있으면 지워라
					if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
					{
						CEventMgr::GetInstance()->Delete_Obj
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
					}
					if (m_iTalkIndex == 0)
					{
						CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
							_eObjID, iter->second[m_iTalkIndex], DIALOG_TYPE::DIALOG_START));

						CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::START_NPC_TALK);
					}
					else
					{
						CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
							_eObjID, iter->second[m_iTalkIndex]));
					}
					++m_iTalkIndex;
				}
			}
		}

		// 카메라 이벤트 시작
		if (m_bTargetCam)
		{
			if (nullptr != m_pCam)
			{
				if (!m_bStaySet)
				{
					// 카메라 이벤트 끝났으면
					if (!m_pCam->Is_LerpTargetChange())
					{
						m_iStayTime = GetTickCount64() + 1700;
						m_bStaySet = true;
					}
				}
				else
				{
					if (GetTickCount64() > m_iStayTime)
					{
						// 대기 시간 끝났으면 다시 돌아가는 카메라 이벤트 실행.
						if (!m_bReturnCam)
						{
							CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, _TargetPos, _StartPos, FALSE);
							m_pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
							CSoundMgr::GetInstance()->PlaySoundW(L"map_transition.wav", CHANNEL_ID::UI_3, 1.f);

							m_bReturnCam = true; 
						}
					}
				}

				if (m_bReturnCam && !m_pCam->Is_LerpTargetChange())
				{
					// 이미 있으면 지워라
					if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
					{
						CEventMgr::GetInstance()->Delete_Obj
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
					}
					// 생성
					CEventMgr::GetInstance()->Add_Obj(L"DialogUI", CDialogUI::Create(pGraphicDev,
						_eObjID, iter->second[m_iTalkIndex]));
					++m_iTalkIndex;
					m_bReturnCam = false;
					m_bTargetCam = false;
				}
			}
		}

		if (m_bTalkEnd)
		{
			if (dynamic_cast<CDialogUI*>(CManagement::GetInstance()->
				Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))->EndLerp_Dialog())
			{
				CEventMgr::GetInstance()->Delete_Obj
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				
				// 움직일 수 있게 다시
				dynamic_cast<CPlayer*>(CManagement::GetInstance()
					->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(false);
				
				m_iTalkIndex = 0;
				m_iStayTime = 0;
				m_bTargetCam = false;
				m_bStaySet = false;
				m_bReturnCam = false;
				m_bTalkEnd = false;
				return true;
			}
		}
	}


	return false;




}

void CTalkMgr::Free()
{
}
