#pragma once

#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CLineCollider : public CCollider
{
private:
	explicit CLineCollider();
	explicit CLineCollider(LPDIRECT3DDEVICE9 CLineCollider);
	explicit CLineCollider(const CLineCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CLineCollider();

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() override;

public:
	void						Set_PointList(const _vec3& _v1, const _vec3& _v2) { m_vPointList[0] = _v1; m_vPointList[1] = _v2; }
	void						Set_OverLap_Line(const _vec3& _vOverlap) { memcpy(&m_vOverlapLine, &_vOverlap, sizeof(_vec3)); }
	const _vec3&				Get_Overlap_Line() const { return m_vOverlapLine; }
private:
	_vec3						m_vPointList[2];
	_vec3						m_vOverlapLine;


public:
	static CLineCollider*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);


private:
	virtual void				Free();

	friend class CCollisionMgr;
	friend class CLineObject;

};

END