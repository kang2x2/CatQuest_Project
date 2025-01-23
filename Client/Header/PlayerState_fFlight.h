#pragma once
#include "stdafx.h"
#include "State.h" 
#include "Player.h"

BEGIN(Engine)

END

class CPlayerState_fFlight : public CState
{
public:
	explicit						CPlayerState_fFlight(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CPlayerState_fFlight();

public:
	virtual HRESULT					Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE				Update_State(const _float& fTimeDelta);
	virtual void					LateUpdate_State();
	virtual void					Render_State();

	virtual STATE_TYPE				Key_Input(const _float& fTimeDelta);

	static CPlayerState_fFlight* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);

private:

private:
	_bool			m_bIsSky;
	_bool			m_bIsLand;

	_float			m_fOriginPosY;

	_float			m_fAccTime;

	_float			m_fHeight_High;
	_float			m_fHeight_Low;

	LERP_FLOAT_INFO	m_tHeight;

private:
	virtual void	Free();
};

