#pragma once

/*
	* Scene Change
	
	1. ���� ������ ���� �� ���� -> ���� ���� Ready ȣ�� -> �ε� ������ �� Ŭ�� �߰� ������ ������Ʈ�� �̺�Ʈ �Ŵ����� �߰� ����

	2. ������ ������ �Ű������� �̺�Ʈ �Ŵ����� �� ���� ����

	3. ������ �����ӿ��� �̺�Ʈ ó�� -> �� ������ ���� ���� ó��(���� �� ������Ʈ ������) -> �Ű������� ���� ���� ���� ���� ������ ���� -> �ֵ� ������Ʈ ó��



	* �� �ʵ� �� �ε� ������ ���� ������� ����

		- �ε� �� ����

		- �ش� �ε� ������ ��׶��� �̹����� �׸���, ������Ʈ������ �����带 ���� �����ͷ� ������Ʈ�� Ŭ���Ѵ�.

				- ������ : �� ������ �Ľ� + ���� �� ���� ������Ʈ ����
		
				- ���⼭ Ŭ���� ������Ʈ�� �� ��� �̺�Ʈ�Ŵ����� �߰��Ǵ� ���� �ƴ϶�, ���� �����̳ʿ� �����Ѵ�.

				- ������ ���������� �����ؼ� �ʱ⿡ �־��ִ� ������Ʈ�� �����忡�� ó���Ѵ�.

		- �������� �ε� ����

			- ���� �� ���� -> �̺�Ʈ ����

			- �����̳� ������Ʈ -> ���� ���鼭 �̺�Ʈ ����

			�����忡�� ���� �����ϸ�, �ش� ���� ������ ������ ������ ���� �ȴ�?

		- �� ����



	* ���� 

		- ��Ʈ�� :  �⺻ ��� �ϳ���� �ؽ�ó�� ������Ʈ ���� �ε�
		
		- �κ� : Ű�Է� ������ ���� ��

		- �� ���� Ready���� ������ ������ �ε��Ͽ� �Ľ��Ѵ�.

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
