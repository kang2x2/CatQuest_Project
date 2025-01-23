#include "BossSceneMgr.h"
#include "stdafx.h"
#include "Export_Function.h"

#include "CameraMgr.h"
#include "Player.h"
#include "SoundMgr.h"
#include "Player_Camera.h"
#include "VioletDragon.h"
#include "Npc_Citizen2.h"

IMPLEMENT_SINGLETON(CBossSceneMgr)

CBossSceneMgr::CBossSceneMgr()
	: m_fAcc(0.f)
	, m_fDeadFadeStayTime(1.5f)
	, m_bFadeIn_End(FALSE)
	, m_bFadeOut_End(FALSE)
	, m_fIntroDelayTime(2.f)
	, m_fOuttroDelayTime(1.5f)
	, m_bIntroAniEnd(FALSE)
{
	for (int i = 0; i < (_uint)PAGE::TYPEEND; ++i)
		m_arrPage[i] = FALSE;
}

CBossSceneMgr::~CBossSceneMgr()
{
}

HRESULT CBossSceneMgr::Ready_BossSceneMgr(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	if (m_arrPage[(_uint)PAGE::INIT]) return E_FAIL;

	m_arrPage[(_uint)PAGE::INIT] = TRUE;

	m_pGraphicDev = _pGraphicDev;

	return S_OK;
}

void CBossSceneMgr::Update_BossSceneMgr(const _float& fTimeDelta)
{
	if (!m_arrPage[(_uint)PAGE::INTRO] || m_arrPage[(_uint)PAGE::FINISH]) return;

	if (m_arrPage[(_uint)PAGE::INTRO] && !m_arrPage[(_uint)PAGE::START])
	{
		m_fAcc += fTimeDelta;
		
		if (m_fIntroDelayTime <= m_fAcc)
		{
			m_arrPage[(_uint)PAGE::START] = TRUE;
			CGameObject* pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");
			NULL_CHECK(pBoss, E_FAIL);
			pBoss->Set_Active(TRUE);
			m_fAcc = 0.f;
		}
	}

	if (m_arrPage[(_uint)PAGE::OUTTRO] && !m_arrPage[(_uint)PAGE::DEAD])
	{
		m_fAcc += fTimeDelta;

		if (m_fIntroDelayTime <= m_fAcc)
		{
			m_arrPage[(_uint)PAGE::DEAD] = TRUE;

			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::WHITE_FADE_OUT);
			CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EASE_OUT, 3.5f, SOUND_VOLUME_BGM, 0.f);

			m_fAcc = 0.f;
		}
	}

	if (m_arrPage[(_uint)PAGE::DEAD] && !m_bFadeOut_End && !m_bFadeIn_End)
	{
		if (!CCameraMgr::GetInstance()->Is_Fade())
		{
			m_fAcc += fTimeDelta;

			if (m_fDeadFadeStayTime <= m_fAcc)
			{
				// 03. 카메라, BGM 페이드 인 (다 하얘진 상황)
				if (CAMERA_ACTION::BOSS_SKILL_IN == CCameraMgr::GetInstance()->Get_CurCameraAction() || CAMERA_ACTION::BOSS_SKILL_OUT == CCameraMgr::GetInstance()->Get_CurCameraAction())
					CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
				CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->m_fDistance = CAM_DISTANCE_DEFAULT;
				CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::WHITE_FADE_IN);
				CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::END_BOSS);
				CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EXPONENTIAL, 2.5f, 0.f, SOUND_VOLUME_BGM);
				CSoundMgr::GetInstance()->PlayBGM(L"catquest_overworld_theme.wav", BGM_TYPE::ENDING);
				m_arrPage[(_uint)PAGE::FADE_OUT] = TRUE;
				m_bFadeOut_End = TRUE;
				Set_Npc();
			}
		}
	}

	if (m_arrPage[(_uint)PAGE::DEAD] && m_bFadeOut_End && !m_bFadeIn_End)
	{
		if (!CCameraMgr::GetInstance()->Is_Fade())
		{
			// 04. 카메라, BGM 페이드인 완료 = 보스 연출 종료 

			m_bFadeIn_End = TRUE;
			m_arrPage[(_uint)PAGE::FINISH] = TRUE;
		}
	}

}

