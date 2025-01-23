#pragma once

#include "SkillEffect.h"



class CEffect_Range_Quater :
	public CSkillEffect
{
protected:
	explicit CEffect_Range_Quater(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const EFFECT_RANGE_QUATER_TYPE& _eType);
	explicit CEffect_Range_Quater(const CEffect& rhs);
	virtual ~CEffect_Range_Quater();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one);


public:
	void						Scaling	(const _float& _fTime, const _float _fStartMag,	const _float& _fTargetMag);
	void						Alphaing	(const _float& _fTime, const _float _fStartValue, const _float& _fTargetValue);
	void						Set_Size(const _vec3& vSize) { m_vSize = vSize; }

	LERP_FLOAT_INFO&			Get_AlphaInfo() { return m_eAlphaInfo; }

private:
	void						Render_Circle(_matrix& matWorld);
	void						Render_Arrow(_matrix& matWorld);
	void						Render_Square(_matrix& matWorld);
	void						Render_Rotated_Square(_matrix& matWorld);
	void						Render_CompleteShape(_matrix& matWorld);

private:
	HRESULT						Add_Component();

private:
	EFFECT_RANGE_QUATER_TYPE	m_eType;

	LERP_FLOAT_INFO				m_eAlphaInfo;
	LERP_FLOAT_INFO				m_eScaleInfo;
	_vec3						m_vLerpSize;

public:
	static CEffect_Range_Quater* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const EFFECT_RANGE_QUATER_TYPE& _eType);

protected:
	virtual void				Free() override;
};

