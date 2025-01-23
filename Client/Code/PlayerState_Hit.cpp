#include "PlayerState_Hit.h"

#include "Export_Function.h"
#include "PlayerHitEffect.h"
#include "SoundMgr.h"

CPlayerState_Hit::CPlayerState_Hit(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_Hit::~CPlayerState_Hit()
{
}

HRESULT CPlayerState_Hit::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_HIT;
	m_fAcc = 0.f;

	return S_OK;
}

STATE_TYPE CPlayerState_Hit::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
        CSoundMgr::GetInstance()->PlaySoundW(L"cat_meow.wav", CHANNEL_ID::PLAYER_0, VOLUME_PLAYER_HIT);
        CSoundMgr::GetInstance()->PlaySoundW(L"player_hit.wav", CHANNEL_ID::EFFECT_5, VOLUME_PLAYER_HIT);
        CEventMgr::GetInstance()->Add_Obj(L"PlayerHit", CPlayerHitEffect::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS)));
		m_bEnter = true;
        m_fAcc = 0.f;
	}

	STATE_TYPE eState = Key_Input(fTimeDelta);
    
    m_fAcc += fTimeDelta;
    if (m_fAcc > 0.3)
    {
        m_fAcc = 0.f;
        static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_HIt(false);
        m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

        if(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly())
            eState = STATE_TYPE::FRONT_FLIGHT;
        else
            eState = STATE_TYPE::FRONT_IDLE;
    }

    if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
        eState = STATE_TYPE::FRONT_DIE;


	if (eState != m_eState)
		m_bEnter = false;
	return eState;
}

void CPlayerState_Hit::LateUpdate_State()
{
}

void CPlayerState_Hit::Render_State()
{
  
}

STATE_TYPE CPlayerState_Hit::Key_Input(const _float& fTimeDelta)
{
	if(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Fly())
	{
		if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.back);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.left + vec3.back) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.back);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.right + vec3.back) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.forward);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.left + vec3.forward) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.forward);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.right + vec3.forward) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.left) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.right) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.back) * FLIGHT_SPEED);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
			static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Set_MaxSpeed_By_Df();
			m_pOwner->Get_OwnerObject()->Get_RigidBody()->Add_Impulse((vec3.forward) * FLIGHT_SPEED);
		}
	}
	else
	{
		if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.right);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward + vec3.left);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back + vec3.right);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
			return m_eState;
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back + vec3.left);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
			return m_eState;
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
			return m_eState;
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);

			return m_eState;
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
			return m_eState;
		}
		else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		{
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Scale(_vec3{ -3.f, 3.f, 3.f });
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MoveInfo().fMoveSpeed);
			return m_eState;
		}
	}

  


    return m_eState;
}

CPlayerState_Hit* CPlayerState_Hit::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_Hit* pInstance = new CPlayerState_Hit(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player HitState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_Hit::Free()
{
	__super::Free();
}
