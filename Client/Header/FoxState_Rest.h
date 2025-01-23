#pragma once
#include "stdafx.h"
#include "State.h"
#include "Monster.h"

BEGIN(Engine)

END

class CFoxState_Rest : public CState
{
public:
	explicit			CFoxState_Rest(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CFoxState_Rest();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CFoxState_Rest* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();

private:

	_float m_fAccTime;
	_float m_fAttackTime;

	_float  m_fPatrolRange;
	_float  m_fChaseRange;
	_float  m_fAttackRange;
	_float  m_fComeBackRange;
	_float  m_fPlayerTargetRange;

	_float  m_fPosShakeRange;
	_vec3   m_vOriginPos;
	
	_float  m_fAddHeight;
	_float  m_fAddRot;
	_float  m_fScaleDown;


	_bool  m_bAssault;

};

