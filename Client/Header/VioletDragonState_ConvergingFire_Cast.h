#pragma once
#include "State.h"



class CVioletDragonState_ConvergingFire_Cast : public CState   //  Dagger Use
{
public:
	explicit			CVioletDragonState_ConvergingFire_Cast(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_ConvergingFire_Cast();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_ConvergingFire_Cast* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:

	_float  m_fAccTime;

	_bool   m_bBullet1;
	_bool   m_bBullet2;
	_bool   m_bBullet3;
	_bool   m_bBullet4;

	_bool   m_bBullet5;
	_bool   m_bBullet6;
	_bool   m_bBullet7;
	_bool   m_bBullet8;

	_bool   m_bBullet9;
	_bool   m_bBullet10;
	_bool   m_bBullet11;
	_bool   m_bBullet12;

	_bool   m_bBullet13;
	_bool   m_bBullet14; 
	_bool   m_bBullet15;
	_bool   m_bBullet16;


private:
	virtual void Free();




};

