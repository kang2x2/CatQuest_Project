#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CPlayerHitEffect : public CEffect
{
	explicit CPlayerHitEffect(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CPlayerHitEffect(const CPlayerHitEffect& rhs);
	virtual ~CPlayerHitEffect();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();

private:
	CTransform* m_pTransformCom;
	CTexture*	m_pTextureCom;

	// Cut
	_vec3	  m_vPos;
	_float	  m_fCutSize;
	_float	  m_fCutMaxSize;
	_bool	  m_bSizeUp;
	_float	  m_fRandRotZ;

public:
	static CPlayerHitEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);

private:
	virtual void				Free() override;
};

