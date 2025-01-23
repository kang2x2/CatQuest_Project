#pragma once

#include "Component.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CAgent :	public CComponent
{
public:
private:
	explicit CAgent();
	explicit CAgent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAgent(const CAgent& rhs, CGameObject* _pOwnerObject);
	virtual ~CAgent();

public:
	static CAgent*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

public:
	CGameObject*			Get_Target() const							{ return m_pTarget; }
	HRESULT					Set_Target(CGameObject* const pTarget)		{ m_pTarget = pTarget; return S_OK; }

public:						/* �ش� �Լ��� ����ϴ� ������Ʈ�� Ʈ������ ������Ʈ�� Ÿ���� ����ƽ�̾�� ���� ��Ʈ������ �ߺ� ������ ������ �� �ִ�.*/
	HRESULT					Chase_Target(const _float& fTimeDelta, const _float& fSpeed, const _float& _fMinDis);

public:
	HRESULT					Ready_Agent();
	virtual _int			Update_Component(const _float& fTimeDelta);

	const _matrix*			Compute_LookAtTarget(const _vec3* pTargetPos, const _vec3* pMyPos, const _vec3* pMyUp);

private:
	CGameObject*			m_pTarget;

private:
	virtual void			Free();
};

END
