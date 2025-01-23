#include "Ram.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "Engine_Define.h"
#include "SoundMgr.h"

//State
#include "RamState_Patrol.h"
#include "RamState_Chase.h"
#include "RamState_ComeBack.h"
#include "RamState_Attack.h"
#include "RamState_Rest.h"

#include "RamState_bPatrol.h"
#include "RamState_bChase.h"
#include "RamState_bComeBack.h"
#include "RamState_bAttack.h"
#include "RamState_bRest.h"
// Shadow
#include "Shadow_Monster.h"

// Skill
#include "Skill_Monster_Thunder.h"
#include "Skill_Monster_CircleAttack.h"

//Circle Effect
#include "Circle_Stemp.h"

CRam::CRam(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev, OBJ_ID::MONSTER_RAM)
{
}

CRam::CRam(const CMonster& rhs)
	: CMonster(rhs)
{
}

CRam::~CRam()
{
}

HRESULT CRam::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(),E_FAIL);

	// MoveInfo
	m_tMoveInfo.fMoveSpeed  = 3.f;
	m_tMoveInfo.fRotSpeed	= 1.f;

	// Stat Info
	m_tStatInfo.bDead = false;
	m_tStatInfo.fCurHP = 40.f;
	m_tStatInfo.fMaxHP = m_tStatInfo.fCurHP;
	m_tStatInfo.fAD = 10.f;


	// 원래 이미지 크기
	m_vImageSize.x = 1.f;  // 100px = 1.f
	m_vImageSize.y = 1.f;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform 
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 2.5f, m_vImageSize.y * 2.5f, m_vImageSize.z });

	m_pTransformCom->Set_Pos(_vec3{ 110.f, m_pTransformCom->Get_Scale().y, 110.f });

	m_pTransformCom->Set_Dir({ 0.f, 0.f, 1.f });

	//m_vOriginPos = m_pTransformCom->Get_Info(INFO_POS);

	fPatternTime = 2.f;

	m_fAccTime = 0.f;

	m_fJumpingSpeed = 0.05f;
	m_fMaxJumpY = m_pTransformCom->Get_Scale().y + 1.f;

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Monster_Ram_Shadow",
			CShadow_Monster::Create(m_pGraphicDev, this, m_pTransformCom->Get_Scale().y * 0.5f, 1.5f));


	m_bSkill = false;
	m_bBaseSkill = false;

	// 스킬 생성 
	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
	m_pSkill = CSkill_Monster_Thunder::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_pSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Thunder", m_pSkill), E_FAIL);


	m_pBaseSkill = CSkill_Monster_CircleAttack::Create(m_pGraphicDev, this);
	NULL_CHECK_RETURN(m_pBaseSkill, E_FAIL);
	FAILED_CHECK_RETURN(CEventMgr::GetInstance()->Add_Obj(L"Skill_Monster_Base", m_pBaseSkill), E_FAIL);


	}

#pragma region State Add

	CState* pState;

	// Patrol
	pState = CRamState_Patrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::PATROL, pState);

	// Chase
	pState = CRamState_Chase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::CHASE, pState);


	// ComeBack
	pState = CRamState_ComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::COMEBACK, pState);

	// Attack
	pState = CRamState_Attack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONATTACK, pState);

	// Rest
	pState = CRamState_Rest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::MONREST, pState);



	// Back
	// Patrol
	pState = CRamState_bPatrol::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_PATROL, pState);

	// Chase
	pState = CRamState_bChase::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_CHASE, pState);


	// ComeBack
	pState = CRamState_bComeBack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_COMEBACK, pState);

	// Attack
	pState = CRamState_bAttack::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONATTACK, pState);

	// Rest
	pState = CRamState_bRest::Create(m_pGraphicDev, m_pStateMachineCom);
	m_pStateMachineCom->Add_State(STATE_TYPE::BACK_MONREST, pState);



#pragma endregion


#pragma region Anim Add


	CAnimation* pAnimation;

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
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONATTACK)], STATE_TYPE::MONATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::MONREST)], STATE_TYPE::MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::MONREST, pAnimation);


	// Back
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
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)], STATE_TYPE::BACK_MONATTACK, 0.1f, FALSE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONATTACK, pAnimation);

	// Rest
	pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)], STATE_TYPE::BACK_MONREST, 0.1f, TRUE);
	m_pAnimatorCom->Add_Animation(STATE_TYPE::BACK_MONREST, pAnimation);


#pragma endregion


	// 애니메이션, 상태 세팅
	m_pStateMachineCom->Set_Animator(m_pAnimatorCom);
	m_pStateMachineCom->Set_State(STATE_TYPE::PATROL);

	m_szName = L"Monster_Ram";

	return S_OK;
}

