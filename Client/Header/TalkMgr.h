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

	
	_bool						  m_bInit = false; // ���� �ʱ�ȭ

	_int					      m_iStayTime; // ī�޶� ���߰� ��� �ð�.
	_bool						  m_bTargetCam; // ī�޶� Ÿ�ٿ��� �̵�
	_bool						  m_bReturnCam; // ī�޶� �ٽÿ���
	_bool						  m_bStaySet;  // ī�޶� ��� �ð� �� ���� ����

	_bool						  m_bTalkEnd; // ������ ���â ���� ȿ���� ����
private:
	virtual void			Free();
};

END

