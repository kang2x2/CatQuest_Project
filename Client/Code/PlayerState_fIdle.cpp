#include "PlayerState_fIdle.h"

#include "Export_Function.h"
#include "MoveDust.h"
#include "MoveWater.h"

CPlayerState_fIdle::CPlayerState_fIdle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_fIdle::~CPlayerState_fIdle()
{
}

HRESULT CPlayerState_fIdle::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_IDLE;

	return S_OK;
}

STATE_TYPE CPlayerState_fIdle::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		if (!CCameraMgr::GetInstance()->Get_CurCamera()->Is_BackView() && 
			!static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_RigidBody()->Is_KnockUp()) 
		{
			_vec3 vPpos = m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO_POS);
			m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(_vec3{ vPpos.x,  m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Scale().y, vPpos.z });

			CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Hp")->Set_Active(true);
			CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Def")->Set_Active(true);
			CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Mana")->Set_Active(true);
		}
		m_bEnter = true;
	}

	if (!static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_PlayerTalking())
	{
		STATE_TYPE eState = Key_Input(fTimeDelta);

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
		{
			m_bEnter = false;
			return STATE_TYPE::FRONT_HIT;
		}

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_StatInfo().bDead)
			return STATE_TYPE::FRONT_DIE;

		if (eState != m_eState)
			m_bEnter = false;
		return eState;
	}
	else
		return m_eState;
	
}

void CPlayerState_fIdle::LateUpdate_State()
{
}

void CPlayerState_fIdle::Render_State()
{
	//cout << "지금은 앞서있기" << endl;
}

STATE_TYPE CPlayerState_fIdle::Key_Input(const _float& fTimeDelta)
{
	// 날자꾸나	
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_F) &&
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Has_Flight())
		return STATE_TYPE::FRONT_FLIGHT;

	// 구르기
#pragma region 구르기구르기
	if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left + vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::BACK_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right + vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::BACK_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.left);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.right);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.back);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Dir(vec3.forward);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::BACK_ROLL;
	}
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIK_SPACE))
	{
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir());
		return STATE_TYPE::FRONT_ROLL;
	}
#pragma endregion

	
	// 공격
	if (CInputDev::GetInstance()->Key_Down(VK_LBUTTON))
	{
		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
		{
			if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir().z > 0.5)
				return STATE_TYPE::BACK_ATTACK;
			else
				return STATE_TYPE::FRONT_ATTACK;

		}
		else
			return STATE_TYPE::FRONT_ATTACK;
	}

	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		return STATE_TYPE::FRONT_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		return STATE_TYPE::BACK_WALK;
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		return STATE_TYPE::FRONT_WALK;

	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_LockOn())
	{
		if (m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Dir().z > 0)
			return STATE_TYPE::BACK_IDLE;
	}
	else
	{
		return m_eState;
	}
		
}

CPlayerState_fIdle* CPlayerState_fIdle::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fIdle* pInstance = new CPlayerState_fIdle(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fIdleState Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fIdle::Free()
{
	__super::Free();
}
