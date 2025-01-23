#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent();													// 사용 가능성 제로
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType);						// 원본 프리팹 생성시 호출
	explicit CComponent(const CComponent& rhs, CGameObject* _pOwnerObject); // 복사 생성시 호출, 해당 컴포넌트를 가진 주인 오브젝트를 알 수 있도록 포인터를 받아온다.
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