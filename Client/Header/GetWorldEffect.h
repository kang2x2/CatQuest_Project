#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CGetWorldEffect : public CEffect
{
	explicit CGetWorldEffect(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);
	explicit CGetWorldEffect(const CGetWorldEffect& rhs);
	virtual ~CGetWorldEffect();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture*		 m_pOraTexCom;
	CTransform*		 m_pOraTransCom;
	LERP_FLOAT_INFO  m_tSizeUpLerp;
	LERP_FLOAT_INFO  m_tAlphaDownLerp;
	_vec3			 m_vPos;
	_float			 m_fTranslucent;
public:
	static CGetWorldEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);

private:
	virtual void				Free() override;
};

