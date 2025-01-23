#include "VioletDragon.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Player.h"
#include "RangeObj.h"

//State-===
//Front
#include "VioletDragonState_Patrol.h"
#include "VioletDragonState_Chase.h"
#include "VioletDragonState_Attack.h"
#include "VioletDragonState_ComeBack.h"
#include "VioletDragonState_Rest.h"
// Back		
#include "VioletDragonState_bPatrol.h"
#include "VioletDragonState_bChase.h"
#include "VioletDragonState_bAttack.h"
#include "VioletDragonState_bComeBack.h"
#include "VioletDragonState_bRest.h"

// Pattern State===
//FullDown
#include "VioletDragonState_FullDown_Fly.h"
#include "VioletDragonState_FullDown_Down.h"
// ConvergingFire
#include "VioletDragonState_ConvergingFire.h"
#include "VioletDragonState_ConvergingFire_Cast.h"
// BloodyThunder
#include "VioletDragonState_BloodyThunder.h"
#include "VioletDragonState_BloodyThunder_Cast.h"
// Blue Thunder
#include "VioletDragonState_BlueThunder.h"
#include "VioletDragonState_BlueThunder_Cast.h"
// ShootingStar
#include "VioletDragonState_ShootingStar.h"
#include "VioletDragonState_ShootingStarRed.h"
// SpreadBullet
#include "VioletDragonState_SpreadBullet.h"
#include "VioletDragonState_SpreadBullet_Cast.h"
// Create Wyvern
#include "VioletDragonState_CreateWyvern.h"
#include "VioletDragonState_CreateWyvern_Cast.h"
// Dash Attack
#include "VioletDragonState_Dash_Attack.h"
#include "VioletDragonState_Dash_Attack_Back.h"
// Ready Pattern
#include "VioletDragonState_ReadyPattern.h"
//Hell Fire
#include "VioletDragonState_HellFire.h"
#include "VioletDragonState_HellFire_Cast.h"


// 2 Attack
#include "VioletDragonState_Attack2.h"
#include "VioletDragonState_bAttack2.h"
#include "VioletDragonState_Chase2.h"
#include "VioletDragonState_bChase2.h"

// 3 Attack
#include "VioletDragonState_Attack3.h"
#include "VioletDragonState_bAttack3.h"
#include "VioletDragonState_bChase3.h"
#include "VioletDragonState_Chase3.h"

// Near Attack
#include "VioletDragonState_NearAttack1.h"
#include "VioletDragonState_NearAttack2.h"
#include "VioletDragonState_bNearAttack1.h"
#include "VioletDragonState_bNearAttack2.h"



// Intro
#include "VioletDragonState_Intro_Down.h"
#include "VioletDragonState_Intro_Wing.h"
#include "VioletDragonState_Intro_Sword.h"

//Dead
#include "VioletDragonState_Dead.h"

// Watch 
#include "VioletDragonState_Watch_In_Sky.h"
#include "VioletDragonState_Watch_Up.h"
#include "VioletDragonState_Watch_Down.h"



// Effect
#include "Shadow_Monster.h"
#include "Skill_Monster_CircleAttack.h"
#include "Skill_Boss_BlueThunder.h"
#include "Skill_Boss_FullDown.h"
#include "Skill_Boss_BloodyThunder.h"
#include "Skill_Boss_CreatWyvern.h"
#include "BigCircle_Stemp.h"
#include "MonstSpirit.h"
#include "GoldCoin.h"
#include "ExpCoin.h"
#include "Skill_Boss_HellFire.h"
#include "BossHpUI.h"
#include "Management.h"


#include "Shadow_Boss.h"    // 병합 후 주석 풀기


CVioletDragon::CVioletDragon(LPDIRECT3DDEVICE9 pGraphicDev)
    : CMonster(pGraphicDev, OBJ_ID::MONSTER_VIOLETDRAGON)
{
}

CVioletDragon::CVioletDragon(const CMonster& rhs)
    : CMonster(rhs)
{
}

CVioletDragon::~CVioletDragon()
{
}

