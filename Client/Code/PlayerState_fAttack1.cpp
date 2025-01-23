#include "PlayerState_fAttack1.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

#include "Mage_Bullet.h"

#include "SoundMgr.h"

CPlayerState_fAttack1::CPlayerState_fAttack1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev), m_bAttackContinue(false)
{
}

CPlayerState_fAttack1::~CPlayerState_fAttack1()
{
}

HRESULT CPlayerState_fAttack1::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_ATTACK1;
	m_bIsTarget = false;
	return S_OK;
}

STATE_TYPE CPlayerState_fAttack1::Update_State(const _float& fTimeDelta)
{
	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		m_bEnter = false;
		return STATE_TYPE::FRONT_DIE;
	}

	if (!m_bEnter)
	{
		if (CLASS_TYPE::MAGE != static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass())
		{
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
			CEventMgr::GetInstance()->Add_Obj(L"Player_Slash_Chopping", CPlayerSlash::Create(
				m_pGraphicDev, m_pOwner->Get_OwnerObject(), true
			));
			CSoundMgr::GetInstance()->PlaySoundW(L"woosh.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_ATTACK);
		}
		else
		{
			if (!static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_FlySkill()->Is_Active())
			{
				CGameObject* pMon = static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallTarget();
				_vec3 vPlayerPos = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
				CProjectile* pBullet = CMage_Bullet::Create(m_pGraphicDev, vPlayerPos, pMon, m_pOwner->Get_OwnerObject());
				CEventMgr::GetInstance()->Add_Obj(L"Projectile_Mage_Bullet", pBullet);
				CSoundMgr::GetInstance()->PlaySoundW(L"magic_appear.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_ATTACK);
			}
			else
			{
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_FlySkill()->Play();
			}
		}

		if (CLASS_TYPE::NINJA == static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass())
		{
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Off_Clocking();
		}

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
			m_bIsTarget = true;
		else
			m_bIsTarget = false;

		m_bAttackContinue = false;

		m_bEnter = true;
	}

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly())
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * -3.f);
	}
	else
	{
		if (!m_bIsTarget)
		{
			if (CLASS_TYPE::MAGE == static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass())
			{
				if (nullptr == static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallTarget())
					m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * -3.f);
				else
				{
					m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallDir(), fTimeDelta * -3.f);
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallDir());
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerDirNormal(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallDir());
				}
			}
			else
				m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
		}
		else
		{
			if (CLASS_TYPE::MAGE == static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass())
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir(), fTimeDelta * -3.f);
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
			}
			else
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir(), fTimeDelta * 0.1f);
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
			}
		}
	}
	
	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		if(!static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly())
			CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		m_bEnter = false;
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd() && static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly() &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_FlySkill()->Is_Active())
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_FLIGHT;
	}
	else if (m_pOwner->Is_AnimationEnd() && static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly() && !m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_FLIGHT;
	}
	else if (m_pOwner->Is_AnimationEnd() && static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly() && m_bAttackContinue)
	{
		m_bEnter = false;
		if (m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir().z > 0)
			return STATE_TYPE::BACK_ATTACK2;
		else
			return STATE_TYPE::FRONT_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
	{
		m_bEnter = false;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		eState = STATE_TYPE::FRONT_IDLE;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue && !m_bIsTarget &&
		nullptr != static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallTarget() &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallDir().z > 0.5f)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue && !m_bIsTarget &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_LockOn() &&
		m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir().z > 0)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue && m_bIsTarget &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z > 0.5f)
	{
		m_bEnter = false;
		return STATE_TYPE::BACK_ATTACK2;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK2;
	}
		
	

	return eState;
}

void CPlayerState_fAttack1::LateUpdate_State()
{
}

void CPlayerState_fAttack1::Render_State()
{
	//cout << "지금은 앞공격1" << endl;
}

STATE_TYPE CPlayerState_fAttack1::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;


	return m_eState;
}

CPlayerState_fAttack1* CPlayerState_fAttack1::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fAttack1* pInstance = new CPlayerState_fAttack1(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fAttack1State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fAttack1::Free()
{
	__super::Free();
}

