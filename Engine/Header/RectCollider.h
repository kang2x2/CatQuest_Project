#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CRectCollider : public CCollider
{
private:
	explicit CRectCollider();
	explicit CRectCollider(LPDIRECT3DDEVICE9 CRectCollider);
	explicit CRectCollider(const CRectCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CRectCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

public:
	void						Set_OverLap_Rect(const _vec3& _vOverlap) { memcpy(&m_vOverlapRect, &_vOverlap, sizeof(_vec3)); }
	const _vec3&				Get_Overlap_Rect() const { return m_vOverlapRect; }

	void						Set_Size(const _vec3& _vSize);
	const _vec3&				Get_Size() const { return m_vSize; }

private:
	_vec3						m_vSize;
	_vec3						m_vOverlapRect;

public:
	static CRectCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual void				Free();

	friend class CCollisionMgr;

};

END