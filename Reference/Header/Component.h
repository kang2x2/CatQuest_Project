#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent();													// ��� ���ɼ� ����
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType);						// ���� ������ ������ ȣ��
	explicit CComponent(const CComponent& rhs, CGameObject* _pOwnerObject); // ���� ������ ȣ��, �ش� ������Ʈ�� ���� ���� ������Ʈ�� �� �� �ֵ��� �����͸� �޾ƿ´�.
	virtual ~CComponent();

public:
	virtual	_int				Update_Component(const _float& fTimeDelta)	{ return 0; }
	virtual void				LateUpdate_Component(void)					{}

public:
	const COMPONENT_TYPE&		Get_Type() const							{ return m_eType; }
	CGameObject*				Get_OwnerObject() const						{ return m_pOwnerObject; }

	_bool						Is_Active() const							{ return m_bActive; }
	void						Set_Active(const _bool& _bActive)			{ m_bActive = _bActive; }

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	_bool						m_bClone;

	CGameObject*				m_pOwnerObject;
	_bool						m_bActive;

	COMPONENT_TYPE				m_eType;

public:
	virtual CComponent*			Clone(CGameObject* _pOwnerObject)		PURE;
	virtual void				Free(void)	override;
};

END