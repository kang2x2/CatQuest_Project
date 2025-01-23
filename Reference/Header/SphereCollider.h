#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CSphereCollider : public CCollider
{
private:
	explicit CSphereCollider();
	explicit CSphereCollider(LPDIRECT3DDEVICE9 CSphereCollider);
	explicit CSphereCollider(const CSphereCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CSphereCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;


public:
	void						Set_Radius(const _float& _fRadius);
	const _float&				Get_Radius() const { return m_fRadius; }

private:
	_float						m_fRadius;


public:
	static CSphereCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual void				Free();
	friend class CCollisionMgr;
};

END