HRESULT CVioletDragon::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
	{
		CGameObject* pGameObject = CBossHpUI::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		CEventMgr::GetInstance()->Add_Obj(L"BossHp_UI", pGameObject);
		m_pBossHpUI = pGameObject;
	}
	m_bStart = false;

	// MoveInfo
	m_tMoveInfo.fMoveSpeed = 8.f;
	m_tMoveInfo.fRotSpeed = 1.f;

	// Stat Info
	m_tStatInfo.bDead = false;
	m_tStatInfo.fCurHP = 0.f;
	m_tStatInfo.fMaxHP = 2000.f;
	m_tStatInfo.fAD = 10.f;


	m_fFullDownDamage = 50.f;

	m_bHP_90 = false;
	m_bHP_60 = false;
	m_bHP_30 = false;

	// 원래 이미지 크기
	m_vImageSize.x = 5.f;  // 100px = 1.f
	m_vImageSize.y = 5.f;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 2.f, m_vImageSize.y * 2.f , m_vImageSize.z });
	
	m_pTransformCom->Set_Pos(_vec3{ 350.f, m_pTransformCom->Get_Scale().y, 150.f });

	//m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	m_pTransformCom->Set_Dir({ -1.f, 0.f, 1.f });

	fPatternTime = 1.f;
	m_fAccTime = 0.f;
	m_FullDownTime = 0.f;
	m_BloodyTime = 0.f;
	m_CreateTime = 0.f;
	m_BlueTime = 0.f; 
	m_HellTime = 0.f;

	m_fJumpingSpeed = 0.05f;
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;



	m_bSkill = false;
	m_bFullDown = false;
	m_bBloodyTunder = false;
	m_bBloodyLate = false;
	m_bCreatWyvernPlay = false;
	m_bCreatWyvernLate = false;
	m_bBlueTunder = false;
	m_bBlueLate = false;
	m_bNearAttack = false;
	m_bNearAttackCheck = false;

	m_bHellFire = false;
	m_bHellLate = false;
	m_bHellLast = false;
	m_bHellFin = false;
	m_bHellEnd = false;

	m_NearAttackTime = 0.f;
	m_DeadCreatTime = 0.f;
	m_fSoundCount = 0.f;





	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{

		m_pBaseSkill = CSkill_Monster_CircleAttack::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pBaseSkill, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Base", m_pBaseSkill), E_FAIL);

		m_pFullDown = CSkill_Boss_FullDown::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pFullDown, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_FullDown", m_pFullDown), E_FAIL);

		m_pBloodyThunder = CSkill_Boss_BloodyThunder::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pBloodyThunder, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BloodyThunder", m_pBloodyThunder), E_FAIL);

		m_pCreateWyvern = CSkill_Boss_CreateWyvern::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pCreateWyvern, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_Create_Wyvern", m_pCreateWyvern), E_FAIL);


		m_pBlueThunder = CSkill_Boss_BlueThunder::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pBlueThunder, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Boss_BlueThunder", m_pBlueThunder), E_FAIL);


		m_pNearAttack = CSkill_Monster_CircleAttack::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pNearAttack, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Near_Base", m_pNearAttack), E_FAIL);

		m_pHellFire = CSkill_Boss_HellFire::Create(m_pGraphicDev, this);
		NULL_CHECK_RETURN(m_pHellFire, E_FAIL);
		FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_HellFire", m_pHellFire), E_FAIL);


	}


	// Test Pattern
	//
	// Full Down


