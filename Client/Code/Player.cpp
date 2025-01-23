#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_Function.h"

#include "RectCollider.h"

#include "PlayerState_Hit.h"
#include "PlayerState_fIdle.h"
#include "PlayerState_fWalk.h"
#include "PlayerState_fRoll.h"
#include "PlayerState_fAttack.h"
#include "PlayerState_fAttack1.h"
#include "PlayerState_fAttack2.h"
#include "PlayerState_fDie.h"
#include "PlayerState_fWake.h"
#include "PlayerState_fSleep.h"
#include "PlayerState_bIdle.h"
#include "PlayerState_bWalk.h"
#include "PlayerState_bRoll.h"
#include "PlayerState_bAttack.h"
#include "PlayerState_bAttack1.h"
#include "PlayerState_bAttack2.h"
#include "PlayerState_fFlight.h"
#include "PlayerState_fAttack3.h"

#include "Environment.h"
#include "Npc.h"
#include "EnterUI.h"
#include "FieldSkillUI.h"

#include "Monster.h"
#include "Projectile.h"

#include "SphereCollider.h"

// Move Effect
#include "MoveDust.h"
#include "MoveWater.h"
// Skill
#include "Skill_Player_Heal.h"
#include "Skill_Player_Fire.h"
#include "Skill_Player_Ice.h"
#include "Skill_Player_Thunder.h"
#include "Skill_Player_Beam.h"
#include "Skill_Player_Fly.h"
#include "Skill_Player_Arrow.h"
//Effect
#include "Effect_Ora.h"
#include "Effect_ThornSparkle.h"
#include "EffectLevel_Banner.h"
#include "EffectLevel_Shine.h"
// UI
#include "RingUI.h"
#include "Effect_Font.h"
#include "FlightUI.h"
#include "Quest_DialogUI.h"

// Shadow
#include "Shadow_Player.h"

#include "RangeObj.h"
#include "EventMgr.h"

#include "WorldFlight.h"
#include "Inventory.h"
#include "Item.h"

#include "SoundMgr.h"
#include "BossSceneMgr.h"
#include "Player_AfterImg.h"

#include "TurretSkull.h"


CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::PLAYER, OBJ_ID::PLAYER)
	, m_pStateMachineCom(nullptr)
	, m_eCurGroundType(GROUND_TYPE::NORMAL)
{
	ZeroMemory(&m_pTextureCom, sizeof(CTexture*) * _uint(STATE_TYPE::TYPEEND));
}

CPlayer::CPlayer(const CPlayer& rhs)
	: Engine::CGameObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
	, m_tStatInfo(rhs.m_tStatInfo)
	, m_pStateMachineCom(rhs.m_pStateMachineCom)
	, m_eCurGroundType(rhs.m_eCurGroundType)
{
	for (size_t i = 0; i < _uint(_uint(STATE_TYPE::TYPEEND)); ++i)
	{
		m_pTextureCom[i] = rhs.m_pTextureCom[i];
	}
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_bBlockInput = FALSE;
	m_iCreateAfterImg = 0;

	m_tMoveInfo.fMoveSpeed = 20.f;
	Set_AD(5);
	m_bIsBoss = false;

	m_fBallTargetLenght = 18.f;
	m_pBallTarget = nullptr;
	m_bLockOn = false;

	m_bFly = false;
	m_pSkillFly = nullptr;

	m_fThornAcc = 0.f;

	m_bHit = false;
	m_bAttack = false;
	m_bSkill = false;

	m_bClocking = false;
	m_fClockingAcc = 0.f;
	m_iClockAlpha = 128.f;

	m_bIsMonster = false;
	m_fMonTargetLength = 99.f;
	m_pMonTarget = nullptr;
	
	m_bhasFlight = false;
	m_bIsTalking = false;

	m_pInven = nullptr;

	m_tStatInfo.fGold = 120;



	for (size_t i = 0; i < 4; ++i)
	{
		m_arrSkillSlot[i] = nullptr;
	}

	m_fAccDef = 0.f;
	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Dir(vec3.right);
	m_pTransformCom->Set_Pos(_vec3{ 
		_float(START_POS_WORLD_X), 
		m_pTransformCom->Get_Scale().y, 
		_float(START_POS_WORLD_Z) });

	CGameObject* pShadow = CShadow_Player::Create(m_pGraphicDev, this);
	CEventMgr::GetInstance()->Add_Obj(L"Player_Shadow", pShadow);
	pShadow->Set_Maintain(TRUE); // <-수정시 팀장 보고!

#pragma region State
	CState* pState = CPlayerState_Hit::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_HIT, pState);
	pState = CPlayerState_fWalk::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_WALK, pState);
	pState = CPlayerState_fIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_IDLE, pState);
	pState = CPlayerState_fRoll::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ROLL, pState);
	pState = CPlayerState_fAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK, pState);
	pState = CPlayerState_fAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK1, pState);
	pState = CPlayerState_fAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK2, pState);
	pState = CPlayerState_bIdle::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_IDLE, pState);
	pState = CPlayerState_bWalk::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_WALK, pState);
	pState = CPlayerState_bRoll::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ROLL, pState);
	pState = CPlayerState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK, pState);
	pState = CPlayerState_bAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK1, pState);
	pState = CPlayerState_bAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_ATTACK2, pState);
	pState = CPlayerState_fWake::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_WAKE, pState);
	pState = CPlayerState_fDie::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_DIE, pState);
	pState = CPlayerState_fSleep::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_SLEEP, pState);
	pState = CPlayerState_fFlight::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_FLIGHT, pState);
	pState = CPlayerState_fFlight::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_FLIGHT, pState);
	pState = CPlayerState_fAttack3::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::FRONT_ATTACK3, pState);
#pragma endregion

