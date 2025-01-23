#include "..\..\Header\Animator.h"

CAnimator::CAnimator()
{

}

CAnimator::CAnimator(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::ANIMATOR)
{
}

CAnimator::CAnimator(const CAnimator& rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	m_AnimationMap = rhs.m_AnimationMap;
	m_pCurAnimation = rhs.m_pCurAnimation;
	m_eCurState = rhs.m_eCurState;
}

CAnimator::~CAnimator()
{
}


HRESULT CAnimator::Ready_Animator()
{
	return S_OK;
}

void CAnimator::Update_Animator(const _float& fTimeDelta)
{

	
	m_pCurAnimation->Update_Animation(fTimeDelta);
	

}

void CAnimator::Render_Animator()
{
	
	m_pCurAnimation->Render_Animation();
	
}

HRESULT CAnimator::Add_Animation(STATE_TYPE eState, CAnimation* pAnimation)
{
	if (nullptr == pAnimation)
		return E_FAIL;

	m_AnimationMap.insert({ eState, pAnimation });

	return S_OK;
}

void CAnimator::Set_Animation(STATE_TYPE eState)
{
	auto	iter = find_if(m_AnimationMap.begin(), m_AnimationMap.end(), [&](const pair<STATE_TYPE, CAnimation*>& pair) {
					return eState == pair.first;
		});

	if (iter == m_AnimationMap.end())
		return;

	m_pCurAnimation = iter->second;
	m_eCurState = eState;
	m_pCurAnimation->Reset_Ani(0);
}

CAnimator* CAnimator::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAnimator* pInstance = new CAnimator(pGraphicDev);

	if (FAILED(pInstance->Ready_Animator()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Animator Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CAnimator::Clone(CGameObject* _pOwnerObject)
{
	return new CAnimator(*this, _pOwnerObject);
}

void CAnimator::Free()
{
	for_each(m_AnimationMap.begin(), m_AnimationMap.end(), CDeleteMap());
	m_AnimationMap.clear();

	CComponent::Free();
}