const _bool CBossSceneMgr::Is_Active_Boss()
{
	CGameObject* pBoss = nullptr;
	
	pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");

	if (nullptr == pBoss)
		return FALSE;
	else if (pBoss->Is_Active())
		return TRUE;
	else
		return FALSE;
}

void CBossSceneMgr::Set_BossIntroAnimation_End()
{
	m_bIntroAniEnd = TRUE;
	
	CPlayer* pPlayer = static_cast<CPlayer*>(CManagement::GetInstance()->Get_Player());
	pPlayer->Block_Input(FALSE);

	CCameraMgr::GetInstance()->Set_CurCameraAction(CAMERA_ACTION::NONE);
}

HRESULT CBossSceneMgr::Start_BossScene()
{
	// 01. 보스 활성화 -> 등장 애니메이션 

	if (!m_arrPage[(_uint)PAGE::INIT] || m_arrPage[(_uint)PAGE::INTRO]) return E_FAIL;

	m_arrPage[(_uint)PAGE::INTRO] = TRUE;

	CGameObject* pPlayer = CManagement::GetInstance()->Get_Player();
	NULL_CHECK_RETURN(pPlayer, E_FAIL);

	CGameObject* pBoss = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::MONSTER, L"Monster_VioletDragon");
	NULL_CHECK_RETURN(pBoss, E_FAIL);
	//pBoss->Set_Active(TRUE);
	pBoss->Get_Transform()->Set_Pos(_vec3{ BOSS_POS_X, pBoss->Get_Transform()->Get_Info(INFO_POS).y, BOSS_POS_Z });

	// 브금 변경
	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_battle_theme.wav", BGM_TYPE::BOSS);
	
	// 카메라 액션 1
	CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::START_BOSS);

	// 카메라 액션 2
	_vec3 vBossPos{ pBoss->Get_Transform()->Get_Info(INFO_POS).x, pPlayer->Get_Transform()->Get_Info(INFO_POS).y, pBoss->Get_Transform()->Get_Info(INFO_POS).z };

	CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::OBJ_CHANGE_TARGET, pPlayer->Get_Transform()->Get_Info(INFO_POS), vBossPos, TRUE);

	return S_OK;
}

void CBossSceneMgr::Play_Dead_BossScene()
{	
	// 02. 카메라, BGM 페이드 아웃

	m_arrPage[(_uint)PAGE::OUTTRO] = TRUE;

	/*CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::WHITE_FADE_OUT);
	CSoundMgr::GetInstance()->Lerp_Volume_CurBGM(LERP_MODE::EASE_OUT, 3.5f, SOUND_VOLUME_BGM, 0.f);*/
}

void CBossSceneMgr::Set_Npc()
{
	CGameObject* pPlayer = CManagement::GetInstance()->Get_Player();
	NULL_CHECK(pPlayer);
	_vec3 vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO_POS);

	CGameObject* pNpc = nullptr;
	_vec3 vNpcPos, vNewPos, vNpcScale;
	
	// 01. Npc_Citizen1
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Citizen1");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x - 6.f, vNpcPos.y, vPlayerPos.z + 9.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	// 02. Npc_Soldier
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_Soldier");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x + 5.f, vNpcPos.y, vPlayerPos.z + 7.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	vNpcScale = pNpc->Get_Transform()->Get_Scale();
	pNpc->Get_Transform()->Set_Scale(_vec3{ -vNpcScale.x, vNpcScale.y, vNpcScale.z });

	// 03. Npc_Citizen2
	pNpc = CNpc_Citizen2::Create(m_pGraphicDev);
	NULL_CHECK(pNpc);
	CEventMgr::GetInstance()->Add_Obj(pNpc->Get_Name(), pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x + 10.f, vNpcPos.y, vPlayerPos.z + 3.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);

	vNpcScale = pNpc->Get_Transform()->Get_Scale();
	pNpc->Get_Transform()->Set_Scale(_vec3{ -vNpcScale.x, vNpcScale.y, vNpcScale.z });

	// 03. Npc_BlackSmith
	pNpc = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::NPC, L"Npc_BlackSmith");
	NULL_CHECK(pNpc);
	vNpcPos = pNpc->Get_Transform()->Get_Info(INFO_POS);
	vNewPos = _vec3{ vPlayerPos.x -5.f, vNpcPos.y, vPlayerPos.z + 4.f };
	pNpc->Get_Transform()->Set_Pos(vNewPos);
}



void CBossSceneMgr::Free()
{
}
