#pragma once
#include "State.h"
#include "stdafx.h"
#include "Monster.h"

BEGIN(Engine)
END


class CVioletDragonState_Intro_Sword :public CState
{
public:
	explicit			CVioletDragonState_Intro_Sword(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_Intro_Sword();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_Intro_Sword* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:
	virtual void Free();

private:

	_float m_fAccTime;

};