#pragma region Animation
	CAnimation* pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_HIT, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_WALK)], STATE_TYPE::FRONT_WALK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)], STATE_TYPE::FRONT_ATTACK1, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)], STATE_TYPE::FRONT_ATTACK2, 0.08f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_ROLL)], STATE_TYPE::FRONT_ROLL, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_DIE)], STATE_TYPE::FRONT_DIE, 0.09f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_WAKE)], STATE_TYPE::FRONT_WAKE, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_WAKE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)], STATE_TYPE::FRONT_SLEEP, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_SLEEP, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.08f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)], STATE_TYPE::FRONT_FLIGHT, 0.02f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::FRONT_FLIGHT, pAnimation);
	// 닌자
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_HIT, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WALK)], STATE_TYPE::FRONT_WALK, 0.1f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)], STATE_TYPE::FRONT_ATTACK1, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)], STATE_TYPE::FRONT_ATTACK2, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ROLL)], STATE_TYPE::FRONT_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_DIE)], STATE_TYPE::FRONT_DIE, 0.09f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WAKE)], STATE_TYPE::FRONT_WAKE, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_WAKE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)], STATE_TYPE::FRONT_SLEEP, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_SLEEP, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.08f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)], STATE_TYPE::FRONT_FLIGHT, 0.02f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]->Add_Animation(STATE_TYPE::FRONT_FLIGHT, pAnimation);

	// 메이지
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_HIT, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_WALK)], STATE_TYPE::FRONT_WALK, 0.1f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)], STATE_TYPE::FRONT_ATTACK1, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)], STATE_TYPE::FRONT_ATTACK2, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ROLL)], STATE_TYPE::FRONT_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_DIE)], STATE_TYPE::FRONT_DIE, 0.09f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_WAKE)], STATE_TYPE::FRONT_WAKE, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_WAKE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)], STATE_TYPE::FRONT_SLEEP, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_SLEEP, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.08f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pMageTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)], STATE_TYPE::FRONT_FLIGHT, 0.02f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]->Add_Animation(STATE_TYPE::FRONT_FLIGHT, pAnimation);

	// 기사
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_HIT)], STATE_TYPE::FRONT_HIT, 0.2f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_HIT, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_WALK)], STATE_TYPE::FRONT_WALK, 0.1f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_IDLE)], STATE_TYPE::FRONT_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)], STATE_TYPE::FRONT_ATTACK, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)], STATE_TYPE::FRONT_ATTACK1, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)], STATE_TYPE::FRONT_ATTACK2, 0.08f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ROLL)], STATE_TYPE::FRONT_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_DIE)], STATE_TYPE::FRONT_DIE, 0.09f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_DIE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_WAKE)], STATE_TYPE::FRONT_WAKE, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_WAKE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)], STATE_TYPE::FRONT_SLEEP, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_SLEEP, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_IDLE)], STATE_TYPE::BACK_IDLE, 0.2f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_IDLE, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_WALK)], STATE_TYPE::BACK_WALK, 0.08f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_WALK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK)], STATE_TYPE::BACK_ATTACK, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_ATTACK, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)], STATE_TYPE::BACK_ATTACK1, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_ATTACK1, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)], STATE_TYPE::BACK_ATTACK2, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_ATTACK2, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::BACK_ROLL)], STATE_TYPE::BACK_ROLL, 0.1f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::BACK_ROLL, pAnimation);
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)], STATE_TYPE::FRONT_FLIGHT, 0.02f, TRUE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_FLIGHT, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK3)], STATE_TYPE::FRONT_ATTACK3, 0.06f, FALSE);
	m_pClassAnimator[_uint(CLASS_TYPE::THORN)]->Add_Animation(STATE_TYPE::FRONT_ATTACK3, pAnimation);
#pragma endregion

