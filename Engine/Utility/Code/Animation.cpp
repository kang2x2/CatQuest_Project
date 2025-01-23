#include "Animation.h"
#include "Texture.h"

CAnimation::CAnimation(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
{
	m_pGraphicDev->AddRef();
}


CAnimation::~CAnimation()
{
}

HRESULT CAnimation::Ready_Animation(CTexture* pTexture, STATE_TYPE eState, _float fDelay, _bool bIsLoop)
{
	if (pTexture == nullptr)
		return E_FAIL;

	m_pTexture = pTexture;

	m_fAcc = 0.f;
	m_fFrame = 0;
	m_fMaxFrame = pTexture->Get_TexCnt();

	m_eState = eState;

	m_fDelay = fDelay;

	m_bIsLoop = bIsLoop;

	return S_OK;
}

void CAnimation::Update_Animation(const _float& fTimeDelta)
{
	m_fAcc += fTimeDelta;

	if (m_fDelay < m_fAcc)
	{
		m_fAcc = m_fAcc - m_fDelay;

		++m_fFrame;

		if (m_bIsLoop && (m_fMaxFrame == m_fFrame))
			m_fFrame = 0;
		else if (!m_bIsLoop && (m_fMaxFrame == m_fFrame))
			m_fFrame = m_fMaxFrame - 1;
	}
}

void CAnimation::Render_Animation()
{
	m_pTexture->Render_Texture(m_fFrame);
}

_bool CAnimation::Is_End()
{
	if (m_fFrame == m_fMaxFrame - 1)
		return true;
	else
		return false;
}

CAnimation* CAnimation::Create(LPDIRECT3DDEVICE9 pGraphicDev, CTexture* pTexture, STATE_TYPE eState, _float fDelay, _bool bIsLoop)
{
	CAnimation* pInstance = new CAnimation(pGraphicDev);

	if (FAILED(pInstance->Ready_Animation(pTexture, eState, fDelay, bIsLoop)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Animation Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CAnimation::Free()
{
	Safe_Release(m_pGraphicDev);
}
