#pragma once

#include "GameObject.h"
#include "Camera.h"

BEGIN(Engine)

class ENGINE_DLL CCameraObject : public CGameObject
{
protected:
	explicit CCameraObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCameraObject(const CCameraObject& rhs);
	virtual ~CCameraObject();

public:
	virtual HRESULT						Ready_Object(void);

	virtual void						Start_Fade(const FADE_MODE& _eMode) {};
	virtual const _bool&				Is_Fade() { return FALSE; }

	virtual void						Set_BackView(const _bool& _bBackView) {};
	virtual void						Set_FlightView(const _bool& _bFlightView) {};
	virtual _bool						Is_BackView()  { return TRUE; } 

public:
	CCamera*							Get_CameraCom() const { return m_pCameraCom; }

protected:
	CCamera*							m_pCameraCom;
	
public:
	virtual void						Free();
};

END