#pragma region SKILL

	CSkill* pSkill = CSkill_Player_Fly::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Fly", pSkill), E_FAIL);
	m_pSkillFly = pSkill;
	m_pSkillFly->Set_Maintain(TRUE);

	pSkill = CSkill_Player_Heal::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Heal", pSkill), E_FAIL);
	m_pSkillHeal = pSkill;
	m_pSkillHeal->Set_Maintain(TRUE);

	pSkill = CSkill_Player_Arrow::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Player_Arrow", pSkill), E_FAIL);
	m_pSkillArrow = pSkill;
	m_pSkillArrow->Set_Maintain(TRUE);

	CUI* pUI = CRingUI::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pUI, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"UI_Ring", pUI), E_FAIL);
	m_pRingUI = pUI;
	m_pRingUI->Set_Maintain(TRUE);

	pUI = CFlightUI::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pUI, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"UI_Fly", pUI), E_FAIL);
	m_pFlyUI = pUI;
	m_pFlyUI->Set_Maintain(TRUE);

	CEffect* pEffect = CEffect_Ora::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pEffect, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Ora", pEffect), E_FAIL);
	m_pEffectOra = pEffect;
	m_pEffectOra->Set_Maintain(TRUE);

	pEffect = CEffectLevel_Banner::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pEffect, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Banner", pEffect), E_FAIL);
	m_pEffectBanner = pEffect;
	m_pEffectBanner->Set_Maintain(TRUE);

	pEffect = CEffectLevel_Shine::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(pEffect, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Effect_Shine", pEffect), E_FAIL);
	m_pEffectShine = pEffect;
	m_pEffectShine->Set_Maintain(TRUE);

#pragma endregion

	// 처음 시작상태 설정
	m_eClass = CLASS_TYPE::NORMAL;
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::FRONT_SLEEP);

	// Camera Setting
	if (PLAY_MODE::TOOL != CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
		CCameraMgr::GetInstance()->Set_ViewSpace();
		CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Set_InitLook_Y(m_pTransformCom->Get_Info(INFO_POS).y);
	}
	m_bMaintain = true; // 씬 변경시 유지 (사용시 팀장 보고)

	
	// << : Test : Range Test
	CGameObject* pGameObject = nullptr;

	pGameObject = CRangeObj::Create(m_pGraphicDev, this, 7.f);
	pGameObject->Set_Maintain(TRUE); // <-수정시 팀장 보고!
	CSphereCollider* pShpere = dynamic_cast<CSphereCollider*>(pGameObject->Get_Component(COMPONENT_TYPE::COL_SPHERE, ID_STATIC));
	pShpere->Set_Radius(7.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Player_Range_Basic_Attack", pGameObject);
	arrRangeObj[(UINT)RANGE_TYPE::BASIC_ATTACK] = dynamic_cast<CRangeObj*>(pGameObject);

	m_szName = L"Player";

	m_pInven = CInventory::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(m_pInven, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"Inventory", m_pInven);
	m_pInven->Set_Maintain(true);

	

	return S_OK;
}
Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	

	//cout << ++k << "--------\n";
	//cout << m_pRigidBodyCom->Get_Velocity().x << "\t" << m_pRigidBodyCom->Get_Velocity().y << "\t" << m_pRigidBodyCom->Get_Velocity().z << "\n";
	//cout << "Player Update--\n";
	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WALK)
	{
		if (m_pStateMachineCom->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 0 ||
			m_pStateMachineCom->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 7)
		{
			if (!CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"FrontMoveDust"))
			{
				if (!m_pRigidBodyCom->Is_Jump())
				{
					CSoundMgr::GetInstance()->PlaySoundW(L"footstep.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_WALK);
					CGameObject* pMoveDust = CMoveDust::Create(m_pGraphicDev, this);


					CEventMgr::GetInstance()->Add_Obj(L"FrontMoveDust", pMoveDust);
				}
				
			}
		}
	}
	else if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_WALK)
	{
		if (m_pStateMachineCom->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 0 ||
			m_pStateMachineCom->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 8)
		{
			if (!CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::EFFECT, L"BackMoveDust"))
			{
				if (!m_pRigidBodyCom->Is_Jump())
				{
					CSoundMgr::GetInstance()->PlaySoundW(L"footstep.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_WALK);

					CGameObject* pMoveDust = CMoveDust::Create(m_pGraphicDev, this);


					CEventMgr::GetInstance()->Add_Obj(L"BackMoveDust", pMoveDust);
				}
				
			}
		}
	}

	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (m_bBlockInput) return iExit; // 인풋 막기 추가

	m_pStateMachineCom->Update_StateMachine(fTimeDelta);

	Regen_Def(fTimeDelta);

	Clocking_Time(fTimeDelta);

	if(!m_bIsTalking)
		Key_Input(fTimeDelta);
	
	Create_ThornSparkle(fTimeDelta);

	if (!m_listAfterImg.empty() && m_eClass == CLASS_TYPE::NINJA)
	{
		if (m_listAfterImg.front() != nullptr)
		{
			m_listAfterImg.front()->Set_Active(true);
			CEventMgr::GetInstance()->Add_Obj(L"Player_AfterImg", m_listAfterImg.front());
			m_listAfterImg.pop_front();
		}
	
	}
		
	return iExit;
}

void CPlayer::LateUpdate_Object()
{
	if (m_bBlockInput)
	{
		__super::LateUpdate_Object();
		return;
	}

	m_pStateMachineCom->LateUpdate_StateMachine();

	if(m_bAttack)
		m_bAttack = false;

	if (m_bSkill)
		m_bSkill = false;

	if (m_bIsTalking && m_bClocking)
		Off_Clocking();


	if(!m_bFly && m_pSkillFly->Is_Active())
	{
		m_pSkillFly->Get_Transform()->Set_Pos(m_pTransformCom->Get_Info(INFO::INFO_POS));
		m_pSkillFly->Set_Active(false);
	}

	if (m_eClass == CLASS_TYPE::MAGE)
	{
		if (m_pSkillArrow->Is_Active())
		{
			_vec3 vDir = m_pSkillArrow->Get_Transform()->Get_Dir();

			if (m_pStateMachineCom->Get_CurState() != STATE_TYPE::FRONT_WALK &&
				m_pStateMachineCom->Get_CurState() != STATE_TYPE::BACK_WALK)
			{
				m_pTransformCom->Set_Dir(vDir);
			}
			
			if (m_pStateMachineCom->Get_CurState() != STATE_TYPE::FRONT_WALK &&
				m_pStateMachineCom->Get_CurState() != STATE_TYPE::BACK_WALK &&
			    m_pStateMachineCom->Get_CurState() != STATE_TYPE::FRONT_ROLL &&
				m_pStateMachineCom->Get_CurState() != STATE_TYPE::BACK_ROLL)
					Set_PlayerLook(vDir);

			m_pBallTarget = nullptr;
		}
		else
		{
			MageBall_Target();
		}
	}

	LevelUp();

	// 잔상 만들기 널체크는 나중에 안정되면 넣을거임
	if (m_eClass == CLASS_TYPE::NINJA)
	{
		if (m_iCreateAfterImg % 4 == 0 && m_listAfterImg.size() <= 5)
		{
			if (m_pStateMachineCom->Get_CurState() != STATE_TYPE::FRONT_IDLE &&
				m_pStateMachineCom->Get_CurState() != STATE_TYPE::BACK_IDLE &&
				m_pStateMachineCom->Get_CurState() != STATE_TYPE::FRONT_FLIGHT)
			{
				CGameObject* pAfterImg = CPlayer_AfterImg::Create(m_pGraphicDev, this);
				m_listAfterImg.push_back(pAfterImg);
			}
		}
		
		++m_iCreateAfterImg;
		if (m_iCreateAfterImg >= 100)
			m_iCreateAfterImg = 0;
	}
	else
	{
		if (!m_listAfterImg.empty())
		{
			for (auto iter : m_listAfterImg)
			{
				CEventMgr::GetInstance()->Delete_Obj(iter);
			}
			m_listAfterImg.clear();
		}
		m_iCreateAfterImg = 0;
	}
	

	
	__super::LateUpdate_Object();
}

