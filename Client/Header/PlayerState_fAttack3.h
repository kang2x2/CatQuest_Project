#pragma once
#include "stdafx.h"
#include "State.h" 
#include "Player.h"

BEGIN(Engine)

END

class CEffect;

class CPlayerState_fAttack3 : public CState
{
public:
	explicit						CPlayerState_fAttack3(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CPlayerState_fAttack3();

public:
	virtual HRESULT					Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE				Update_State(const _float& fTimeDelta);
	virtual void					LateUpdate_State();
	virtual void					Render_State();

	virtual STATE_TYPE				Key_Input(const _float& fTimeDelta);

	static CPlayerState_fAttack3* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);

private:
	_bool			m_bIsTarget;
	_bool			m_bAttack;

private:
	virtual void	Free();
};
