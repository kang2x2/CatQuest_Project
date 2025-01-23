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

#pragma region Quest1 : ���������� ��Ź
	// Quest1 : ���������� ��Ź
	// ��������
	m_mapTalkData.insert(make_pair(100, vector<wstring>{
		{ L"�ȳ�! \n�츮 ������ �� �Ծ�!"},
		{ L"�ʵ� �巡���� �ҹ��� ��� ����ġ�� �°ž�? \n�׷��ٸ� ȯ���̾�." },
		{ L"�Ϸ� ���� óġ���� ������ �ٽ� ����� \nã�ƿ��״ϱ�!"},
		{ L"��. ���� ������ �ʸ� ������ ���ӽ���� ��!"},
		{ L"�ƽ��Ե� �巡�￡ ���� ������ \n���� ������ �ִ� ���̾�."},
		{ L"�׵��� �� �Ʒ��ʿ� �ִ� ����ġ���� \nȥ�������� ���ھ�!"}
		}));
	// ��������
	m_mapTalkData.insert(make_pair(101, vector<wstring>{
		{ L"����ġ���� ȥ���ᱸ��!"},
		{ L"�̰ɷ� �༮�鵵 ����ó�� Ȱ��ġ�� �� �Ұž�." },
		{ L"����! �̰� �츮���� ���� �ִ� ��ų���̾�." },
		{ L"�ϰ� �������ָ� �巡���� óġ�ϴ� �� \n������ �ǰ���!"}
	}));
#pragma endregion
#pragma region Quest2 : ���� ����
// Quest2 : ���� ����
// ��������
	m_mapTalkData.insert(make_pair(200, vector<wstring>{
		{ L"������ ������ ���� ���͵��� \n��� ���������� ������?"},
		{ L"�������� �ȿ��� ���¸� ���� ���ε� \n ���Ͱ� �ʹ� ���Ƽ� ���� �ʳ���."},
		{ L"��� �����ϸ� �ȿ��� �������� \n�����ɿ��� ��������."},
		{ L"�׵��� ���� �巡�￡ ���� ������ ��ƵѰ�."}
	}));

	// ��Ƽ��(2)
	m_mapTalkData.insert(make_pair(201, vector<wstring>{
		{ L"���͸� ��� �����ϼ̳׿�!"},
		{ L"���� �����մϴ�. �����ϱ� �������׿�."},
		{ L"�׸��� �̰͵��� �̰����� ���������\n � ������� ��ǰ�ϱ��?" },
		{ L"�̷��� ������ �ִ��󱸿�." },
		{ L"������ ��Ų� �� ������ �� �� ������ \n����������!" }
	}));
	//

#pragma endregion
#pragma region Quest3 : �巡�￡�� ���ϱ� ���ؼ�
// Quest3 : �巡�￡�� ���ϱ� ���ؼ�
	// ��������
	m_mapTalkData.insert(make_pair(300, vector<wstring>{
		{ L"�巡�� �����뿡�� ������ �Ծ�!"},
		{ L"�巡���� �����Ǽ��� �ְ� ������ ���� \n ���� ���ؼ� �� �� �־�� ��!"},
		{ L"�������� ��� �ִ� ���� �����ɶ�� \n�� �� �ִ� ����� �˰� ���� �� ����."},
		{ L"���������� ���� ����� ���� �ؾȰ��� �ִ� \n������ �˰� �����ž�."},
		{ L"����!" }
	}));

	m_mapTalkData.insert(make_pair(301, vector<wstring>{
		{ L"�ϰ� ���Ƽ� ���°� ���⼭�� ���̴���!"},
		{ L"���� �ʶ�� �س� �� �˾Ҿ�!" },
		{ L"�׸��� �ϰ� �������� �� �ִ� ���� \n�̷��� ã�Ҿ�." },
		{ L"�ε� ����ϰ� ����!" }
	}));


	// ����
	m_mapTalkData.insert(make_pair(310, vector<wstring>{
		{ L"���� �������� ������ �������� ���Ŵٱ���?"},
		{ L"���� �������� �������� �ֱ� �մϴٸ�.." },
		{ L"���ôٽ��� �������� ���� ���� �پ ���ž� �˴ϴ�." },
		{ L"�����ؼ� �ٳ������!" }
	}));
	// ������
	m_mapTalkData.insert(make_pair(320, vector<wstring>{
		{ L"�մ��� ã�ƿ��ٴ�.. �ݰ���."},
		{ L"�ϴ��� ���� �ʹٰ�? \n�ϴ��� �������ؼ� �ö��� ���갡 �ʿ���." },
		{ L"������ ��򰡿� �ִ� �ö��� ���긦 ã�ƿ�." },
		{ L"�׷� �� �� �ְ� ������." }
	}));
	m_mapTalkData.insert(make_pair(321, vector<wstring>{
		{ L"��¥�� ã�ƿԱ�."},
		{ L"����. �ϴ��� �� �� �ְ� ������." },
		{ L"���� �ϴ��� ������ ���ƺ�����!"}
	}));
	//