void CPlayer::Render_Object()
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	if(m_bHit && m_tStatInfo.fCurDef <= 0)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));
	else if (m_bHit && m_tStatInfo.fCurDef > 0)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 199, 144));

	if(m_eClass == CLASS_TYPE::NINJA)
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iClockAlpha, 255, 255, 255));

	m_pStateMachineCom->Render_StateMachine();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object(); 
}

void CPlayer::OnCollision_Enter(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vMyPos = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		CloseTarget_Dis(_pColObj);

		if (Is_Attack())
		{
			Regen_Mana();
			if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK3)
			{
				dynamic_cast<CMonster*>(_pColObj)->Damaged(m_tStatInfo.fAD + 10, this);

			}
			else
			{
				dynamic_cast<CMonster*>(_pColObj)->Damaged(m_tStatInfo.fAD + (rand() % 10), this);
				CCameraMgr::GetInstance()->Shake_Camera();

			}
		}
		if (Is_Skill())
		{
			for (auto iter : m_arrSkillSlot)
			{
				if (nullptr != iter && iter->Is_Active())
				{
					dynamic_cast<CMonster*>(_pColObj)->Damaged(dynamic_cast<CSkill*>(iter)->Get_SkillDamage(), this);
				}
			}

		}

		/*if (_pColObj->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
		{
			_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}*/
		
	}
	break;
	case Engine::OBJ_TYPE::RANGE_OBJ:
	{
		if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_ID() == OBJ_ID::SKILL_BOSS_FULLDOWN)
		{
			m_pRigidBodyCom->Knock_Up(500);
		}
		if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_Type() == OBJ_TYPE::MONSTER)
		{
			CloseTarget_Dis(dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj());

			if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
				m_bIsBoss = true;
			else
				m_bIsBoss = false;
		}
	

	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vNewPos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();
		vNewPos.y = 0.f;

		m_pTransformCom->Set_Pos(vMyPos + vNewPos);
	}
	break;
	case Engine::OBJ_TYPE::NPC:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		// 대화 가능 UI
		// if (!m_bIsTalking)
		// {
		// 	if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT
		// 		&& dynamic_cast<CNpc*>(_pColObj)->Get_ReadyTalk() == true) {
		// 		CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
		// 			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
		// 
		// 		m_pEnterUI->EnterUI_On(UIENTER_TYPE::CHAT, _pColObj);
		// 	}
		// } 
		// else
		// {
		// 	CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
		// 		(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
		// 	m_pEnterUI->EnterUI_Off();
		// }

	}
	case Engine::OBJ_TYPE::ITEM:
	{
		if (_pColObj->Get_ID() == OBJ_ID::ITEM_EXP)
			Set_CurExp(m_tStatInfo.fCurExp + static_cast<CItem*>(_pColObj)->Get_ItemValue());
		if (_pColObj->Get_ID() == OBJ_ID::ITEM_GOLD)
			Set_Gold(m_tStatInfo.fGold + static_cast<CItem*>(_pColObj)->Get_ItemValue());
	}
		break;
	case Engine::OBJ_TYPE::PROJECTILE:
		break;
	case Engine::OBJ_TYPE::CAMERA:
		break;
	case Engine::OBJ_TYPE::ENVIRONMENT:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		_pColObj->Set_EventSwitch(true);
		_pColObj->Set_IsEnter(true);

		// 입장 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::ENTER, _pColObj);
		}
		// 탐색 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
		}
	}
	break;
	default:
		break;
	}
}

void CPlayer::OnCollision_Stay(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vMyPos  = m_pTransformCom->Get_Info(INFO_POS);
	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);

	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::MONSTER:
	{
		CloseTarget_Dis(_pColObj);

		if (Is_Attack())
		{
			Regen_Mana();
			if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK3)
			{
				dynamic_cast<CMonster*>(_pColObj)->Damaged(m_tStatInfo.fAD + 10, this);
				
			}
			else
			{
				dynamic_cast<CMonster*>(_pColObj)->Damaged(m_tStatInfo.fAD + (rand() % 10), this);
				CCameraMgr::GetInstance()->Shake_Camera();
				
			}
		}
		if (Is_Skill())
		{
			for (auto iter : m_arrSkillSlot)
			{
				if (nullptr != iter && iter->Is_Active())
				{
					dynamic_cast<CMonster*>(_pColObj)->Damaged(dynamic_cast<CSkill*>(iter)->Get_SkillDamage(), this);
				}
			}
			
		}
		
		/*if (_pColObj->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
		{
			_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}*/
	}
	break;
	case Engine::OBJ_TYPE::RANGE_OBJ:
	{
		if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_ID() == OBJ_ID::SKILL_BOSS_FULLDOWN)
		{
			m_pRigidBodyCom->Knock_Up(500);
		}
		if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_Type() == OBJ_TYPE::MONSTER)
		{
			CloseTarget_Dis(dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj());

			if (dynamic_cast<CRangeObj*>(_pColObj)->Get_OwnerObj()->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
				m_bIsBoss = true;
			else
				m_bIsBoss = false;
		}
		


	}
	break;
	case Engine::OBJ_TYPE::LINE:
	{
		_vec3 vNewPos = static_cast<CLineCollider*>(_pColObj->Get_Collider())->Get_Overlap_Line();
		vNewPos.y = 0.f;

		m_pTransformCom->Set_Pos(vMyPos + vNewPos);
	}
	break;
	case Engine::OBJ_TYPE::NPC:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO)
		{
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}
		// 대화 가능 UI
		if (!m_bIsTalking)
		{
			if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT
				&& dynamic_cast<CNpc*>(_pColObj)->Get_ReadyTalk() == true) 
			{
				CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
					(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

				m_pEnterUI->EnterUI_On(UIENTER_TYPE::CHAT, _pColObj);
			}
		}
		else
		{
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));
		
			m_pEnterUI->EnterUI_Off();
		}
	}
	break;
	case Engine::OBJ_TYPE::ITEM:
	{
		// ? UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_QUESTION) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::QUESTION, _pColObj);
		}

	}
		break;
	case Engine::OBJ_TYPE::PROJECTILE:
		break;
	case Engine::OBJ_TYPE::CAMERA:
		break;
	case Engine::OBJ_TYPE::ENVIRONMENT:
	{
		_vec3 vOverlap = static_cast<CRectCollider*>(m_pColliderCom)->Get_Overlap_Rect();

		if (_pColObj->Get_EnterType() == ENTER_TYPE::ENTER_NO) {
			if (vOverlap.x > vOverlap.z)
			{
				if (vMyPos.z < vColPos.z)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z - vOverlap.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x,
													vMyPos.y,
													vMyPos.z + vOverlap.z });
			}
			else
			{
				if (vMyPos.x < vColPos.x)
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x - vOverlap.x,
													vMyPos.y,
													vMyPos.z });
				else
					m_pTransformCom->Set_Pos(_vec3{ vMyPos.x + vOverlap.x,
													vMyPos.y,
													vMyPos.z });
			}
		}

		// 입장 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::ENTER, _pColObj);
		}
		// 탐색 가능 UI
		if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT) {
			CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
				(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

			m_pEnterUI->EnterUI_On(UIENTER_TYPE::INSPECT, _pColObj);
		}
	}
	break;
	default:
		break;
	}
}

