#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CEffect_Font : public CEffect
{
	explicit CEffect_Font(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont);
	explicit CEffect_Font(const CEffect_Font& rhs);
	virtual ~CEffect_Font();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	void						Caculate();

private:

	FONT_TYPE					m_eFontType;
	RECT						m_rcFont;
	RECT						m_rcFont2;
	RECT						m_rcFontxp;
	_float						m_fRectRad;

	wstring						m_strFont;
	_uint						m_iNumb;
	
	_vec3						m_vFontPos;
	_vec3						m_vColor;
	_float						m_fAlpha;
	

	LERP_FLOAT_INFO				m_tAlpha;
	LERP_FLOAT_INFO				m_tPosY;

public:
	static CEffect_Font* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pOwner, _uint iNumb, FONT_TYPE eFont);

private:
	virtual void				Free() override;
};
