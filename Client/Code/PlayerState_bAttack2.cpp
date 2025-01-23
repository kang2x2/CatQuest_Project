#include "PlayerState_bAttack2.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

#include "Mage_Bullet.h"

#include "SoundMgr.h"

CPlayerState_bAttack2::CPlayerState_bAttack2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_bAttack2::~CPlayerState_bAttack2()
{
}

HRESULT CPlayerState_bAttack2::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::BACK_ATTACK2;
	m_bIsTarget = false;
	return S_OK;
}

STATE_TYPE CPlayerState_bAttack2::Update_State(const _float& fTimeDelta)
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
				m_pGraphicDev, m_pOwner->Get_OwnerObject(), false
			));
			CSoundMgr::GetInstance()->PlaySoundW(L"woosh2.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_ATTACK);
		}
		else
		{
			CGameObject* pMon = static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_BallTarget();
			_vec3 vPlayerPos = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS);
			CProjectile* pBullet = CMage_Bullet::Create(m_pGraphicDev, vPlayerPos, pMon, m_pOwner->Get_OwnerObject());
			CEventMgr::GetInstance()->Add_Obj(L"Projectile_Mage_Bullet", pBullet);
			CSoundMgr::GetInstance()->PlaySoundW(L"magic_appear_2.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_ATTACK);
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

	STATE_TYPE eState = Key_Input(fTimeDelta);

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
	{
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		m_bEnter = false;
		return STATE_TYPE::FRONT_HIT;
	}

	if (m_pOwner->Is_AnimationEnd() && static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly())
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_FLIGHT;
	}
	else if (m_pOwner->Is_AnimationEnd() && !m_bAttackContinue)
	{
		m_bEnter = false;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		eState = STATE_TYPE::BACK_IDLE;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass() != CLASS_TYPE::THORN)
	{
		m_bEnter = false;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL);
		return STATE_TYPE::BACK_IDLE;
	}
	else if (m_pOwner->Is_AnimationEnd() && m_bAttackContinue &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_PlayerClass() == CLASS_TYPE::THORN)
	{
		m_bEnter = false;
		return STATE_TYPE::FRONT_ATTACK3;
	}


	return eState;
}

void CPlayerState_bAttack2::LateUpdate_State()
{
}

void CPlayerState_bAttack2::Render_State()
{
	//cout << "지금은 뒤공격2" << endl;
}

STATE_TYPE CPlayerState_bAttack2::Key_Input(const _float& fTimeDelta)
{
	if (!m_pOwner->Is_AnimationEnd() && CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
		m_bAttackContinue = true;

	return m_eState;
}

CPlayerState_bAttack2* CPlayerState_bAttack2::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_bAttack2* pInstance = new CPlayerState_bAttack2(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player bAttack2State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_bAttack2::Free()
{
	__super::Free();
}