void CPlayer::OnCollision_Exit(CGameObject* _pColObj)
{
	if (STATE_TYPE::FRONT_FLIGHT == m_pStateMachineCom->Get_CurState() && _pColObj->Get_ID() != OBJ_ID::LINE)
		return;

	_vec3 vColPos = _pColObj->Get_Transform()->Get_Info(INFO_POS);


	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::RANGE_OBJ:
		m_bIsMonster = false;
		m_fMonTargetLength = 99.f;
		m_pMonTarget = nullptr;
		Set_PlayerDirNormal(m_vMonTargetDir);
		break;
	default:
		break;
	}

	_pColObj->Set_IsEnter(false);

	// 부쉬면 Event 한번 더 진행
	if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ALPHA)
		_pColObj->Set_EventSwitch(true);

	// UI 끄기
	if (_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_ENTER ||
		_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_INSPECT ||
		_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_CHAT ||
		_pColObj->Get_InterType() == INTERACTION_TYPE::INTERACTION_QUESTION)
	{
		CEnterUI* m_pEnterUI = static_cast<CEnterUI*>
			(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Enter"));

		m_pEnterUI->EnterUI_Off();
	}
}

const _bool CPlayer::Is_Jump() const
{
	NULL_CHECK_RETURN(m_pRigidBodyCom, FALSE);

	return m_pRigidBodyCom->Is_Jump();
}
HRESULT CPlayer::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pStateMachineCom = dynamic_cast<CStateMachine*>(Engine::Clone_Proto(COMPONENT_TYPE::STATEMACHINE, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::STATEMACHINE, pComponent);

	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	for (_uint i = 0; i < _uint(CLASS_TYPE::TYPEEND); ++i)
	{
		pComponent = m_pClassAnimator[i] = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);
	}

	pComponent = m_pRigidBodyCom = dynamic_cast<CRigidBody*>(Engine::Clone_Proto(COMPONENT_TYPE::RIGIDBODY, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::RIGIDBODY, pComponent);



#pragma region Texture
	// Normal
	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Ninja
	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pNinjaTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight_Ninja", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Mage
	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pMageTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Thorn
	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fIdle_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWalk_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fRoll_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack1_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack2_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_HIT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fHit_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_IDLE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bIdle_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_WALK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bWalk_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_ROLL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bRoll_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack1_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_bAttack2_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_WAKE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fWake_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_DIE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fDie_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_SLEEP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fSleep_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_FLIGHT)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fFlight_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pThornTextureCom[_uint(STATE_TYPE::FRONT_ATTACK3)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Player_fAttack3_Thorn", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
#pragma endregion


	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	/*if (CInputDev::GetInstance()->Key_Down(VK_F9))
	{
		CBossSceneMgr::GetInstance()->Start_BossScene();
	}*/

	/*if (CInputDev::GetInstance()->Key_Down(VK_F8))
	{
		CGameObject* pMon = CTurretSkull::Create(m_pGraphicDev);
		NULL_CHECK(pMon);
		CEventMgr::GetInstance()->Add_Obj(L"Monster_Skull", pMon);
	}*/

	if (CInputDev::GetInstance()->Key_Down('Q'))
		m_bhasFlight = true;

	if (CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView() &&
		CInputDev::GetInstance()->Key_Down(VK_LSHIFT))// Jump Test
	{
		CSoundMgr::GetInstance()->PlaySoundW(L"cat_jump.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_WALK);
		m_pRigidBodyCom->Jump();
	}
		
	if (CInputDev::GetInstance()->Key_Down('R'))
	{
		if(m_tStatInfo.fCurHP < m_tStatInfo.fMaxHP ||
			m_tStatInfo.fCurMP < m_tStatInfo.fMaxMP)
				m_pSkillHeal->Play();
	}

	if (CInputDev::GetInstance()->Key_Down(VK_F1))
	{
		Class_Change(CLASS_TYPE::NINJA);
	}
	else if (CInputDev::GetInstance()->Key_Down(VK_F2))
	{
		Class_Change(CLASS_TYPE::MAGE);
	}
	else if (CInputDev::GetInstance()->Key_Down(VK_F3))
	{
		Class_Change(CLASS_TYPE::THORN);
	}
	else if (CInputDev::GetInstance()->Key_Down(VK_F4))
	{
		Class_Change(CLASS_TYPE::NORMAL);
	}


	if (CInputDev::GetInstance()->Key_Down('1') &&
		m_arrSkillSlot[0] != nullptr && !m_arrSkillSlot[0]->Is_Active() &&
		m_arrSkillSlot[0]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[0]->Play();
		Using_Mana(m_arrSkillSlot[0]->Get_SkillUsage());
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('2') &&
		m_arrSkillSlot[1] != nullptr && !m_arrSkillSlot[1]->Is_Active() &&
		m_arrSkillSlot[1]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[1]->Play();
		Using_Mana(m_arrSkillSlot[1]->Get_SkillUsage());
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('3') &&
		m_arrSkillSlot[2] != nullptr && !m_arrSkillSlot[2]->Is_Active() && 
		m_arrSkillSlot[2]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[2]->Play();
		Using_Mana(m_arrSkillSlot[2]->Get_SkillUsage());
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}
	else if (CInputDev::GetInstance()->Key_Down('4') &&
		m_arrSkillSlot[3] != nullptr && !m_arrSkillSlot[3]->Is_Active() &&
		m_arrSkillSlot[3]->Get_SkillUsage() <= m_tStatInfo.fCurMP)
	{
		m_arrSkillSlot[3]->Play();
		Using_Mana(m_arrSkillSlot[3]->Get_SkillUsage());
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_IDL_TO_ATK);
	}



	if (m_eClass == CLASS_TYPE::MAGE && m_bFly)
	{
		if (CInputDev::GetInstance()->Key_Down('Z'))
		{
			if (!m_pSkillFly->Is_Active())
			{
				m_pSkillFly->Set_Active(true);
			}
			else
			{
				m_pSkillFly->Get_Transform()->Set_Pos(m_pTransformCom->Get_Info(INFO::INFO_POS));
				m_pSkillFly->Set_Active(false);
			}
		}
	}
	if (m_eClass == CLASS_TYPE::MAGE)
	{
		if (CInputDev::GetInstance()->Key_Down('X'))
		{
			if (!m_pSkillArrow->Is_Active())
			{
				m_pSkillArrow->Set_Active(true);
				m_bLockOn = true;
			}
			else
			{
				m_pSkillArrow->Set_Active(false);
				m_bLockOn = false;
			}
		}
	}

	/*if (CInputDev::GetInstance()->Key_Down('T'))
	{
		CGameObject* pGameObject = CQuest_DialogUI::Create(m_pGraphicDev, L"다메 다메 다메요 다메 다메요.\n아나따와 스끼데 스끼 스끼데.");
		CEventMgr::GetInstance()->Add_Obj(L"UI_QuestDialog", pGameObject);
	}*/

	if (CInputDev::GetInstance()->Key_Down('L'))
		Set_CurHP(m_tStatInfo.fMaxHP);
	if (CInputDev::GetInstance()->Key_Down('K'))
		Set_CurMP(m_tStatInfo.fMaxMP);
	if (CInputDev::GetInstance()->Key_Down('N'))
		Set_MoveSpeed(50.f);
	if (CInputDev::GetInstance()->Key_Down('M'))
		Set_MoveSpeed(20.f);
	if (CInputDev::GetInstance()->Key_Down('I'))
		Set_AD(100.f);
	if (CInputDev::GetInstance()->Key_Down('O'))
		Set_AD(10.f);
		
}

