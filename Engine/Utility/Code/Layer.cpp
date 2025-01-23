#include "..\..\Header\Layer.h"

CLayer::CLayer()
	:	m_bActive(true)
{
}

CLayer::~CLayer()
{
}

CGameObject * CLayer::Get_GameObject(const _tchar * pObjTag)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second;
}

CComponent * CLayer::Get_Component(const _tchar * pObjTag, const COMPONENT_TYPE& _eComponentType, COMPONENTID eID)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;
	
	return iter->second->Get_Component(_eComponentType, eID);
}

HRESULT CLayer::Add_GameObject(const _tchar * pObjTag, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	pGameObject->Set_Name(pObjTag);

	m_mapObject.insert({ pObjTag, pGameObject });

	return S_OK;
}

HRESULT CLayer::Delete_GameObject(CGameObject* pGameObject)
{
	for (map<const _tchar*, CGameObject*>::iterator iter = m_mapObject.begin(); iter != m_mapObject.end(); ++iter)
	{
		if (iter->second == pGameObject)
		{
			iter->second->Release();
			m_mapObject.erase(iter);
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT CLayer::Return_GameObject(CGameObject* pGameObject)
{
	return S_OK;
}

HRESULT CLayer::Ready_Layer()
{
	return S_OK;
}

_int CLayer::Update_Layer(const _float & fTimeDelta)
{
	_int		iResult = 0;

	for (auto& iter : m_mapObject)
	{
		if (!iter.second->Is_Active()) continue;

		iResult = iter.second->Update_Object(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CLayer::LateUpdate_Layer()
{
	for (auto& iter : m_mapObject)
	{
		if (!iter.second->Is_Active()) continue;

		iter.second->LateUpdate_Object();
	}
}

CLayer * CLayer::Create()       
{
	CLayer *	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Layer Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLayer::Free()
{
	//for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());

	for (multimap<const _tchar*, CGameObject*>::iterator iter = m_mapObject.begin(); iter != m_mapObject.end();)
	{
		if (iter->second->Is_Maintain()) // 삭제해서 안되는 오브젝트들은 남겨두도록 한다.
		{
			++iter;
		}
		else
		{
			iter->second->Release();
			m_mapObject.erase(iter++);
		}
	}

	m_mapObject.clear();
}
