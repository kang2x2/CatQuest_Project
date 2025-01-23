#include "DragonState_bAttack.h"
#include "Export_Function.h"

CDragonState_bAttack::CDragonState_bAttack(LPDIRECT3DDEVICE9 pGraphicDev)
	:CState(pGraphicDev)
{
}

CDragonState_bAttack::~CDragonState_bAttack()  
{
}

HRESULT CDragonState_bAttack::Ready_State(CStateMachine* pOwner)
{
	if (nullptr != pOwner)
	{
		m_pOwner = pOwner;
	}

	m_eState = STATE_TYPE::BACK_ATTACK;

	return S_OK;
}

STATE_TYPE CDragonState_bAttack::Update_State(const _float& fTimeDelta)
{
	// юс╫ц
	STATE_TYPE eState = Key_Input(fTimeDelta);



	if (m_pOwner->Is_AnimationEnd())
	{
		return STATE_TYPE::BACK_IDLE;
	}


	return eState;
}

void CDragonState_bAttack::LateUpdate_State()
{
}

void CDragonState_bAttack::Render_State()
{
}

STATE_TYPE CDragonState_bAttack::Key_Input(const _float& fTimeDelta)
{


	return m_eState;
}

CDragonState_bAttack* CDragonState_bAttack::Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner)
{
	CDragonState_bAttack* pInstance = new CDragonState_bAttack(pGraphicDev);

	if (FAILED(pInstance->Ready_State(pOwner)))
	{
		Safe_Release(pInstance);
		MSG_BOX("DragonState bAttackState Create Failed");
		return nullptr;

	}

	return pInstance;
}

void CDragonState_bAttack::Free()
{
	__super::Free();
}