void CPlayer::Regen_Def(const _float& fTimeDelta)
{
	if (m_tStatInfo.fCurDef < m_tStatInfo.fMaxDef)
	{
		m_fAccDef += fTimeDelta;
		if (m_fAccDef > 12.f)
		{
			_float fRegenDef = m_tStatInfo.fCurDef + 20;
			if (fRegenDef > m_tStatInfo.fMaxDef)
				fRegenDef = m_tStatInfo.fMaxDef;
			Set_CurDef(fRegenDef);
			m_fAccDef = 0.f;
		}
	}
}

void CPlayer::Clocking_Time(const _float& fTimeDelta)
{
	if (m_eClass == CLASS_TYPE::NINJA && !m_bClocking)
	{
		if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK1 ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK2 ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ATTACK ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ATTACK1 ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ATTACK2 ||
			m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_HIT ||
			true == m_bIsTalking ||
			true == m_bSkill)
		{
			m_fClockingAcc = 0.f;
			m_iClockAlpha = 255;
		}
			
		m_fClockingAcc += fTimeDelta;
		{
			if (m_fClockingAcc > 0.02f)
			{
				m_fClockingAcc = 0.f;
				m_iClockAlpha -= 1;
			}
		}
		
		if (m_iClockAlpha <= 128)
		{
			m_iClockAlpha = 128;
			m_fClockingAcc = 0.f;
			m_bClocking = true;
		}

	}
}

void CPlayer::Create_ThornSparkle(const _float& fTimeDelta)
{
	if (m_eClass == CLASS_TYPE::THORN && m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WALK ||
		m_eClass == CLASS_TYPE::THORN && m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_WALK)
	{
		m_fThornAcc += fTimeDelta;
		if (m_fThornAcc > 0.3f)
		{
			CEffect* pEffect = CEffect_ThornSparkle::Create(m_pGraphicDev, m_pTransformCom->Get_Info(INFO::INFO_POS));
			NULL_CHECK(pEffect);
			CEventMgr::GetInstance()->Add_Obj(L"Effect_ThornSparkle", pEffect);

			m_fThornAcc = 0.f;
		}
	}
}

void CPlayer::LevelUp()
{
	if (m_tStatInfo.fCurExp >= m_tStatInfo.fMaxExp)
	{
		Set_MaxExp(m_tStatInfo.fMaxExp + 25);
		Set_CurExp(0.f);
		Set_Level(m_tStatInfo.iLevel + 1);
		Set_MaxHP(m_tStatInfo.fMaxHP + 4);
		Set_CurHP(m_tStatInfo.fMaxHP);
		Set_AD(m_tStatInfo.fAD + 1.f);
		m_pEffectShine->Play_Effect(vec3.one);
		m_pEffectBanner->Play_Effect(vec3.one);
		CSoundMgr::GetInstance()->PlaySoundW(L"skill_purrserk.wav", CHANNEL_ID::EFFECT_5, VOLUME_PLAYER_LEVEL);
	}
}

