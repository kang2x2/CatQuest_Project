#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud2_Shadow : public CEffect
{
	explicit CCloud2_Shadow(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCloud2_Shadow(const CCloud2_Shadow& rhs);
	virtual ~CCloud2_Shadow();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

	const _float				Get_Distance_From_Camera();
private:
	CTexture* m_pTextureCom;
	_uint	  m_iAlpha;

public:
	static CCloud2_Shadow* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

