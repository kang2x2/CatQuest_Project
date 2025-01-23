#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CStateMachine;

class ENGINE_DLL CState :
	public CBase
{
public:
	explicit CState(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CState();

public:
	virtual HRESULT			Ready_State(CStateMachine* pOwner) PURE;
	// ����Ÿ���� ��ȯ
	virtual STATE_TYPE		Update_State(const _float& fTimeDelta) PURE;
	virtual void			LateUpdate_State() PURE;
	virtual void			Render_State() PURE;

	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta) PURE;

	virtual	STATE_TYPE		Get_State() { return m_eState; }

protected:
	// � ���¸ӽ��� �ڽ��� ���ϰ� �ִ��� �˷��ִ� ����
	CStateMachine*			m_pOwner;
	// � �������� �����ִ� ����
	STATE_TYPE				m_eState;

	LPDIRECT3DDEVICE9		m_pGraphicDev;

	_bool					m_bEnter;

	// State�� ��ӹ޴� ����Ŭ������ ���鶧 �̰� �־��ָ� ��
	/*static C(�������Ŭ����)* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);
	{
		C(�������Ŭ����)* pInstance = new CC(�������Ŭ����)(pGraphicDev);

		if (FAILED(pInstance->Ready_State(pOwner)))
		{
			Safe_Release(pInstance);
			MSG_BOX("(�������Ŭ����) Create Failed");
			return nullptr;
		}

		return pInstance;
	}*/

public:
	virtual void	Free();
};

END