#pragma endregion
#pragma region Quest3.5 : ����
// Quest3.5 : ����
	// ��������
	m_mapTalkData.insert(make_pair(350, vector<wstring>{
		{ L"�� �ٸ� ������ ����µ� ����� �巡�� ���尡 \n����ϴ� ������ ���� ���� ����� ���� �ֳ���!"},
		{ L"�� ������ ��´ٸ� ���� �巡�� ������ \n������ ���� ���� �� �����ž�!" },
		{ L"����̵��� ���� �Ⱦ��ؼ� �ǳ��� ���ϴµ�. \n�ʴ� �� �� �����ϱ� �� �� �����ž�!"},
		{ L"������ �����ϴ� �� �𸣰����� ��� �Ǹ� \n�����Ե� ���� �޶�!"}
	}));

	m_mapTalkData.insert(make_pair(351, vector<wstring>{
		{ L"�װ� ������ �����ΰž�? \n������ �����߱���. ������?"},
		{ L"�ϰ� ������ �� �ִ� ���� ���ο� ��ų���� ã�Ҿ�! \n�̰͵� ������ �ٰ�."},
		{ L"����. ���� ������ ���� �ẹ ���� �����ɿ��� \n������ �غ��״� ��� �ڿ� ����!" }
	}));

	// ��� ����
	m_mapTalkData.insert(make_pair(360, vector<wstring>{
		{ L"������ ��� ���ؼ��� ���� ������ �ʿ��ϴ�."},
		{ L"������� �Դٸ� ���� ���� �� ���̴�."},
		{ L"������ ������ ���ƶ�. �׷� ���� ��������." }
	}));
#pragma endregion
#pragma region Quest4 : ������ ������
// Quest4 : ������ ������
// ��������
	m_mapTalkData.insert(make_pair(400, vector<wstring>{
		{ L"���� ��� �غ� ��������."},
		{ L"��ħ ���������� ������ �޾Ҿ�. \n�巡���� ������ �� ������ �ִ� ����̾�."},
		{ L"���� ������ ������ ���ư��� \n�������� ������ �ɰž�."},
		{ L"�Ƹ� ���� ���� �ػ� �ִ� \n���͵��� ���ذ� �����ž�."},
		{ L"�ػ� ���� ��� ���͸� óġ�ϰ� \n���������� ����."},
		{ L"�� ��Ƽ� �ٽ� ������!"}
	}));

	// ��Ƽ��(1)
	m_mapTalkData.insert(make_pair(410, vector<wstring>{
		{ L"��ٸ��� �־����ϴ�."},
		{ L"�� �տ� ����� �巡���� �ֽ��ϴ�."},
		{ L"���� ����̵��� ��� �ƽ��ϴ�. \n�ε� �����Ͻʽÿ�."},
		{ L"������ ���ϴ�!"}
	}));
	//

#pragma endregion
#pragma region Quest5 : ����
// Quest5 : ����
	// ��������
	m_mapTalkData.insert(make_pair(500, vector<wstring>{
		{ L"�巡���� �����Ʊ���!"},
		{ L"���� ����! \n���п� ������ ��ȭ�� ã�ƿԾ�!" },
		{ L"���⼭ �Ʒ��ʿ� �ִ� ���� ������ ���ڿղ��� \n��ٸ��� �ҽ��� ��ٸ��� �輭."},
		{ L"���ڿղ� �� ����!" }
	}));

	// ���ڿ�
	m_mapTalkData.insert(make_pair(510, vector<wstring>{
		{ L"�״밡 �巡�� �����ΰ�."},
		{ L"���п� ���� ��ȭ�� ã�� �� �ְ� �Ǿ�����."},
		{ L"�츮�� �״��� Ȱ���� ���� ���� ���� ���̳�."},
		{ L"�ٽ� �ѹ� ���縦 ǥ�ϳ�. \n������ �巡�� ���忩."}
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

			// ��ȭ �� ������ �� ����
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// ������ ��ȭ �������ڸ��� ī�޶� ž��� �ٲٱ�
			// ����
			if (_iTalkID == 320)
			{
				if (CCameraMgr::GetInstance()->Get_CurCameraAction()
					!= CAMERA_ACTION::PLAYER_BACK_TO_TOP)
				{
					CMiniGameMgr_Jump::GetInstance()->End_MiniGame(); // �̴ϰ��� ����
				}
			}
			// ������ ������ �� ����ߴٸ�
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::END_NPC_TALK);

			}
			if(m_iTalkIndex < iter->second.size())
			{
				// �̹� ������ ������
				if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
				{
					CEventMgr::GetInstance()->Delete_Obj
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
				}
				// ����
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
		
			// �ٽ� ������ �� �ְ�
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

			// ��ȭ �� ������ �� ����
			dynamic_cast<CPlayer*>(CManagement::GetInstance()
				->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"))->Set_PlayerTalk(true);

			// �̺�Ʈ �ε������
			if (m_iTalkIndex == _EventIndex)
			{
				m_pCam = dynamic_cast<CPlayer_Camera*>(CCameraMgr::GetInstance()->Get_CurCamera());
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, _StartPos, _TargetPos, TRUE);
				CSoundMgr::GetInstance()->PlaySoundW(L"map_transition.wav", CHANNEL_ID::UI_3, 1.f);

				m_bTargetCam = true;
			}

			// ������ ������ �� ����ߴٸ�
			if (m_iTalkIndex >= iter->second.size())
			{
				m_bTalkEnd = true;
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::END_NPC_TALK);
			}
			if (m_iTalkIndex < iter->second.size())
			{
				if (m_iTalkIndex != _EventIndex)
				{
					// �̹� ������ ������
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

		// ī�޶� �̺�Ʈ ����
		if (m_bTargetCam)
		{
			if (nullptr != m_pCam)
			{
				if (!m_bStaySet)
				{
					// ī�޶� �̺�Ʈ ��������
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
						// ��� �ð� �������� �ٽ� ���ư��� ī�޶� �̺�Ʈ ����.
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
					// �̹� ������ ������
					if (CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"))
					{
						CEventMgr::GetInstance()->Delete_Obj
						(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"DialogUI"));
					}
					// ����
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
				
				// ������ �� �ְ� �ٽ�
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
