#include "..\..\Header\EventMgr.h"

#include "Management.h"
#include "Scene.h"

IMPLEMENT_SINGLETON(CEventMgr)

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{
	Free();
}

void CEventMgr::Update_Event()
{
	// 이전 프레임에 삭제될 예정이었던 오브젝트들을 삭제한다.
	for (size_t i = 0; i < m_vecDeleteObj.size(); ++i)
	{
		if (nullptr != m_vecDeleteObj[i])
		{
			CManagement::GetInstance()->Get_CurScene()->Get_Layer(m_vecDeleteObj[i]->Get_Type())->Delete_GameObject(m_vecDeleteObj[i]);
		}
	}
	m_vecDeleteObj.clear();

	// 이전 프레임에 풀에 반환될 예정이었던 오브젝트들을 반환한다.
	for (size_t i = 0; i < m_vecReturnObj.size(); ++i)
	{
		if (nullptr != m_vecReturnObj[i])
		{
			CManagement::GetInstance()->Get_CurScene()->Get_Layer(m_vecReturnObj[i]->Get_Type())->Return_GameObject(m_vecReturnObj[i]);
		}
	}
	m_vecReturnObj.clear();

	// 이전 프레임에 등록된 이벤트를 처리한다(오브젝트 추가, 씬 변경)
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
		Execute_Event(m_vecEvent[i]);
	m_vecEvent.clear();
}

HRESULT CEventMgr::Add_Obj(const _tchar* pObjTag, CGameObject* const _pObj)
{
	NULL_CHECK_RETURN(_pObj, E_FAIL);

	EVENT event;
	ZeroMemory(&event, sizeof(EVENT));

	event.lParam = (DWORD_PTR)_pObj;
	event.wParam = pObjTag;
	event.eType = EVENT_TYPE::ADD_OBJ;

	for (auto& iter : m_vecEvent) 
	{
		if (iter.lParam == event.lParam && iter.eType == event.eType)
			return E_FAIL;
	}
	FAILED_CHECK_RETURN(Add_Event(event), E_FAIL);

	return S_OK;
}

HRESULT CEventMgr::Delete_Obj(CGameObject* const _pObj)
{
	NULL_CHECK_RETURN(_pObj, E_FAIL);

	EVENT event;
	ZeroMemory(&event, sizeof(EVENT));

	event.lParam = (DWORD_PTR)_pObj;
	event.eType = EVENT_TYPE::DELETE_OBJ;

	for (auto& iter : m_vecEvent) 
	{
		if (iter.lParam == event.lParam && iter.eType == event.eType)
			return E_FAIL;
	}

	FAILED_CHECK_RETURN(Add_Event(event), E_FAIL);
	
	_pObj->Set_Active(false);
	
	return S_OK;
}


HRESULT CEventMgr::Return_Obj(CGameObject* const _pObj)
{
	NULL_CHECK_RETURN(_pObj, E_FAIL);

	EVENT event;
	ZeroMemory(&event, sizeof(EVENT));

	event.lParam = (DWORD_PTR)_pObj;
	event.eType = EVENT_TYPE::RETURN_OBJ;

	for (auto& iter : m_vecEvent)
	{
		if (iter.lParam == event.lParam && iter.eType == event.eType)
			return E_FAIL;
	}

	FAILED_CHECK_RETURN(Add_Event(event), E_FAIL);

	return S_OK;
}

HRESULT CEventMgr::Change_Scene(CScene* const _pScene)
{
	EVENT event;
	ZeroMemory(&event, sizeof(EVENT));

	event.lParam = (DWORD_PTR)_pScene;
	event.eType = EVENT_TYPE::CHANGE_SCENE;

	for (auto& iter : m_vecEvent)
	{
		if (iter.lParam == event.lParam && iter.eType == event.eType)
			return E_FAIL;
	}

	FAILED_CHECK_RETURN(Add_Event(event), E_FAIL);

	return S_OK;

}

HRESULT CEventMgr::Add_Event(const EVENT& _event)
{
	if (EVENT_TYPE::CHANGE_SCENE == _event.eType) // 씬이 생성 되고(레디 -> 애드오브젝트) 씬이 이벤트매니저에 예약된다.
	{
		m_vecEvent.insert(m_vecEvent.begin(), _event);
		return S_OK;
	}
	m_vecEvent.push_back(_event);

	return S_OK;
}

HRESULT CEventMgr::Execute_Event(const EVENT& _event)
{
	switch (_event.eType)
	{
	case EVENT_TYPE::ADD_OBJ:
	{
		CGameObject* pGameObject = (CGameObject*)_event.lParam;

		FAILED_CHECK_RETURN(CManagement::GetInstance()->Add_Object(pGameObject->Get_Type(), _event.wParam, pGameObject), E_FAIL);
	}
	break;
	case EVENT_TYPE::DELETE_OBJ:
	{
		CGameObject* pGameObject = (CGameObject*)_event.lParam;
		m_vecDeleteObj.push_back(pGameObject);
	}
	break;
	case EVENT_TYPE::RETURN_OBJ:
	{
		CGameObject* pGameObject = (CGameObject*)_event.lParam;
		m_vecReturnObj.push_back(pGameObject);

	}
	break;
	case EVENT_TYPE::CHANGE_SCENE:
	{
		CScene* pScene = (CScene*)_event.lParam;
		FAILED_CHECK_RETURN(CManagement::GetInstance()->Change_Scene(pScene), E_FAIL);
	}
	break;
	default:
		break;
	}
	
	return S_OK;

}

void CEventMgr::Free()
{

}