#pragma region State Add

	CState* pState;
	// Front ==============================
	// Patrol
	pState = CVioletDragonState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CVioletDragonState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CVioletDragonState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CVioletDragonState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

	// Rest
	pState = CVioletDragonState_Rest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONREST, pState);
	

	// Back ================================
	// Patrol
	pState = CVioletDragonState_bPatrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_PATROL, pState);

	// Chase
	pState = CVioletDragonState_bChase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_CHASE, pState);

	// ComeBack
	pState = CVioletDragonState_bComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_COMEBACK, pState);

	// Attack
	pState = CVioletDragonState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONATTACK, pState);

	// Rest
	pState = CVioletDragonState_bRest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONREST, pState);
	


	// Pattern ================================	
	
	// Full Down Pattern =============================
	// FullDown - Fly
	pState = CVioletDragonState_FullDown_Fly::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_FLY, pState);
	
	//FullDown - Move
	//pState = CVioletDragonState_FullDown_Move::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_Move, pState);

	// FullDown - Down
	pState = CVioletDragonState_FullDown_Down::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_FULLDOWN_DOWN, pState);

	
	// Convergint Fire Pattern =========================
	// Converging Fire
	pState = CVioletDragonState_ConvergingFire::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CONVERGING_FIRE, pState);

	// Converging Cast
	pState = CVioletDragonState_ConvergingFire_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CONVERGING_CAST, pState);



	// Bloody Thunder Pattern ==========================
	// Bloody Thunder
	pState = CVioletDragonState_BloodyThunder::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLOODY_THUNDER, pState);
	// Bloody Cast
	pState = CVioletDragonState_BloodyThunder_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLOODY_CAST, pState);


	// Blue Thunder Pattern ==========================
	// Blue Thunder
	pState = CVioletDragonState_BlueThunder::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLUE_THUNDER, pState);
	// Bloody Cast
	pState = CVioletDragonState_BlueThunder_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BLUE_CAST, pState);



	// Shooting Star Pattern ===========================
	// Shooting Star
	pState = CVioletDragonState_ShootingStar::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SHOOTING_STAR, pState);
	// Shooting Red
	pState = CVioletDragonState_ShootingStarRed::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SHOOTING_RED, pState);


	// Spread Bullet Pattern =============================
	// Spread Bullet
	pState = CVioletDragonState_SpreadBullet::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SPREAD_BULLET, pState);
	// Spread Cast
	pState = CVioletDragonState_SpreadBullet_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_SPREAD_CAST, pState);


	// Create Wyvern Pattern ==============================
	// Create Wyvern 
	pState = CVioletDragonState_CreateWyvern::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CREATE_WYVERN, pState);
	// Create Wyvern Cast
	pState = CVioletDragonState_CreateWyvern_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CREATE_CAST, pState);


	// Dash Attack Pattern ==============================
	// Dash Attack
	pState = CVioletDragonState_Dash_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_DASH_ATTACK, pState);
	// Dash Attack Backj
	pState = CVioletDragonState_Dash_Attack_Back::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_DASH_BACK_ATTACK, pState);

	// Ready Pattern
	pState = CVioletDragonState_ReadyPattern::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_READY_PATTERN, pState);



	// 2 Pattern
	pState = CVioletDragonState_Attack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_ATTACK2, pState);

	pState = CVioletDragonState_bAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_ATTACK2, pState);

	pState = CVioletDragonState_Chase2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CHASE2, pState);

	pState = CVioletDragonState_bChase2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_CHASE2, pState);


	// 3 Pattern
	pState = CVioletDragonState_Attack3::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_ATTACK3, pState);

	pState = CVioletDragonState_bAttack3::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_ATTACK3, pState);

	pState = CVioletDragonState_Chase3::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_CHASE3, pState);

	pState = CVioletDragonState_bChase3::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_CHASE3, pState);


	// Near Attack
	// Near 1
	pState = CVioletDragonState_NearAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_NEAR_ATTACK1, pState);
	// Near Back 1
	pState = CVioletDragonState_bNearAttack1::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_NEAR_ATTACK1, pState);
	// Near 2
	pState = CVioletDragonState_NearAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_NEAR_ATTACK2, pState);
	// Near Back 2
	pState = CVioletDragonState_bNearAttack2::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_BACK_NEAR_ATTACK2, pState);


	// Intro  ==========
	// Down
	pState = CVioletDragonState_Intro_Down::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_INTRO_DOWN, pState);
	// Wing
	pState = CVioletDragonState_Intro_Wing::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_INTRO_WING, pState);
	// Sword
	pState = CVioletDragonState_Intro_Sword::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_INTRO_SWORD, pState);


	// Dead
	pState = CVioletDragonState_Dead::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSSDEAD, pState);

	// HellFire
	pState = CVioletDragonState_HellFire::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_HELLFIRE, pState);
	//HellFire Cast
	pState = CVioletDragonState_HellFire_Cast::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_HELLFIRE_CAST, pState);



	//// Watch  ==============
	//pState = CVioletDragonState_Watch_Up::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_WATCH_UP, pState);

	//pState = CVioletDragonState_Watch_Down::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_WATCH_DOWN, pState);

	//pState = CVioletDragonState_Watch_In_Sky::Create(m_pGraphicDev, m_pStateMachineCom);
	//m_pStateMachineCom->Add_State(STATE_TYPE::BOSS_WATCH_IN_SKY, pState);


#pragma endregion



