#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CCircleCollider : public CCollider
{
private:
	explicit CCircleCollider();
	explicit CCircleCollider(LPDIRECT3DDEVICE9 CCircleCollider);
	explicit CCircleCollider(const CCircleCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CCircleCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

private:
	_float						m_fRadius;

public:
	static CCircleCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual void				Free();

	friend class CCollisionMgr;

};

END