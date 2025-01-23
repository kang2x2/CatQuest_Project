#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CEffectLevel_Banner : public CEffect
{
	explicit CEffectLevel_Banner(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffectLevel_Banner(const CEffectLevel_Banner& rhs);
	virtual ~CEffectLevel_Banner();

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
	void						Follow_Emble();

private:
	_matrix						m_matEffect[2];
	_float						m_fBannerSizeX, m_fBannerSizeY;
	_float						m_fEmbleSizeX, m_fEmbleSizeY;


	CTexture*					m_pTex_Banner;
	CTexture*					m_pTex_Emble;
	RECT						m_rcFont;
	wstring						m_strLv;

	_float						m_fBanner_Y;
	_float						m_fEmble_Y;


	_float						m_fAcc;

	LERP_FLOAT_INFO				m_t_fSize_Banner;
	LERP_FLOAT_INFO				m_t_fPosition_Emble;
	LERP_VEC3_INFO				m_t_vSize_Emble;

	_bool						m_bReadyEnd;

public:
	static CEffectLevel_Banner* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};


