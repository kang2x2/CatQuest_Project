#pragma once
#include "GameObject.h"
#include "Player_Camera.h"

BEGIN(Engine)

class CTalkMgr : public CBase
{
	DECLARE_SINGLETON(CTalkMgr)
private:
	explicit CTalkMgr();
	virtual ~CTalkMgr();

public:
	void	Init();

public:
	_bool	Get_Talk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID);
	_bool	Get_CamTalk(LPDIRECT3DDEVICE9 pGraphicDev, _int _iTalkID, OBJ_ID _eObjID, _int _EventIndex, _vec3 _StartPos, _vec3 _TargetPos);
	_bool	Get_IsInit() { return m_bInit; }

private:
	CPlayer_Camera*				  m_pCam;

	map<int, vector<wstring>>	  m_mapTalkData; 
	_int						  m_iTalkIndex; 

	
	_bool						  m_bInit = false; // 최초 초기화

	_int					      m_iStayTime; // 카메라가 멈추고 대기 시간.
	_bool						  m_bTargetCam; // 카메라 타겟에게 이동
	_bool						  m_bReturnCam; // 카메라 다시원점
	_bool						  m_bStaySet;  // 카메라 대기 시간 한 번만 세팅

	_bool						  m_bTalkEnd; // 마지막 대사창 러프 효과를 위해
private:
	virtual void			Free();
};

END

