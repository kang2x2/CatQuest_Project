#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CShadow_Item : public CEffect
{
	explicit CShadow_Item(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CShadow_Item(const CShadow_Item& rhs);
	virtual ~CShadow_Item();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture* m_pTextureCom;

	_float    m_InitY;
	_float    m_fSize;

public:
	static CShadow_Item* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

