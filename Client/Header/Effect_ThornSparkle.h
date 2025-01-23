#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

struct tagSparkle
{
	CTransform*				m_pSparkleTransCom;
	CTexture*				m_pSparkleTextureCom;
	LERP_FLOAT_INFO			m_tSizeUpLerp;
	LERP_FLOAT_INFO			m_tSizeDownLerp;
};

class CEffect_ThornSparkle : public CEffect
{
	explicit CEffect_ThornSparkle(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);
	explicit CEffect_ThornSparkle(const CEffect_ThornSparkle& rhs);
	virtual ~CEffect_ThornSparkle();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	tagSparkle	 m_sSparkle[3];
	_vec3		 m_vPos;
	_int		 m_iLevel;
public:
	static CEffect_ThornSparkle* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _pPos);

private:
	virtual void				Free() override;
};

