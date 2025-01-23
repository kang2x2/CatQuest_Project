#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CZeoliteDust : public CEffect
{
	explicit CZeoliteDust(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CZeoliteDust(const CZeoliteDust& rhs);
	virtual ~CZeoliteDust();

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
	_int		m_iTranslucent;
	_int		m_iDeAlpha;
public:
	static CZeoliteDust* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

