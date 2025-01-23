#pragma once
#include "State.h"


class CVioletDragonState_BloodyThunder : public CState
{

public:
	explicit			CVioletDragonState_BloodyThunder(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual				~CVioletDragonState_BloodyThunder();


public:
	virtual HRESULT		Ready_State(CStateMachine* pOwner);
	virtual STATE_TYPE  Update_State(const _float& fTimeDelta);
	virtual void		LateUpdate_State();
	virtual void		Render_State();


	// ��� ����
	virtual STATE_TYPE		Key_Input(const _float& fTimeDelta);



public:
	static CVioletDragonState_BloodyThunder* Create(LPDIRECT3DDEVICE9 pGraphicDev, CStateMachine* pOwner);




private: 

	_float m_fAccTime;
	_bool m_bThunder;





private:
	virtual void Free();



};

