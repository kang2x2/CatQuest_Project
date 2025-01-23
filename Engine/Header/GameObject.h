#pragma once

#include "Component.h"


BEGIN(Engine)

class CTransform;
class CCollider;
class CVIBuffer;
class CAnimator;
class CRigidBody;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_TYPE& _eType, const OBJ_ID& _eID);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	virtual CGameObject* Clone() { return nullptr; }

#pragma region Access Methods

public:
	CComponent*							Get_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);
	CTransform*							Get_Transform() const { return m_pTransformCom; }
	CCollider*							Get_Collider() const { return m_pColliderCom; }
	CAnimator*							Get_Animator() const { return m_pAnimatorCom; }
	CVIBuffer*							Get_VIBuffer() const { return m_pBufferCom; }
	CRigidBody*							Get_RigidBody() const { return m_pRigidBodyCom; }

	const _tchar*						Get_Name() const { return m_szName; } // ���� ��� �ް� ���!

	CGameObject*						Get_Parent() const { return m_pParentObj; }
	CGameObject*						Get_Child(const _uint& _iIndex = 0);

	const _float&						Get_ViewZ();  // ���� ��� ������Ʈ���� ���ļ���
	void								Set_ViewZ();  // ���� ��� ������Ʈ���� ���ļ���
	const OBJ_TYPE						Get_Type() const { return m_eType; }
	const OBJ_ID						Get_ID() const { return m_eID; } // ���� ��� �ް� ���!

	void								Set_Parent(CGameObject* const _pParent) { m_pParentObj = _pParent; }
	void								Set_Name(const _tchar* _szName) { m_szName = _szName; } // ���� ��� �ް� ���!
	void								Set_Active(const _bool& _bActive) { m_bActive = _bActive; }
	void								Set_ID(const OBJ_ID& _eID) { m_eID = _eID; } // ���� ��� �ް� ���!
	void								Set_Maintain(const _bool& _bMaintain) { m_bMaintain = _bMaintain; }

	const _bool&						Is_Active() const { return m_bActive; }
	const _bool							Is_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);

	const _bool&						Is_Maintain() const { return m_bMaintain; }

	
	UI_LAYER							Get_LayerLv() { return m_eUILayer; }

	// ��ȣ�ۿ� �� �浹 �� �̺�Ʈ ����
	ENTER_TYPE							Get_EnterType() { return m_eEnter; }
	INTERACTION_TYPE					Get_InterType() { return m_eInterType; }

	void								Set_IsEnter(_bool _switch) { m_bEnter = _switch; }
	void								Set_EventSwitch(_bool _switch) { m_bEventSwitch = _switch; }
#pragma endregion

#pragma region Collision Methods

public:
	virtual void						OnCollision_Enter(CGameObject* _pColObj) {};
	virtual void						OnCollision_Stay(CGameObject* _pColObj) {};
	virtual void						OnCollision_Exit(CGameObject* _pColObj) {};

#pragma endregion

public:
	virtual HRESULT						Ready_Object();
	virtual _int						Update_Object(const _float& fTimeDelta);
	virtual void						LateUpdate_Object();
	virtual void						Render_Object();

private:
	CComponent*							Find_Component(const COMPONENT_TYPE& _eType, COMPONENTID eID);

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;

	const _tchar*						m_szName;
	multimap<COMPONENT_TYPE, CComponent*>	m_mapComponent[ID_END];

	CTransform*							m_pTransformCom;	
	CCollider*							m_pColliderCom;
	CVIBuffer*							m_pBufferCom;
	CAnimator*							m_pAnimatorCom;
	CRigidBody*							m_pRigidBodyCom;

	CGameObject*						m_pParentObj;
	vector<CGameObject*>				m_vecChilds;
	
	OBJ_TYPE							m_eType;
	OBJ_ID								m_eID; // ���� ��� �ް� ���!
	_bool								m_bActive;

	_float                              m_fViewZ; // ���� ��� ������Ʈ���� ���ļ���

	_bool								m_bMaintain; // Ư�� �� ����� �������� �ʴ´�.

	// UI_Layer
	UI_LAYER							m_eUILayer;

	// ��ȣ�ۿ� �� �浹 �� �̺�Ʈ ����
	ENTER_TYPE							m_eEnter;
	INTERACTION_TYPE					m_eInterType;
	_bool								m_bEventSwitch;
	_bool								m_bEnter;

public:
	virtual void						Free();
};


END