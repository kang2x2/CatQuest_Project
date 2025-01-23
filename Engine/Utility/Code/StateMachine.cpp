#include "..\..\Header\StateMachine.h"
#include "..\..\Header\State.h"
#include "..\..\Header\Animator.h"

#include "Management.h"

CStateMachine::CStateMachine()
{

}

CStateMachine::CStateMachine(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::STATEMACHINE), m_pCurState(nullptr), m_pAnimator(nullptr), m_eCurState(STATE_TYPE::TYPEEND)
{
}

CStateMachine::CStateMachine(const CStateMachine& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	m_StateMap = rhs.m_StateMap;
	m_pCurState = rhs.m_pCurState;
	m_pAnimator = rhs.m_pAnimator;
}	

CStateMachine::~CStateMachine()
{
}


HRESULT CStateMachine::Ready_StateMachine()
{
	return S_OK;
}

void CStateMachine::Update_StateMachine(const _float& fTimeDelta)
{
	if (nullptr != m_pAnimator)
	{
		m_PCurAnimator = m_pAnimator;
		m_pAnimator = nullptr;
		m_PCurAnimator->Set_Animation(m_eCurState);
	}

	STATE_TYPE eState = m_pCurState->Update_State(fTimeDelta);
	
	if(nullptr != m_PCurAnimator)
		m_PCurAnimator->Update_Animator(fTimeDelta);

	// 현재 상태와 다른상태가 반환되면 반환된 상태로 변경
	if (eState != m_eCurState)
	{
		Set_State(eState);
		m_PCurAnimator->Set_Animation(eState);
	}
}

void CStateMachine::LateUpdate_StateMachine()
{
	m_pCurState->LateUpdate_State();
}

void CStateMachine::Render_StateMachine()
{
	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())  // 수정시 팀장 보고
	{
		m_pAnimator->Render_Animator();
		return;
	}
	m_pCurState->Render_State();
	
	if (nullptr != m_PCurAnimator)
	m_PCurAnimator->Render_Animator();
}

_bool CStateMachine::Is_AnimationEnd()
{
	if (m_PCurAnimator->Get_CurAniamtion()->Is_End())
		return true;

	else
		return false;
}

void CStateMachine::Set_State(STATE_TYPE eState)
{
	auto	iter = find_if(m_StateMap.begin(), m_StateMap.end(), [&](const pair<STATE_TYPE, CState*>& pair) {
		return eState == pair.first;
		});

	if (iter == m_StateMap.end())
		return;

	m_pCurState = iter->second;
	m_eCurState = eState;

	/*if (m_PCurAnimator != nullptr)
		m_PCurAnimator->Set_Animation(eState);*/
}

HRESULT CStateMachine::Add_State(STATE_TYPE eState, CState* pState)
{
	if (nullptr == pState)
		return E_FAIL;

	m_StateMap.insert({ eState, pState });

	return S_OK;
}

CStateMachine* CStateMachine::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStateMachine* pInstance = new CStateMachine(pGraphicDev);

	if (FAILED(pInstance->Ready_StateMachine()))
	{
		Safe_Release(pInstance);
		MSG_BOX("StateMachine Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CStateMachine::Clone(CGameObject* _pOwnerObject)
{
	return new CStateMachine(*this, _pOwnerObject);
}

void CStateMachine::Free()
{
	for_each(m_StateMap.begin(), m_StateMap.end(), CDeleteMap());
	m_StateMap.clear();

	CComponent::Free();
}
