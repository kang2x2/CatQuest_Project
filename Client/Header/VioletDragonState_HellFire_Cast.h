#pragma once
#include "State.h"


class CVioletDragonState_HellFire_Cast : public CState
{

public:
	explicit			CVioletDragonState_HellFire_Cast(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_HellFire_Cast();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_HellFire_Cast* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);




private: 

	_float m_fAccTime;
	_bool m_bThunder;





private:
	virtual void Free();



};

