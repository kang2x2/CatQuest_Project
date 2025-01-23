#include "PlayerState_fAttack3.h"

#include "Export_Function.h"

#include "PlayerSlash.h"

#include "Effect_ThornAttack.h"

#include "SoundMgr.h"

CPlayerState_fAttack3::CPlayerState_fAttack3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CState(pGraphicDev)
{
}

CPlayerState_fAttack3::~CPlayerState_fAttack3()
{
}

HRESULT CPlayerState_fAttack3::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
		m_pOwner = pOwner;

	m_eState = STATE_TYPE::FRONT_ATTACK3;
	m_bIsTarget = false;
	m_bAttack = false;

	return S_OK;
}

STATE_TYPE CPlayerState_fAttack3::Update_State(const _float& fTimeDelta)
{
	if (!m_bEnter)
	{
		
		CEventMgr::GetInstance()->Add_Obj(L"Player_Slash_Chopping", CPlayerSlash::Create(
			m_pGraphicDev, m_pOwner->Get_OwnerObject(), false));

		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_MonsterThere())
			m_bIsTarget = true;
		else
			m_bIsTarget = false;

		m_pOwner->Get_OwnerObject()->Get_Transform()->Reset_Lerp();
		m_bAttack = false;
		m_bEnter = true;

		CSoundMgr::GetInstance()->PlaySoundW(L"short_growl.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_ATTACK);
	}

	if (!m_bIsTarget)
	{
		m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 8.f);
	}
	else
	{
		if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Boss())
		{
			if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget() != nullptr &&
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetLength() > 8.5f)
			{
				_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS),
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget()->Get_Transform()->Get_Info(INFO::INFO_POS), 0.3f, fTimeDelta, LERP_MODE::EASE_IN);
				if (vOut.y != -99)
				{
					m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(_vec3{ vOut.x, m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS).y, vOut.z });
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
				}
			}
			else
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Reset_Lerp();
				m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
			}
				
		}
		else
		{
			if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget() != nullptr &&
				static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetLength() > 1.5f)
			{
				_vec3 vOut = m_pOwner->Get_OwnerObject()->Get_Transform()->Lerp(m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS),
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTarget()->Get_Transform()->Get_Info(INFO::INFO_POS), 0.3f, fTimeDelta, LERP_MODE::EASE_IN);
				if (vOut.y != -99)
				{
					m_pOwner->Get_OwnerObject()->Get_Transform()->Set_Pos(_vec3{ vOut.x, m_pOwner->Get_OwnerObject()->Get_Transform()->Get_Info(INFO::INFO_POS).y, vOut.z });
					static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_PlayerLook(static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Get_MonTargetDir());
				}
			}
			else
			{
				m_pOwner->Get_OwnerObject()->Get_Transform()->Reset_Lerp();
				m_pOwner->Get_OwnerObject()->Get_Transform()->Translate(fTimeDelta * 6.f);
			}	
		}
	}
		

	if (m_pOwner->Get_Animator()->Get_CurAniamtion()->Get_CurFrame() == 9 && !m_bAttack)
	{
		CEffect* pEffect = CEffect_ThornAttack::Create(m_pGraphicDev, m_pOwner->Get_OwnerObject());
		if(pEffect != nullptr);
			CEventMgr::GetInstance()->Add_Obj(L"Effect_ThornAttack", pEffect);
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_Attack(true);
		CCameraMgr::GetInstance()->Shake_Camera(0.2, 50);
		m_bAttack = true;
		CSoundMgr::GetInstance()->PlaySoundW(L"skill_lightnyan.wav", CHANNEL_ID::PLAYER_1, VOLUME_PLAYER_SKILL);
	}
		

	if (m_pOwner->Is_AnimationEnd())
	{
		m_bEnter = false;
		CCameraMgr::GetInstance()->Start_Action(CAMERA_ACTION::PLAYER_ATK_TO_IDL); // << Test
		return STATE_TYPE::FRONT_IDLE;
	}


	return m_eState;
}

void CPlayerState_fAttack3::LateUpdate_State()
{
	if (static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Is_Hit())
		static_cast<CPlayer*>(m_pOwner->Get_OwnerObject())->Set_HIt(false);
}

void CPlayerState_fAttack3::Render_State()
{
	//cout << "지금은 앞공격3" << endl;
}

STATE_TYPE CPlayerState_fAttack3::Key_Input(const _float& fTimeDelta)
{
	return m_eState;
}

CPlayerState_fAttack3* CPlayerState_fAttack3::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CPlayerState_fAttack3* pInstance = new CPlayerState_fAttack3(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Player fAttack3State Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPlayerState_fAttack3::Free()
{
	__super::Free();
}
