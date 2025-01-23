#pragma once

/*
	* Scene Change
	
	1. 현재 씬에서 다음 씬 생성 -> 다음 씬의 Ready 호출 -> 로딩 데이터 및 클라 추가 데이터 오브젝트들 이벤트 매니저로 추가 예약

	2. 생성한 다음을 매개변수로 이벤트 매니저의 씬 변경 예약

	3. 마지막 프레임에서 이벤트 처리 -> 씬 변경을 가장 먼저 처리(현재 씬 오브젝트 날린다) -> 매개변수로 들어온 다음 씬이 현재 씬으로 세팅 -> 애드 오브젝트 처리



	* 각 필드 씬 로딩 쓰레드 연동 방식으로 변경

		- 로딩 씬 존재

		- 해당 로딩 씬에서 백그라운드 이미지를 그리고, 업데이트에서는 쓰레드를 통해 데이터로 오브젝트를 클론한다.

				- 쓰레드 : 툴 데이터 파싱 + 개별 씬 단위 오브젝트 생성
		
				- 여기서 클론한 오브젝트는 그 즉시 이벤트매니저로 추가되는 것이 아니라, 별도 컨테이너에 보관한다.

				- 씬에서 개별적으로 생성해서 초기에 넣어주는 오브젝트도 쓰레드에서 처리한다.

		- 쓰레드의 로딩 종료

			- 다음 씬 생성 -> 이벤트 예약

			- 컨테이너 오브젝트 -> 루프 돌면서 이벤트 예약

			쓰레드에서 씬을 생성하면, 해당 씬의 로직은 쓰레드 내에서 돌게 된다?

		- 씬 시작



	* 수정 

		- 인트로 :  기본 배경 하나깔고 텍스처와 컴포넌트 전부 로딩
		
		- 로비 : 키입력 받으면 월드 ㄱ

		- 각 씬의 Ready에서 데이터 파일을 로드하여 파싱한다.

*/


#include "GameObject.h"

BEGIN(Engine)

class CScene;

class ENGINE_DLL CEventMgr : public CBase
{
	DECLARE_SINGLETON(CEventMgr)

public:
	explicit CEventMgr();
	virtual ~CEventMgr();

public:
	void					Update_Event();

public:
	HRESULT					Add_Obj(const _tchar* pObjTag, CGameObject* const _pObj);
	HRESULT					Delete_Obj(CGameObject* const _pObj);
	HRESULT					Return_Obj(CGameObject* const _pObj);
	HRESULT					Change_Scene(CScene* const _pScene);

	vector<CGameObject*>&	Get_VecDeleteObj() { return m_vecDeleteObj; }

private:
	HRESULT					Add_Event(const EVENT& _event);
	HRESULT					Execute_Event(const EVENT& _event);


private:
	vector<EVENT>			m_vecEvent;
	vector<CGameObject*>	m_vecDeleteObj;
	vector<CGameObject*>	m_vecReturnObj;

private:
	virtual void			Free();
};

END
