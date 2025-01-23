#pragma once

#include "GameObject.h"
#include "Component.h"
BEGIN(Engine)

class ENGINE_DLL CCollider : public CComponent
{
protected:
	explicit CCollider();
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType);
	explicit CCollider(const CCollider& rhs, CGameObject* _pOwnerObject);
	virtual ~CCollider();

public:
	const _bool 				Is_Collision		() const					{ return (0 < m_iCol) ? TRUE : FALSE; }
	
	const COL_TYPE&				Get_ColliderType	() const					{ return m_eColType; }
	const UINT&					Get_ID				() const					{ return m_iID; }

	void						OnCollision_Enter	(CGameObject* _pColObj);
	void						OnCollision_Stay	(CGameObject* _pColObj);
	void						OnCollision_Exit	(CGameObject* _pColObj);

public:
	HRESULT						Ready_Collider();
	virtual void				Render_Collider() {};

protected:
	_vec3						m_vOffset;
		
	_uint						m_iID;	// 콜라이더 고유 ID
	_int						m_iCol; // 현재 충돌중인 콜라이더 개수

	COL_TYPE					m_eColType;	// 렉트인지, 써클인지, 라인인지, 스피어인지

	_mesh*						m_pMesh;

public:
	static CCollider*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType);
	virtual CComponent*			Clone(CGameObject* _pOwnerObject);


protected:
	virtual void				Free();

private:
	static _uint				g_iNextID;

	friend class CCollisionMgr;

};

END