void CPlayer::CloseTarget_Dis(CGameObject* pTarget)
{
	_vec3 vTargetDir = pTarget->Get_Transform()->Get_Info(INFO::INFO_POS) - m_pTransformCom->Get_Info(INFO::INFO_POS);
	_float fTargetLength = D3DXVec3Length(&vTargetDir);
	

	if (m_fMonTargetLength >= fTargetLength)
	{
		m_fMonTargetLength = fTargetLength;
		D3DXVec3Normalize(&m_vMonTargetDir, &vTargetDir);
		m_vMonTargetDir.y = 0;
		m_pMonTarget = pTarget;
		m_bIsMonster = true;
	}
}

CGameObject* CPlayer::MageBall_Target()
{
	multimap<const _tchar*, CGameObject*> pMapMon = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();
	m_pBallTarget = nullptr;

	for (auto iter : pMapMon)
	{
		_vec3 PlayerPos = m_pTransformCom->Get_Info(INFO::INFO_POS);
		_vec3 MonPos = iter.second->Get_Transform()->Get_Info(INFO::INFO_POS);
		_vec3 TargetDir = MonPos - PlayerPos;

		_float fLength = D3DXVec3Length(&TargetDir);

		if (m_fBallTargetLenght > fLength)
		{
			if (m_fBallTargetLenght - fLength > 1)
			{
				m_fBallTargetLenght = fLength;
				m_pBallTarget = iter.second;
				D3DXVec3Normalize(&m_vBallDir, &TargetDir);
				m_vBallDir.y = 0;
			}
		}
	}
	if (m_pBallTarget != nullptr)
	{
		m_fBallTargetLenght = 22.f;
		return m_pBallTarget;
	}
	else
	{
		m_fBallTargetLenght = 22.f;
		return nullptr;
	}
}

_bool CPlayer::Is_BallTarget()
{
	if (m_pBallTarget != nullptr) 
		return true; 
	else 
		return false;
}

CGameObject* CPlayer::Get_MonTarget()
{
	if (m_pMonTarget != nullptr && m_pMonTarget->Is_Active())
		return m_pMonTarget;
	else
		return nullptr;
}

void CPlayer::Set_PlayerLook(const _vec3& vDir)
{
	if(vDir.x < 0)
		m_pTransformCom->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
	if (vDir.x > 0)
		m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
}

void CPlayer::Set_PlayerDirNormal(const _vec3& vDir)
{
#pragma region MyTrashCode
	//_float horizontalX = vDirA.x;
	//_float horizontalZ = vDirA.z;

	//_vec3 resultDir;

	//if (horizontalX > 0.f && horizontalX <= 1.f && horizontalZ > 0.f && horizontalZ <= 1.f)
	//	resultDir = (_vec3(1.f, 0.f, 1.f)); // 오른쪽 뒤 대각선
	//else if (horizontalX >= 0.f && horizontalX < 1.f && horizontalZ < -0.f && horizontalZ <= -1.f)
	//	resultDir = (_vec3(1.f, 0.f, -1.f)); // 오른쪽 앞 대각선
	//else if (horizontalX < -0.f && horizontalX <= -1.f && horizontalZ > 0.f && horizontalZ <= 1.f)
	//	resultDir = (_vec3(-1.f, 0.f, 1.f)); // 왼쪽 뒤 대각선
	//else if (horizontalX < -0.f && horizontalX <= -1.f && horizontalZ < -0.f && horizontalZ <= -1.f)
	//	resultDir = (_vec3(-1.f, 0.f, -1.f)); // 왼쪽 앞 대각선
	//else if (horizontalX >= 0.f)
	//	resultDir = (_vec3(1.f, 0.f, 0.f)); // 오른쪽
	//else if (horizontalX <= -0.f)
	//	resultDir = (_vec3(-1.f, 0.f, 0.f)); // 왼쪽
	//else if (horizontalZ >= 0.f)
	//	resultDir = (_vec3(0.f, 0.f, 1.f)); // 뒤쪽
	//else if (horizontalZ <= -0.f)
	//	resultDir = (_vec3(0.f, 0.f, -1.f)); // 앞쪽
	//else
	//	resultDir = (_vec3(vDirA.x, 0.f, vDirA.z));

	//m_pTransformCom->Set_Dir(resultDir);
	//Set_PlayerLook(resultDir);
#pragma endregion

	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL)
		return;

	_vec3 vDirA = vDir;

	float absX = fabs(vDir.x);
	float absY = fabs(vDir.y);
	float absZ = fabs(vDir.z);

	// 가장 큰 성분을 찾습니다.
	float maxComponent = max(max(absX, absY), absZ);

	// 가장 큰 성분의 부호에 따라 해당 방향으로 매핑.
	if (maxComponent == absX) {
		vDirA.x = (vDirA.x > 0) ? 1.0f : -1.0f;
		vDirA.y = vDirA.z = 0;
	}
	else if (maxComponent == absY) {
		vDirA.y = (vDirA.y > 0) ? 1.0f : -1.0f;
		vDirA.x = vDirA.z = 0;
	}
	else {
		vDirA.z = (vDirA.z > 0) ? 1.0f : -1.0f;
		vDirA.x = vDirA.y = 0;
	}

	// 다시 한 번 정규화
	float length = sqrt(vDirA.x * vDirA.x + vDirA.y * vDirA.y + vDirA.z * vDirA.z);
	vDirA.x /= length;
	vDirA.y = 0;
	vDirA.z /= length;

	m_pTransformCom->Set_Dir(vDirA);
	//Set_PlayerLook(vDirA);
}

