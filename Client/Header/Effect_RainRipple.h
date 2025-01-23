#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CEffect_RainRipple : public CEffect
{
	explicit CEffect_RainRipple(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos);
	explicit CEffect_RainRipple(const CEffect_RainRipple& rhs);
	virtual ~CEffect_RainRipple();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture*		m_pTextureCom;
	random_device	m_Random;

	_float			m_fSpeed;
	_vec3			m_InitPos;

	_float			m_fDirZ;

	_vec3			m_vWindVelo;
	_float			m_fdriftAngle;

	_float			m_fAccTime;

	_uint			m_iTexChoice;
	_uint			m_iAlpha;

	LERP_FLOAT_INFO m_tAlpha;

public:
	static CEffect_RainRipple* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos);

private:
	virtual void				Free() override;
};
