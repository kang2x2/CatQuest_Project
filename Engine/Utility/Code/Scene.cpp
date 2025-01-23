#include "..\..\Header\Scene.h"

#include "Export_Function.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev, const SCENE_TYPE& _eType)
	: m_pGraphicDev(pGraphicDev), m_eType(_eType), m_bStartFade(FALSE)
{
	m_pGraphicDev->AddRef();
}

CScene::~CScene()
{
}


CGameObject * CScene::Get_GameObject(const OBJ_TYPE & _eObjType, const _tchar * pObjTag)
{
	auto		iter = m_mapLayer.find(_eObjType);

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second->Get_GameObject(pObjTag);
}

CComponent * CScene::Get_Component(const OBJ_TYPE& _eObjType, const _tchar * pObjTag, const COMPONENT_TYPE& _eComponentType, COMPONENTID eID)
{
	auto		iter = m_mapLayer.find(_eObjType);

	if (iter == m_mapLayer.end())
		return nullptr;
	
	return iter->second->Get_Component(pObjTag, _eComponentType, eID);
}

HRESULT CScene::Add_Object(const OBJ_TYPE & _eObjType, const _tchar * pObjTag, CGameObject* _pObj)
{
	CLayer* pLayer = Get_Layer(_eObjType);

	NULL_CHECK_RETURN(pLayer, E_FAIL);

	FAILED_CHECK_RETURN(pLayer->Add_GameObject(pObjTag, _pObj), E_FAIL);

	if (_pObj->Is_Maintain())
		m_vecMaintain.push_back(_pObj);

	return S_OK;
}

CLayer * CScene::Get_Layer(const OBJ_TYPE& _eType)
{	
	auto iter = m_mapLayer.find(_eType);

	if (iter == m_mapLayer.end())
		return nullptr;

	return iter->second;

	return nullptr;
}

HRESULT CScene::Release_MaintainObj()
{
	for_each(m_vecMaintain.begin(), m_vecMaintain.end(), CDeleteObj());
	m_vecMaintain.clear();

	return S_OK;
}

// ¼ºÇõ Ãß°¡
HRESULT CScene::Empty_Layer(const OBJ_TYPE& _eObjType)
{
	CLayer* pLayer = Get_Layer(_eObjType);

	NULL_CHECK_RETURN(pLayer, E_FAIL);

	pLayer->Get_ObjectMap().clear();

	return S_OK;
}

HRESULT CScene::Ready_Scene()
{
	return S_OK;

}

_int CScene::Update_Scene(const _float & fTimeDelta)
{
	_int		iResult = 0;


	for (auto& iter : m_mapLayer)
	{
		if (!iter.second->Is_LayerActive())
		{
			switch (iter.first)
			{
			case::OBJ_TYPE::PLAYER:
			{
				for (auto iter2 : iter.second->Get_ObjectMap())
				{
					Engine::Add_RenderGroup(RENDER_ALPHA, iter2.second);
				}
			}
			case::OBJ_TYPE::MONSTER:
			{
				for (auto iter2 : iter.second->Get_ObjectMap())
				{
					Engine::Add_RenderGroup(RENDER_ALPHA, iter2.second);
				}
			}
			case::OBJ_TYPE::EFFECT:
			{
				for (auto iter2 : iter.second->Get_ObjectMap())
				{
					Engine::Add_RenderGroup(RENDER_ALPHA, iter2.second);
				}
			}
			default:
				break;
			}
			continue;
		}

		iResult = iter.second->Update_Layer(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CScene::LateUpdate_Scene()
{
	for (auto& iter : m_mapLayer)
	{
		if (!iter.second->Is_LayerActive()) continue;

		iter.second->LateUpdate_Layer();
	}
		
}

void CScene::Free()
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();

	Safe_Release(m_pGraphicDev);
}