_int CRam::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CMonster::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
		m_pStateMachineCom->Set_State(STATE_TYPE::MONREST);
		m_pStateMachineCom->Get_RealAnimator()->Set_Animation(STATE_TYPE::MONREST);
		return iExit;
	}


	// Jumping 
	_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	_float		Y = m_pTransformCom->Get_Scale().y;
	STATE_TYPE	eCurType = m_pStateMachineCom->Get_CurState();


	if (eCurType != STATE_TYPE::MONATTACK && eCurType != STATE_TYPE::BACK_MONATTACK)
	{
		if (vOwnerPos.y < Y || vOwnerPos.y >  m_fMaxJumpY)
		{
			m_fJumpingSpeed *= -1;
		}
		m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);
	}


	// Skill Use Condition
	STATE_TYPE CurState = m_pStateMachineCom->Get_CurState();
	if (STATE_TYPE::BACK_MONATTACK == CurState ||
		STATE_TYPE::MONATTACK == CurState ||
		STATE_TYPE::CHASE == CurState ||
		STATE_TYPE::BACK_CHASE == CurState ||
		STATE_TYPE::MONREST == CurState ||
		STATE_TYPE::BACK_MONREST == CurState)
	{
		m_bSkill = true;		
	}
	else
	{
		m_bSkill = false;
		dynamic_cast<CSkill_Monster_Thunder*>(m_pSkill)->End();
	}
	
	if(m_bSkill == true)
	{
		m_fAccTime += fTimeDelta;
		if (m_fAccTime >= 2.f)
		{
			dynamic_cast<CSkill_Monster_Thunder*>(m_pSkill)->Play();
			if (m_fAccTime >= 3.f)
			{
				dynamic_cast<CSkill_Monster_Thunder*>(m_pSkill)->LatePlay();
				CSoundMgr::GetInstance()->PlaySound(L"skill_lightnyan.wav", CHANNEL_ID::MONSTER_RAM, SOUND_VOLUME_MONSKILL_THUNDER);
				m_fAccTime = 0.f;
				m_bSkill = false;
			}

		}
	}
	



	// Base Skill Use Condition
	if (STATE_TYPE::BACK_MONATTACK == CurState || STATE_TYPE::MONATTACK == CurState)
	{
		if (!m_bBaseSkill)
		{
			m_pBaseSkill->Play();
			m_bBaseSkill = true;
		}

		if (m_pAnimatorCom->Get_CurAniamtion()->Is_End() || this->m_bActive == false)
		{
			m_pBaseSkill->End();
			m_bBaseSkill = false;
		}

	}

	if (STATE_TYPE::BACK_MONATTACK == CurState || STATE_TYPE::MONATTACK == CurState)
	{
		if (m_pAnimatorCom->Get_CurAniamtion()->Get_CurFrame() == 15)
		{
			CEventMgr::GetInstance()->Add_Obj(L"Monster_Ram_Stemp", CCircle_Stemp::Create(m_pGraphicDev, _vec3{ vOwnerPos.x, 0.5f, vOwnerPos.z }));
			if (m_bAttackSound == false)
			{
				CSoundMgr::GetInstance()->PlaySound(L"enemy_impact2.wav", CHANNEL_ID::MONSTER_HEDGEHOG, SOUND_VOLUME_MON_FOOT_ATTACK); // 스킬이 없는 고슴도치껄 사용
				m_bAttackSound = true;
			}
		}
	}
	else
	{
		m_bAttackSound = false;
	}


	return iExit;
}

void CRam::LateUpdate_Object()
{
	//
	//if (m_bSkill)
	//	m_bSkill = false;

	__super::LateUpdate_Object();

}

void CRam::Render_Object()
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


	// 원래 색상 상태로 돌리기 
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	__super::Render_Object(); // 콜라이더 출력
	
}

void CRam::OnCollision_Enter(CGameObject* _pColObj)
{
	__super::OnCollision_Enter(_pColObj);
}

void CRam::OnCollision_Stay(CGameObject* _pColObj)
{
	__super::OnCollision_Stay(_pColObj);
}

void CRam::OnCollision_Exit(CGameObject* _pColObj)
{
	__super::OnCollision_Exit(_pColObj);
}

HRESULT CRam::Add_Component()
{
	CComponent*		pComponent = nullptr;

	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);
	
	// Animator
	pComponent = m_pAnimatorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(COMPONENT_TYPE::ANIMATOR, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::ANIMATOR, pComponent);



#pragma region Texture

	//  Front

	pComponent = m_pTextureCom[_uint(STATE_TYPE::PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Front_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// Back

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_PATROL)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_CHASE)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_COMEBACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONATTACK)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram_Attack", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom[_uint(STATE_TYPE::BACK_MONREST)] = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Back_Ram", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


#pragma endregion




	return S_OK;
}



CRam* CRam::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRam* pInstance = new CRam(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Ram Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRam::Free()
{
	__super::Free();
}
