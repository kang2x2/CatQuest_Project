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

	// 현재상태의 업데이트의 반환 상태타입을 받아 비교하여 상태가 변했는지 판단함
	void			Update_StateMachine(const _float& fTimeDelta);
	void			LateUpdate_StateMachine();
	void			Render_StateMachine();

public:
	// 어떤 객체의 애니메이터를 담을 설정해주는 함수
	void			Set_Animator(CAnimator* pAnimator) { m_pAnimator = pAnimator; }
	CAnimator*		Get_Animator() { return m_PCurAnimator; }

	CAnimator*		Get_RealAnimator() { return m_pAnimator; } // 몬스터 툴 예외처리용
	_bool			Is_AnimationEnd();
public:
	// 상태를 설정 및 변경해주는 함수(애니메이터까지 같이 바꿔줌)
	void			Set_State(STATE_TYPE eState);
	// 상태를 맵컨테이너에다가 추가해주는 함수
	HRESULT			Add_State(STATE_TYPE eState, CState* pState);

	const STATE_TYPE& Get_CurState() { return m_eCurState; }

protected:
	// 상태들을 담을 맵컨테이너 
	map<STATE_TYPE, CState*>		m_StateMap;
	CState*							m_pCurState;
	// 현재가 어떤 상태타입인지 정하는 변수
	STATE_TYPE					    m_eCurState;

	CAnimator*						m_pAnimator;
	CAnimator*						m_PCurAnimator;

public:
	static	CStateMachine* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	// 클론시 어떤 객체가 클론했는지 알려주는 인자가 들어감
	virtual CComponent* Clone(CGameObject* _pOwnerObject);

private:
	virtual void	Free();

};


END