void CPlayer::Regen_HP(const _float& fHeal)
{
	if (m_tStatInfo.fCurHP > 0 && m_tStatInfo.fCurHP < m_tStatInfo.fMaxHP ||
		m_tStatInfo.fCurMP >= 0 && m_tStatInfo.fCurMP < m_tStatInfo.fMaxMP)
	{
		_float fRegenHeal = m_tStatInfo.fCurHP + fHeal;
		if (fRegenHeal > m_tStatInfo.fMaxHP)
			fRegenHeal = m_tStatInfo.fMaxHP;

		Set_CurHP(fRegenHeal);
		Set_CurMP(m_tStatInfo.fMaxMP);

		CGameObject* pEffect = CEffect_Font::Create(m_pGraphicDev, this, fHeal, FONT_TYPE::HEAL);
		NULL_CHECK(pEffect);
		CEventMgr::GetInstance()->Add_Obj(L"Effect_Font", pEffect);
	}

}

void CPlayer::Regen_Mana()
{
	Set_CurMP(m_tStatInfo.fCurMP += 0.5f);

	if (m_tStatInfo.fCurMP >= m_tStatInfo.fMaxMP)
		Set_CurMP(m_tStatInfo.fMaxMP);
}

void CPlayer::Using_Mana(const _uint& iUsage)
{
	Set_CurMP(m_tStatInfo.fCurMP - iUsage);

	if (m_tStatInfo.fCurMP <= 0)
		Set_CurMP(0);

}

void CPlayer::Class_Change(const CLASS_TYPE& _eType)
{
	switch (_eType)
	{
	case CLASS_TYPE::NORMAL:
		m_eClass = CLASS_TYPE::NORMAL;
		m_tMoveInfo.fMoveSpeed = 20.f;
		m_bClocking = false;
		m_pSkillFly->Set_Active(false);
		m_pSkillArrow->Set_Active(false);
		m_pEffectOra->Set_Active(false);
		m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
		break;
	case CLASS_TYPE::NINJA:
		m_eClass = CLASS_TYPE::NINJA;
		m_bClocking = true;
		m_iClockAlpha = 128.f;
		m_pSkillFly->Set_Active(false);
		m_pSkillArrow->Set_Active(false);
		m_pEffectOra->Set_Active(false);
		m_tMoveInfo.fMoveSpeed = 25.f;

		m_pStateMachineCom->Set_Animator(m_pClassAnimator[_uint(CLASS_TYPE::NINJA)]);
		break;
	case CLASS_TYPE::MAGE:
		m_eClass = CLASS_TYPE::MAGE;
		m_tMoveInfo.fMoveSpeed = 20.f;
		m_bClocking = false;
		m_pEffectOra->Set_Active(false);
		m_pStateMachineCom->Set_Animator(m_pClassAnimator[_uint(CLASS_TYPE::MAGE)]);
		break;
	case CLASS_TYPE::THORN:
		m_eClass = CLASS_TYPE::THORN;
		m_tMoveInfo.fMoveSpeed = 20.f;
		m_bClocking = false;
		m_pSkillFly->Set_Active(false);
		m_pSkillArrow->Set_Active(false);
		m_pEffectOra->Set_Active(true);
		m_pStateMachineCom->Set_Animator(m_pClassAnimator[_uint(CLASS_TYPE::THORN)]);
		break;
	default:
		break;
	}
}

void CPlayer::Damaged(const _float& fDamage, CGameObject* pObj)
{
	NULL_CHECK(pObj);

	if (m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_DIE ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_WAKE ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ROLL ||
		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BACK_ROLL)
		return;

	if (pObj->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
	{
		if (static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::MONATTACK ||
			static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BOSS_ATTACK2 ||
			static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BOSS_ATTACK3 ||
			static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BACK_MONATTACK ||
			static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BOSS_BACK_ATTACK2 ||
			static_cast<CMonster*>(pObj)->Get_StateMachine()->Get_CurState() == STATE_TYPE::BOSS_BACK_ATTACK3)
		{
			if (!m_pRigidBodyCom->Is_Vel_Zero() || m_pStateMachineCom->Get_CurState() == STATE_TYPE::FRONT_ATTACK3 || m_bFly)
			{
				m_pRigidBodyCom->Zero_KnockBack();
			}
			else
			{
				_vec3 vDir = m_pTransformCom->Get_Dir();
				vDir *= -1;

				if (pObj != nullptr)
					m_pRigidBodyCom->Knock_Back(vDir, 320);
			}

		}
	}

	if (pObj->Get_Type() == OBJ_TYPE::PROJECTILE)
	{

		if (static_cast<CProjectile*>(pObj)->Get_Owner() != nullptr &&
			static_cast<CProjectile*>(pObj)->Get_Owner()->Get_ID() == OBJ_ID::MONSTER_VIOLETDRAGON)
		{
			if (!m_pRigidBodyCom->Is_Vel_Zero())
			{
				m_pRigidBodyCom->Zero_KnockBack();
			}
			else
			{
				if (pObj != nullptr)
					m_pRigidBodyCom->Knock_Back(pObj, 220);
			}
		}
	}



	CGameObject* pEffect = CEffect_Font::Create(m_pGraphicDev, this, fDamage, FONT_TYPE::HIT);
	NULL_CHECK(pEffect);
	CEventMgr::GetInstance()->Add_Obj(L"Effect_Font", pEffect);


	if (m_tStatInfo.fCurDef > 0)
	{
		Set_CurDef(m_tStatInfo.fCurDef - fDamage);
		m_bHit = true;
	}
	else
	{
		if (m_tStatInfo.fCurHP <= 1)
		{
			Set_CurHP(0);
			m_tStatInfo.bDead = true;
		}
		else
		{
			Set_CurHP(m_tStatInfo.fCurHP - fDamage);
			m_bHit = true;
		}
	}
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Free()
{

	__super::Free();
}