#pragma region Anim Add

	CAnimation* pAnimation;

	// Front ================================
	// Patrol
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::PATROL)], STATE_TYPE::PATROL, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::PATROL, pAnimation);

	// ComeBack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::COMEBACK)], STATE_TYPE::COMEBACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::COMEBACK, pAnimation);

	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::CHASE)], STATE_TYPE::CHASE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::CHASE, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONATTACK)], STATE_TYPE::MONATTACK, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONREST)], STATE_TYPE::MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONREST, pAnimation);


	// Back ====================================
	// Patrol
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)], STATE_TYPE::BACK_PATROL, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_PATROL, pAnimation);

	// ComeBack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)], STATE_TYPE::BACK_COMEBACK, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_COMEBACK, pAnimation);

	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)], STATE_TYPE::BACK_CHASE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_CHASE, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)], STATE_TYPE::BACK_MONATTACK, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)], STATE_TYPE::BACK_MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONREST, pAnimation);



	// Pattern ==================================
	
	// FullDown - Fly
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_FLY)], STATE_TYPE::BOSS_FULLDOWN_FLY, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_FLY, pAnimation);

	// FullDown - Move
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_MOVE)], STATE_TYPE::BOSS_FULLDOWN_MOVE, 0.05f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_MOVE, pAnimation);


	// FullDown - Down
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_DOWN)], STATE_TYPE::BOSS_FULLDOWN_DOWN, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_FULLDOWN_DOWN, pAnimation);



	// Converging Fire
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_FIRE)], STATE_TYPE::BOSS_CONVERGING_FIRE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CONVERGING_FIRE, pAnimation);

	// Converging Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_CAST)], STATE_TYPE::BOSS_CONVERGING_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CONVERGING_CAST, pAnimation);



	// Bloody Thunder
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_THUNDER)], STATE_TYPE::BOSS_BLOODY_THUNDER, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLOODY_THUNDER, pAnimation);

	// Bloody Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_CAST)], STATE_TYPE::BOSS_BLOODY_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLOODY_CAST, pAnimation);


	// Blue Thunder
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLUE_THUNDER)], STATE_TYPE::BOSS_BLUE_THUNDER, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLUE_THUNDER, pAnimation);

	// Blue Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BLUE_CAST)], STATE_TYPE::BOSS_BLUE_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BLUE_CAST, pAnimation);



	
	// Shooting Star
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_STAR)], STATE_TYPE::BOSS_SHOOTING_STAR, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SHOOTING_STAR, pAnimation);
	
	// Shooting Red
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_RED)], STATE_TYPE::BOSS_SHOOTING_RED, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SHOOTING_RED, pAnimation);



	// Spread Bullet 
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_BULLET)], STATE_TYPE::BOSS_SPREAD_BULLET, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SPREAD_BULLET, pAnimation);

	// Spread Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_CAST)], STATE_TYPE::BOSS_SPREAD_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_SPREAD_CAST, pAnimation);


	// Creat Wyvern 
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_WYVERN)], STATE_TYPE::BOSS_CREATE_WYVERN, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CREATE_WYVERN, pAnimation);

	// Creat Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_CAST)], STATE_TYPE::BOSS_CREATE_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CREATE_CAST, pAnimation);


	// Dash Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_DASH_ATTACK)], STATE_TYPE::BOSS_DASH_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_DASH_ATTACK, pAnimation);


	// Dash Attack Back
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_DASH_BACK_ATTACK)], STATE_TYPE::BOSS_DASH_BACK_ATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_DASH_BACK_ATTACK, pAnimation);


	// Ready Pattern
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_READY_PATTERN)], STATE_TYPE::BOSS_READY_PATTERN, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_READY_PATTERN, pAnimation);



	// 2
	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CHASE2)], STATE_TYPE::BOSS_CHASE2, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CHASE2, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_ATTACK2)], STATE_TYPE::BOSS_ATTACK2, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_ATTACK2, pAnimation);


	// bChase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_CHASE2)], STATE_TYPE::BOSS_BACK_CHASE2, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_CHASE2, pAnimation);

	// bAttack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_ATTACK2)], STATE_TYPE::BOSS_BACK_ATTACK2, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_ATTACK2, pAnimation);



	// 3
	// Chase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_CHASE3)], STATE_TYPE::BOSS_CHASE3, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_CHASE3, pAnimation);

	// Attack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_ATTACK3)], STATE_TYPE::BOSS_ATTACK3, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_ATTACK3, pAnimation);


	// bChase
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_CHASE3)], STATE_TYPE::BOSS_BACK_CHASE3, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_CHASE3, pAnimation);

	// bAttack
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_ATTACK3)], STATE_TYPE::BOSS_BACK_ATTACK3, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_ATTACK3, pAnimation);


	// Intro
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_DOWN)], STATE_TYPE::BOSS_INTRO_DOWN, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_INTRO_DOWN, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_WING)], STATE_TYPE::BOSS_INTRO_WING, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_INTRO_WING, pAnimation);

	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_SWORD)], STATE_TYPE::BOSS_INTRO_SWORD, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_INTRO_SWORD, pAnimation);

	// Dead
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSSDEAD)], STATE_TYPE::BOSSDEAD, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSSDEAD, pAnimation);



	// Near Attack
	// 1F 
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_NEAR_ATTACK1)], STATE_TYPE::BOSS_NEAR_ATTACK1, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_NEAR_ATTACK1, pAnimation);
	//1B
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_NEAR_ATTACK1)], STATE_TYPE::BOSS_BACK_NEAR_ATTACK1, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_NEAR_ATTACK1, pAnimation);
	// 2F
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_NEAR_ATTACK2)], STATE_TYPE::BOSS_NEAR_ATTACK2, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_NEAR_ATTACK2, pAnimation);
	//2B
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_NEAR_ATTACK2)], STATE_TYPE::BOSS_BACK_NEAR_ATTACK2, 0.05f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_BACK_NEAR_ATTACK2, pAnimation);

	// Hell Fire
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_HELLFIRE)], STATE_TYPE::BOSS_HELLFIRE, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_HELLFIRE, pAnimation);
	// Hell Fire Cast
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_HELLFIRE_CAST)], STATE_TYPE::BOSS_HELLFIRE_CAST, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_HELLFIRE_CAST, pAnimation);






	// Watch
	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_UP)], STATE_TYPE::BOSS_WATCH_UP, 0.1f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_WATCH_UP, pAnimation);

	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_IN_SKY)], STATE_TYPE::BOSS_WATCH_IN_SKY, 0.1f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_WATCH_IN_SKY, pAnimation);

	//pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_DOWN)], STATE_TYPE::BOSS_WATCH_DOWN, 0.1f, FALSE);
	//m_pAnimatorCom->Add_Animation(STATE_TYPE::BOSS_WATCH_DOWN, pAnimation);






#pragma endregion

	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::BOSS_INTRO_DOWN);


	m_szName = L"Monster_VioletDragon";

	m_bActive = FALSE; // 수정시 팀장 보고

    return S_OK;
}

