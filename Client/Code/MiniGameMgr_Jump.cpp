#include "MiniGameMgr_Jump.h"
#include "stdafx.h"
#include "Export_Function.h"

// Island
#include "Island_Ice.h"
#include "Island_Death.h"
#include "Island_Jump.h"
#include "Island_Village.h"
#include "Island_King.h"

#include "CameraMgr.h"
#include "Player.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(CMiniGameMgr_Jump)

CMiniGameMgr_Jump::CMiniGameMgr_Jump()
	: m_bInit(FALSE)
	, m_bActive(FALSE)
{
}

CMiniGameMgr_Jump::~CMiniGameMgr_Jump()
{
}

HRESULT CMiniGameMgr_Jump::Init(LPDIRECT3DDEVICE9 _pGraphicDev)
{
    m_pGraphicDev = _pGraphicDev;
	m_bInit = TRUE;
    return S_OK;
}

void CMiniGameMgr_Jump::Update(const _float& _fDelta)
{
	if (!m_bActive) return;

	Check_MiniGame(_fDelta);
}

HRESULT CMiniGameMgr_Jump::Start_MiniGame()
{
	m_bActive = TRUE;

	CSoundMgr::GetInstance()->ChangeBGM(L"catquest_kitcat_theme.wav", BGM_TYPE::ISLAND_JUMP);


	return S_OK;
}

HRESULT CMiniGameMgr_Jump::End_MiniGame()
{
	m_bActive = FALSE;
	return S_OK;
}



// 정말 대충 짠 코드니 참고하지 마세요!

_bool bTestDie = false;
LERP_FLOAT_INFO tLerp;

void CMiniGameMgr_Jump::Check_MiniGame(const _float& _fDelta)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player"));

	NULL_CHECK(pPlayer);
	NULL_CHECK(m_arrIsland[(UINT)ISLAND_TYPE::JUMP]);

	if (CCameraMgr::GetInstance()->Is_BackView() && !pPlayer->Is_Jump() && !m_arrIsland[(UINT)ISLAND_TYPE::JUMP]->Is_In_Player())
	{
		if (!bTestDie)
		{
			Die_Player();
		
			tLerp.Init_Lerp(LERP_MODE::EASE_OUT);
			_float fTargetLerp = pPlayer->Get_Transform()->Get_Info(INFO_POS).y - pPlayer->Get_Transform()->Get_Scale().y * 2.5f;
			tLerp.Set_Lerp(0.5f, pPlayer->Get_Transform()->Get_Info(INFO_POS).y, fTargetLerp);
			tLerp.fCurValue = pPlayer->Get_Transform()->Get_Info(INFO_POS).y;
		}

	}

	if (bTestDie && tLerp.bActive)
	{
		tLerp.Update_Lerp(_fDelta);
		_vec3 pos = pPlayer->Get_Transform()->Get_Info(INFO_POS);
		pos.y = tLerp.fCurValue;
		pPlayer->Get_Transform()->Set_Pos(pos);

		if (!tLerp.bActive)
		{
			CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_OUT);
		}
	}

	if (bTestDie && !tLerp.bActive && !CCameraMgr::GetInstance()->Is_Fade())
	{
		bTestDie = FALSE;
		CCameraMgr::GetInstance()->Start_Fade(FADE_MODE::BLACK_FADE_IN);
		pPlayer->Get_Transform()->Set_Pos(MINIGAME_JUMP_RESET_POS);
		CCameraMgr::GetInstance()->Set_ViewSpace();
	}

}

HRESULT CMiniGameMgr_Jump::Die_Player()
{
	bTestDie = true;

	CSoundMgr::GetInstance()->PlaySoundW(L"water_splash.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_WATER);

	/*
	
		* 1. 플레이어 흩어지는 셰이더 효과?
		
		* 2. 화면 페이드 인 아웃 (어떤 페이드로?)
		
		* 3. 다시 시작위치에서 시작
	
	*/


	return S_OK;
}

HRESULT CMiniGameMgr_Jump::Create_Islands()
{
	CIsland* pGameObject = nullptr;

	pGameObject = CIsland_Village::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::VILLAGE] = pGameObject;

	pGameObject = CIsland_Ice::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::ICE] = pGameObject;

	pGameObject = CIsland_Death::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::DEATH] = pGameObject;

	pGameObject = CIsland_Jump::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::JUMP] = pGameObject;

	pGameObject = CIsland_King::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(pGameObject->Get_Name(), pGameObject), E_FAIL);
	m_arrIsland[(UINT)ISLAND_TYPE::KING] = pGameObject;

	return S_OK;
}


void CMiniGameMgr_Jump::Free()
{
}
