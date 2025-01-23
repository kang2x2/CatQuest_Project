#pragma once
#include "stdafx.h"
#include "State.h" 
#include "Player.h"

BEGIN(Engine)

END

class CPlayerState_bAttack2 : public CState
{
public:
	explicit						CPlayerState_bAttack2(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CPlayerState_bAttack2();

public:
	virtual HRESULT					Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE				Update_State(const _float& fTimeDelta);
	virtual void					LateUpdate_State();
	virtual void					Render_State();

	virtual STATE_TYPE				Key_Input(const _float& fTimeDelta);

	static CPlayerState_bAttack2* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);

private:
	_bool			m_bAttackContinue;
	_bool			m_bIsTarget;

private:
	virtual void	Free();
};