_int CVioletDragon::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);



	// Position Value
	_vec3 vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);

	if (true == m_tStatInfo.bDead)
	{

		/*	CEventMgr::GetInstance()->Add_Obj(L"Violet_Spirit1", CMonstSpirit::Create(m_pGraphicDev, _vec3{ vOwnerPos.x + 5.f , vOwnerPos.y, vOwnerPos.z }));
			CEventMgr::GetInstance()->Add_Obj(L"Violet_Spirit2", CMonstSpirit::Create(m_pGraphicDev, _vec3{ vOwnerPos.x - 5.f , vOwnerPos.y, vOwnerPos.z }));
			CEventMgr::GetInstance()->Add_Obj(L"Violet_Spirit3", CMonstSpirit::Create(m_pGraphicDev, _vec3{ vOwnerPos.x + 10.f, vOwnerPos.y, vOwnerPos.z - 5.f }));
			CEventMgr::GetInstance()->Add_Obj(L"Violet_Spirit4", CMonstSpirit::Create(m_pGraphicDev, _vec3{ vOwnerPos.x - 10.f, vOwnerPos.y, vOwnerPos.z + 5.f }));
	*/

	// Coin -> 생성 X

	// Near
	//CGameObject* GoldCoin1 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin1);
	//GoldCoin1->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x + 10.f, GoldCoin1->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z });

	//CGameObject* GoldCoin2 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin2);
	//GoldCoin2->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x - 10.f , GoldCoin2->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z });

	//CGameObject* GoldCoin3 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin3);
	//GoldCoin3->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x, GoldCoin3->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z + 10.f });

	//CGameObject* GoldCoin4 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin4);
	//GoldCoin4->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x, GoldCoin4->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z - 10.f });


	//// Far
	//CGameObject* GoldCoin5 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin5);
	//GoldCoin5->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x + 15.f, GoldCoin5->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z + 15.f });

	//CGameObject* GoldCoin6 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin6);
	//GoldCoin6->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x +15.f, GoldCoin6->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z - 15.f });

	//CGameObject* GoldCoin7 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin7);
	//GoldCoin7->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x - 15.f, GoldCoin7->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z + 15.f });

	//CGameObject* GoldCoin8 = CGoldCoin::Create(m_pGraphicDev);
	//CEventMgr::GetInstance()->Add_Obj(L"Item_GoldCoin", GoldCoin8);
	//GoldCoin8->Get_Transform()->Set_Pos({ m_pTransformCom->Get_Info(INFO_POS).x - 15.f, GoldCoin8->Get_Transform()->Get_Info(INFO_POS).y , m_pTransformCom->Get_Info(INFO_POS).z - 15.f });



	// 스킬 삭제
		dynamic_cast<CSkill_Monster_CircleAttack*>(m_pBaseSkill)->End();

		dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->End();
		dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->LateEnd();

		dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->End();
		dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->LateEnd();

		dynamic_cast<CSkill_Boss_FullDown*>(m_pFullDown)->End();

		dynamic_cast<CSkill_Boss_CreateWyvern*>(m_pCreateWyvern)->End();



		// 모든 몬스터 삭제
		multimap<const _tchar*, CGameObject*> pMapMon = CManagement::GetInstance()->Get_Layer(OBJ_TYPE::MONSTER)->Get_ObjectMap();


		for (auto iter : pMapMon)
		{
			dynamic_cast<CMonster*>(iter.second)->Set_Dead();
		}

	}


	if (!m_bStart && this->Is_Active())
	{
		arrRangeObj[(UINT)RANGE_TYPE::BASIC_ATTACK]->Set_Active(true);
		m_pBossHpUI->Set_Active(true);
		Set_CurHP(m_tStatInfo.fMaxHP);
		m_bStart = true;


		// 그림자  
		if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		{
			CEventMgr::GetInstance()->Add_Obj(L"Monster_VioletDragon_Shadow", CShadow_Boss::Create(m_pGraphicDev, this));
		}


	}

	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
		m_pStateMachineCom->Set_State(STATE_TYPE::MONREST);
		m_pStateMachineCom->Get_RealAnimator()->Set_Animation(STATE_TYPE::MONREST);
		return iExit;
	}


	//_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();



	// Base Skill Use Condition
	if (STATE_TYPE::BACK_MONATTACK == CurState || STATE_TYPE::MONATTACK == CurState ||
		STATE_TYPE::BOSS_ATTACK2 == CurState || STATE_TYPE::BOSS_BACK_ATTACK2 == CurState ||
		STATE_TYPE::BOSS_ATTACK3 == CurState || STATE_TYPE::BOSS_BACK_ATTACK3 == CurState  || 
		STATE_TYPE::BOSS_NEAR_ATTACK1 == CurState || STATE_TYPE::BOSS_NEAR_ATTACK2 == CurState||
		STATE_TYPE::BOSS_BACK_NEAR_ATTACK1 == CurState || STATE_TYPE::BOSS_BACK_NEAR_ATTACK2 == CurState)
	{
		if (!m_bSkill)
		{
			m_pBaseSkill->Play();
			m_bSkill = true;
		}
		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 12)
		{
			CSoundMgr::GetInstance()->PlaySound(L"BossAttack.mp3", CHANNEL_ID::MONSTER_BOSS_0, SOUND_VOLUME_MON_FOOT_ATTACK);
		}

		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 15)
		{

		}

		if (m_pAnimatorCom->Get_CurAniamtion()->Is_End() || this->m_bActive == false)
		{

			m_pBaseSkill->End();
			m_bSkill = false;
		}

	}
	else
	{
		m_pBaseSkill->End();
	}


	////  Near Attack 
	//if (STATE_TYPE::BOSS_NEAR_ATTACK1 == CurState || STATE_TYPE::BOSS_BACK_NEAR_ATTACK1 == CurState ||
	//	STATE_TYPE::BOSS_NEAR_ATTACK2 == CurState || STATE_TYPE::BOSS_BACK_NEAR_ATTACK2 == CurState)
	//{
	//	if (false == m_bNearAttack)
	//	{
	//		m_pNearAttack->Play();
	//		m_bNearAttack = true;
	//	}
	//	if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 8)
	//	{
	//		CSoundMgr::GetInstance()->PlaySound(L"BossAttack.mp3", CHANNEL_ID::MONSTER_BOSS_0, SOUND_VOLUME_MON_FOOT_ATTACK);
	//	}
	//	if (m_pAnimatorCom->Get_CurAniamtion()->Is_End() || this->m_bActive == false)
	//	{
	//		m_pNearAttack->End();
	//		m_bNearAttack = false;
	//	}

	//}
	//else
	//{
	//	m_pNearAttack->End();
	//}




	// Full Down Skill Use Condition
	if (STATE_TYPE::BOSS_FULLDOWN_FLY == CurState && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		if (!m_bFullDown)
		{
			m_pFullDown->Play();
			m_bFullDown = true;
		}
	}
	if (STATE_TYPE::BOSS_FULLDOWN_DOWN == CurState && m_pAnimatorCom->Get_CurAniamtion()->Is_End())
	{
		if (m_bFullDown)
		{
			m_pFullDown->End();
			m_bFullDown = false;
		}
	}
	if (STATE_TYPE::BOSS_FULLDOWN_DOWN == CurState )
	{
		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 3)
		{
			CSoundMgr::GetInstance()->PlaySound(L"DragonFullDown2.wav", CHANNEL_ID::MONSTER_BOSS_1, 0.7f);  // fulldown Sound
			CEventMgr::GetInstance()->Add_Obj(L"Monster_Hedgehog_Stemp", CBigCircle_Stemp::Create(m_pGraphicDev, _vec3{ vOwnerPos.x, 0.5f, vOwnerPos.z }));
			


		}
	}


	

	// Bloody Thunder Skill Use Condition
	if ((STATE_TYPE::BOSS_BLOODY_CAST == CurState || STATE_TYPE::BOSS_BLOODY_THUNDER == CurState ))
	{
		m_BloodyTime += fTimeDelta;
		 
		if (m_bBloodyTunder == false &&  m_bBloodyLate == false  &&   m_BloodyTime >= 1.f)
		{
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->Play();
			m_bBloodyTunder = true;
		}
		if ( m_bBloodyTunder == true  &&  m_bBloodyLate == false &&  m_BloodyTime >= 2.f)
		{
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->End();
	
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->LatePlay();
			CSoundMgr::GetInstance()->PlaySound(L"skill_lightnyan.wav", CHANNEL_ID::MONSTER_BOSS_1, SOUND_VOLUME_MONSKILL_THUNDER);
			CCameraMgr::GetInstance()->Shake_Camera(0.15, 40);
			m_bBloodyTunder = false;
			m_bBloodyLate = true;
		}
		if (m_bBloodyTunder == false  &&  m_bBloodyLate == true  && m_BloodyTime >= 3.f)
		{
			CCameraMgr::GetInstance()->Stop_Shake();
			dynamic_cast<CSkill_Boss_BloodyThunder*>(m_pBloodyThunder)->LateEnd();
			m_BloodyTime = 0.f;
		}
		
	}
	else
	{
		m_BloodyTime = 0.f;

		m_bBloodyLate = false;
	}


	// Blue Thunder Skill Use Condition
	if ((STATE_TYPE::BOSS_BLUE_THUNDER == CurState || STATE_TYPE::BOSS_BLUE_CAST == CurState))
	{
		m_BlueTime += fTimeDelta;

		if (m_bBlueTunder == false && m_bBlueLate == false && m_BlueTime >= 1.f)
		{
			dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->Play();
			m_bBlueTunder = true;
		}
		if (m_bBlueTunder == true && m_bBlueLate == false && m_BlueTime >= 2.f)
		{
			dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->End();

			dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->LatePlay();
			CSoundMgr::GetInstance()->PlaySound(L"skill_lightnyan.wav", CHANNEL_ID::MONSTER_BOSS_1, SOUND_VOLUME_MONSKILL_THUNDER);
			CCameraMgr::GetInstance()->Shake_Camera(0.15, 40);
			m_bBlueTunder = false;
			m_bBlueLate = true;
		}
		if (m_bBlueTunder == false && m_bBlueLate == true && m_BlueTime >= 3.f)
		{
			CCameraMgr::GetInstance()->Stop_Shake();
			dynamic_cast<CSkill_Boss_BlueThunder*>(m_pBlueThunder)->LateEnd();
			m_BlueTime = 0.f;
		}

	}
	else
	{
		m_BlueTime = 0.f;
		m_bBlueLate = false;
	}



	// HellFire Skill Use Condition
	if (STATE_TYPE::BOSS_HELLFIRE_CAST == CurState || STATE_TYPE::BOSS_HELLFIRE == CurState)
	{
		m_HellTime += fTimeDelta;

		if (m_bHellFire == false && m_bHellLate == false && m_HellTime >= 1.f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->EarlyPlay();
			m_bHellFire = true;
		}

		if (m_bHellFire == true && m_bHellLate == false && m_HellTime >= 2.f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->Play();
			m_bHellLate = true;
		}


		if (m_bHellLast == false && m_bHellFin == false   && m_HellTime >= 2.5f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->LatePlay();
			m_bHellLast = true;
		}
		if (m_bHellLast == true && m_bHellFin == false &&  m_HellTime >= 3.f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->LastPlay();
			m_bHellFin = true;

		}
		if (m_bHellFin == true && m_bHellEnd == false &&  m_HellTime >= 3.5f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->FinalPlay();
			m_bHellEnd = true;
		}
		if (m_bHellEnd == true && m_HellTime >= 4.f)
		{
			dynamic_cast<CSkill_Boss_HellFire*>(m_pHellFire)->End();
		}
	

	}
	else
	{
	
		m_HellTime = 0.f;
		m_bHellFire = false;
		m_bHellLate = false;
		m_bHellFin = false;
		m_bHellEnd = false;
	}




	// Create Wyvern Skill Use Condition
	if (STATE_TYPE::BOSS_CREATE_CAST == CurState  || STATE_TYPE::BOSS_CREATE_WYVERN == CurState)
	{
		m_CreateTime += fTimeDelta;

		if (m_bCreatWyvernPlay == false && m_bCreatWyvernLate == false)
		{
			dynamic_cast<CSkill_Boss_CreateWyvern*>(m_pCreateWyvern)->Play();
			m_bCreatWyvernPlay = true;
			CSoundMgr::GetInstance()->PlaySound(L"dragon_roar.wav", CHANNEL_ID::MONSTER_BOSS_2, 0.5f);
		}
	
		if (m_bCreatWyvernPlay == true  && m_bCreatWyvernLate == false  && m_CreateTime >= 2.f)
		{
			dynamic_cast<CSkill_Boss_CreateWyvern*>(m_pCreateWyvern)->LatePlay();
			m_bCreatWyvernLate = true;
		}

		if (m_bCreatWyvernPlay == true && m_bCreatWyvernLate == true && m_CreateTime >= 3.f)
		{
			m_CreateTime = 0.f;
			dynamic_cast<CSkill_Boss_CreateWyvern*>(m_pCreateWyvern)->End();
		
		}

	}
	else
	{
		m_CreateTime = 0.f;
		m_bCreatWyvernPlay = false;
		m_bCreatWyvernLate = false;
	}


	_float fSoundVolm = 0.5f;

	if (m_tStatInfo.fCurHP <= m_tStatInfo.fMaxHP * 0.9f  && m_fSoundCount == 0)
	{
		CSoundMgr::GetInstance()->PlaySound(L"dragon_roar2.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);
		m_fSoundCount++;
	}
	if (m_tStatInfo.fCurHP <= m_tStatInfo.fMaxHP * 0.7f && m_fSoundCount == 1)
	{
		CSoundMgr::GetInstance()->PlaySound(L"short_growl.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);
		m_fSoundCount++;
	}
	if (m_tStatInfo.fCurHP <= m_tStatInfo.fMaxHP * 0.5f && m_fSoundCount == 2)
	{
		CSoundMgr::GetInstance()->PlaySound(L"dragon_roar2.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);
		m_fSoundCount++;
	}
	if (m_tStatInfo.fCurHP <= m_tStatInfo.fMaxHP * 0.3f && m_fSoundCount == 3)
	{
		CSoundMgr::GetInstance()->PlaySound(L"short_growl.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);
		m_fSoundCount++;
	}

	if (m_tStatInfo.fCurHP <= m_tStatInfo.fMaxHP * 0.2f && m_fSoundCount == 4)
	{
		CSoundMgr::GetInstance()->PlaySound(L"dragon_roar2.wav", CHANNEL_ID::MONSTER_BOSS_2, fSoundVolm);
		m_fSoundCount++;
	}


	return iExit;
}

void CVioletDragon::LateUpdate_Object()
{

	if (m_tStatInfo.fCurHP <= (m_tStatInfo.fMaxHP * 0.9f))
	{
		m_bHP_90 = true;
	}

	if (m_tStatInfo.fCurHP <= (m_tStatInfo.fMaxHP * 0.6f))
	{
		m_bHP_60 = true;
	}

	if (m_tStatInfo.fCurHP <= (m_tStatInfo.fMaxHP * 0.3f))
	{
		m_bHP_30 = true;
	}

	__super::LateUpdate_Object();
}

void CVioletDragon::Render_Object()
{
	// 피격 시 red
	if (m_bHit)
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(HITCOLOR_A, HITCOLOR_R, HITCOLOR_G, HITCOLOR_B));
	}
	else
	{
		m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pStateMachineCom->Render_StateMachine();

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	__super::Render_Object();

	// 원래 색상 상태로 돌리기 
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	__super::Render_Object(); // 콜라이더 출력
}

void CVioletDragon::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);

	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();


	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{

		if ((STATE_TYPE::BOSS_DASH_ATTACK == CurState || STATE_TYPE::BOSS_DASH_BACK_ATTACK == CurState) &&
			m_pAnimatorCom->Get_CurAniamtion()->Is_End())
		{
			dynamic_cast<CPlayer*>(_pColObj)->Damaged(m_tStatInfo.fAD, this);
		}
	}
	break;

	default:
	{
	}
	break;
	} // Switch end

}

