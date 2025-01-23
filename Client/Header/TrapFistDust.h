#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CTrapFistDust : public CEffect
{
	explicit CTrapFistDust(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos);
	explicit CTrapFistDust(const CTrapFistDust& rhs);
	virtual ~CTrapFistDust();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture*	m_pTextureCom;
	CAnimation* m_pAnimation;
	_vec3		m_vPos;
	_int		m_iTranslucent;
	_int		m_iDeAlpha;
public:
	static CTrapFistDust* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos);

private:
	virtual void				Free() override;
};

