#pragma once
#include "Component.h"
#include "GameObject.h"


BEGIN(Engine)

class CState;
class CAnimator;

class ENGINE_DLL CStateMachine : public CComponent
{
private:
	explicit CStateMachine();
	explicit CStateMachine(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CStateMachine(const CStateMachine& rhs, CGameObject* _pOwnerObject);
	virtual ~CStateMachine();

public:
	

public:
	HRESULT			Ready_StateMachine();

	// ��������� ������Ʈ�� ��ȯ ����Ÿ���� �޾� ���Ͽ� ���°� ���ߴ��� �Ǵ���
	void			Update_StateMachine(const _float& fTimeDelta);
	void			LateUpdate_StateMachine();
	void			Render_StateMachine();

public:
	// � ��ü�� �ִϸ����͸� ���� �������ִ� �Լ�
	void			Set_Animator(CAnimator* pAnimator) { m_pAnimator = pAnimator; }
	CAnimator*		Get_Animator() { return m_PCurAnimator; }

	CAnimator*		Get_RealAnimator() { return m_pAnimator; } // ���� �� ����ó����
	_bool			Is_AnimationEnd();
public:
	// ���¸� ���� �� �������ִ� �Լ�(�ִϸ����ͱ��� ���� �ٲ���)
	void			Set_State(STATE_TYPE eState);
	// ���¸� �������̳ʿ��ٰ� �߰����ִ� �Լ�
	HRESULT			Add_State(STATE_TYPE eState, CState* pState);

	const STATE_TYPE& Get_CurState() { return m_eCurState; }

protected:
	// ���µ��� ���� �������̳� 
	map<STATE_TYPE, CState*>		m_StateMap;
	CState*							m_pCurState;
	// ���簡 � ����Ÿ������ ���ϴ� ����
	STATE_TYPE					    m_eCurState;

	CAnimator*						m_pAnimator;
	CAnimator*						m_PCurAnimator;

public:
	static	CStateMachine* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	// Ŭ�н� � ��ü�� Ŭ���ߴ��� �˷��ִ� ���ڰ� ��
	virtual CComponent* Clone(CGameObject* _pOwnerObject);

private:
	virtual void	Free();

};


END