void CVioletDragon::OnCollision_Stay(CGameObject* _pColObj)
{

	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();


	//switch (_pColObj->Get_Type())
	//{
	//case Engine::OBJ_TYPE::PLAYER:
	//{
	//	if ((m_pStateMachineCom->Get_CurState() == STATE_TYPE::BOSS_NEAR_ATTACK1 ||
	//		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BOSS_BACK_NEAR_ATTACK1 ||
	//		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BOSS_NEAR_ATTACK2 ||
	//		m_pStateMachineCom->Get_CurState() == STATE_TYPE::BOSS_BACK_NEAR_ATTACK2))
	//	{
	//		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 8 && m_bNearAttackCheck == false)
	//		{
	//			dynamic_cast<CPlayer*>(_pColObj)->Damaged(m_tStatInfo.fAD, this);
	//			m_bNearAttackCheck = true;
	//		}
	//		
	//	}
	//	else
	//	{
	//		m_bNearAttackCheck = false;
	//	}
	//}
	//break;
	//default:
	//{
	//}
	//break;
	//} // Switch End
	__super::OnCollision_Stay(_pColObj);

}

void CVioletDragon::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CVioletDragon::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Animator
	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);


#pragma region Texture

	// Front ===================================

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Back ==================================

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




	// Pattern ===================================
	
	// Full Down ===========================
	// Full Down Fly
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_FLY)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Fly", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	
	//// Full Down Move
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_MOVE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Fly", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Full Down Down
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_FULLDOWN_DOWN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_FullDown_VioletDragon_Down", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Converging Fire ======================
	// Converging Fire 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_FIRE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); 

	//Converging Fire Cast
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CONVERGING_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_ConvergingFire_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); 


	// Bloody Thunder ===========================
	// Bloody Thunder
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_THUNDER)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); 
	// Bloody Cast
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLOODY_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_BloodyThunder_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); 

	// Blue Thunder ===========================
	// Blue Thunder
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLUE_THUNDER)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	// Blue Cast
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BLUE_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_BlueThunder_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Shooting Star ============================
	// Shooting Star
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_STAR)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	// Shooting Red
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SHOOTING_RED)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); 


	// Spread Bullet ============================
	// Spread Bullet 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_BULLET)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Spread Cast
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_SPREAD_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_SpreadBullet_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요


	// Create Wyvern ===========================
	// Create Wyvern 
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_WYVERN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	// Create Cast
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CREATE_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_BloodyThunder_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요


	// Dash Attack - Front ==============================
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_DASH_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dash_VioletDragon_Front", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요
	//Dash Attack - Back =================================
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_DASH_BACK_ATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dash_VioletDragon_Back", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요

	// Ready Pattern
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_READY_PATTERN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_ReadyPattern_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent); // 텍스처 수정 필요


	// 2
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CHASE2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_CHASE2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// 3
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_ATTACK3)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_ATTACK3)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_CHASE3)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_CHASE3)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Intro
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_DOWN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Intro_Down_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_WING)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Intro_Wing_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_INTRO_SWORD)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Intro_Sword_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Dead
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSSDEAD)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dead_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Near Attack 
	// Near1 Front
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_NEAR_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Near1 Back
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_NEAR_ATTACK1)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Near2 Front
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_NEAR_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	// Near2 Back
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_BACK_NEAR_ATTACK2)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_VioletDragon_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);



	// Hell Fire
	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_HELLFIRE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_VioletDragon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_HELLFIRE_CAST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_SpreadBullet_VioletDragon_Cast", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




	//// Watch
	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_UP)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_WatchUp_VioletDragon", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_IN_SKY)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_WatchInSky_VioletDragon", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	//pComponent = m_pTextureCom[_uint(STATE_TYPE::BOSS_WATCH_DOWN)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_WatchDown_VioletDragon", this));
	//NULL_CHECK_RETURN(pComponent, E_FAIL);
	//m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);




#pragma endregion


	return S_OK;
}



CVioletDragon* CVioletDragon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVioletDragon* pInstance = new CVioletDragon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Violet Dragon Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CVioletDragon::Free()
{
	__super::Free();
}
