#pragma once
#include "State.h"
class CVioletDragonState_CreateWyvern_Cast : public CState
{
public:
	explicit			CVioletDragonState_CreateWyvern_Cast(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_CreateWyvern_Cast();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// 사용 안함
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);

public:
	static CVioletDragonState_CreateWyvern_Cast* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);


private:


	_float  m_fAccTime;

	// Very Near
	_bool   m_bCreateWyvern1;
	_bool   m_bCreateWyvern2;

	// Near 
	_bool	m_bCreateWyvern3;
	_bool	m_bCreateWyvern4;
	_bool	m_bCreateWyvern5;
	_bool	m_bCreateWyvern6;


	// Boss Near
	_bool	m_bCreateWyvern7;
	_bool	m_bCreateWyvern8;
	_bool	m_bCreateWyvern9;
	_bool	m_bCreateWyvern10;



	// Create region
	_vec3 vCreatePosition;
	_vec3 vCreateBossPosition;

	_bool m_bInit;

private:

	virtual void Free();




};

