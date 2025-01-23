#pragma once

#include "Component.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CTransform :	public CComponent
{
private:
	explicit CTransform();
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs, CGameObject* _pOwnerObject);
	virtual ~CTransform();

public:
	const _vec3&			Get_Info		(const INFO& _eInfo) const	{ return m_vInfo[_eInfo]; }
	const _matrix&			Get_WorldMat	() const					{ return m_matWorld; }
	const _vec3&			Get_Scale		() const					{ return m_vScale; }
	const _vec3&			Get_Dir			() const					{ return m_vDir; }

public:
	void					Rotate			(const DIRID& _eDir , const _float& fSpeed	, const SPACEID _eSpace = LOCAL);

	void					Translate		(const DIRID& _eDir	, const _float& fSpeed	, const SPACEID _eSpace = LOCAL); 
	void					Translate		(const _vec3& _vDir	, const _float& fSpeed);
	void					Translate		(const _float& fSpeed);

	void					Set_Pos			(const _vec3& _vPos);								
	void					Set_Rot			(const _vec3& _vRot, const SPACEID _eSpace = LOCAL);
	void					Set_Scale		(const _vec3& _vPos);
	void					Set_Dir			(const _vec3& _vDir)		{ m_vDir = _vDir; }
	void					Set_PosY		(const _float& _fHeight);

	void					Reverse			();


	_vec3&					Lerp			(const _vec3& vStart, const _vec3& vTarget, const _float& fLerpTime, const _float& fTimeDelta, const LERP_MODE& _eMode = LERP_MODE::DEFAULT);
	_vec3&					Normal_Lerp		(const _vec3& vStart, const _vec3& vTarget, const _float& fLerpTime, const _float& fTimeDelta);
	void					Reset_Lerp		();

public:
	HRESULT					Ready_Transform	();
	virtual _int			Update_Component(const _float& fTimeDelta);

private:
	void					Cal_WorldMat	(); 

private:
	_vec3					m_vInfo[INFO_END];	// 외부에서 현재 트랜스폼 정보를 알고 싶을 때 (로컬 뱡향벡터, 월드 포지션)
	_matrix					m_matWorld;			// 실질 월드 매트릭스
	_quat					m_quatQ;		
	_vec3					m_vScale;		
	_vec3					m_vAngle;	

	_vec3					m_vDir;

	_vec3					m_vStart;
	_bool					m_bStart;
	_float					m_fCurTime;
	LERP_MODE				m_eLerpMod;


public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual void			Free();

	friend class CCollisionMgr;

	friend class CRectCollider;
	friend class CCircleCollider;
	friend class CLineCollider;
	friend class CCollider;

};

END