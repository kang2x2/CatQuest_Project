#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CBoxCollider : public CCollider
{
private:
	explicit CBoxCollider();
	explicit CBoxCollider(LPDIRECT3DDEVICE9 CBoxCollider);
	explicit CBoxCollider(const CCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CBoxCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

private:
	_vec3						m_vSize;

public:
	static CBoxCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual void				Free();

	friend class CCollisionMgr;

};

END