#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CEffectLevel_Shine : public CEffect
{
	explicit CEffectLevel_Shine(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffectLevel_Shine(const CEffectLevel_Shine& rhs);
	virtual ~CEffectLevel_Shine();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;


private:
	void						Follow_Owner();

private:
	_matrix				m_matEffect[3];


	CTexture*			m_pTex_Glow;
	CTexture*			m_pTex_Shine;
	CTexture*			m_pTex_Shine_02;

	_bool				m_bStartShine;

	// Glow
	_float				m_fGlow_SizeY;
	_float				m_fGlow_PosY;
	LERP_FLOAT_INFO		m_tSize_Y_Glow;
	LERP_FLOAT_INFO		m_tPos_Y_Glow;

	// »þÀÎ
	_float				m_fShineAlpha;
	LERP_FLOAT_INFO		m_tAlpha_Shine;
	LERP_VEC3_INFO		m_tSize_Shine;

	// »þÀÎ02
	_float				m_fShineAlpha2;
	LERP_FLOAT_INFO		m_tAlpha_Shine2;
	LERP_VEC3_INFO		m_tSize_Shine2;

public:
	static CEffectLevel_Shine* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};


