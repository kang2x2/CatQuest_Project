#pragma once

#include "Engine_Define.h"
#include "Base.h"

#include "CameraObject.h"
#include "Camera.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CCameraMgr : public CBase
{
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit CCameraMgr();
	virtual ~CCameraMgr();

public:
	CCameraObject*							Get_Camera		(const _tchar* pCameraTag);
	CCameraObject*							Get_CurCamera	()															{ return m_pCurCamera; }
	HRESULT									Add_Camera		(const _tchar* pCameraTag, CCameraObject* pCameraObject);
	HRESULT									Set_MainCamera	(const _tchar* pCameraTag);
	HRESULT									Change_Camera	(const _tchar* pCameraTag);
	const _bool&							Is_Blending		() const													{ return m_bBlending; }
	const _matrix&							Get_Billboard_X();
	const _matrix&							Get_Billboard_Y();
	const _matrix&							Get_WorldMat();
	const CAMERA_ACTION&					Get_CurCameraAction() const 
	{ 
		return m_eCurAction; 
	}


public:
	HRESULT									Set_ViewSpace	();
	HRESULT									Set_Projection	();
	HRESULT									Set_Viewport	();
	HRESULT									Set_CurCameraAction(const CAMERA_ACTION& _eAction) { m_eCurAction = _eAction; return S_OK; }

	HRESULT									Set_LookAt		(CGameObject* pLookAt);
	HRESULT									Set_Follow		(CGameObject* pFollow);

	void									Shake_Camera(const _float& _fTime = DF_CAMERA_SHAKE_TIME, const _float& _fIntensity = DF_CAMERA_SHAKE_INTENSITY);
	const _bool&							Is_Shake_Camera() const;
	void									Stop_Shake();

	const _bool&							Is_Fix() const { return m_bFix; }
	const _bool&							Is_Fade();
	const _bool&							Is_BackView() const;

	void									Start_Fade(const FADE_MODE& _eMode);
	HRESULT									Start_Action(const CAMERA_ACTION& _eMode, const _vec3& _vStartPos = vec3.one, const _vec3& _vEndPos = vec3.one, const _bool& _bFix = FALSE);

private:
	CCameraObject*							Find_Camera		(const _tchar* pCameraTag);
	void									Blend_Camera	();

private:
	map<const _tchar*, CCameraObject*>		m_mapCamera;
	CCameraObject*							m_pCurCamera; // 현재 카메라
	CCameraObject*							m_pPreCamera; // 이전 카메라

	_bool									m_bBlending;

	CAMERA_ACTION							m_eCurAction;

	_bool									m_bFix;
	_bool									m_bBoss; // 현재 보스 씬인지 아닌지

public:
	virtual void Free();
};

END