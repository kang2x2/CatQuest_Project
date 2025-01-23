#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CTexture;

class ENGINE_DLL CAnimation :
	public CBase
{
public:
	explicit CAnimation(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CAnimation();

public:
	virtual HRESULT			Ready_Animation(CTexture* pTexture, STATE_TYPE eState, _float fDelay, _bool bIsLoop);
	virtual void			Update_Animation(const _float& fTimeDelta);
	virtual void			Render_Animation();

	virtual void			Reset_Ani(_uint iFrame) { m_fFrame = iFrame, m_fAcc = 0.f; }

	virtual _uint&			Get_CurFrame() { return m_fFrame; }

	virtual _bool			Is_End();
protected:
	CTexture*				m_pTexture = nullptr;

	_uint					m_fFrame;
	_uint					m_fMaxFrame;

	_float					m_fAcc;
	_float					m_fDelay;

	_bool					m_bIsLoop;

	STATE_TYPE				m_eState = STATE_TYPE::TYPEEND;

	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static	CAnimation* Create(LPDIRECT3DDEVICE9 pGraphicDev, CTexture* pTexture, STATE_TYPE eState, _float fDelay, _bool bIsLoop);

public:
	virtual void	Free();
};

END

