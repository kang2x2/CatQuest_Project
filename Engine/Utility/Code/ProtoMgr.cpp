#include "..\..\Header\ProtoMgr.h"

#include "..\..\Header\GameObject.h"

IMPLEMENT_SINGLETON(CProtoMgr)

CProtoMgr::CProtoMgr()
{
}

CProtoMgr::~CProtoMgr()
{
	Free();
}

HRESULT CProtoMgr::Ready_Texture(const _tchar * pTextureTag, CComponent * pComponent)
{
	CComponent*		pPrototype = Find_Texture(pTextureTag);

	if (nullptr != pPrototype)
		return E_FAIL;

	m_mapProto_Char.emplace(pTextureTag, pComponent);

	return S_OK;
}

HRESULT CProtoMgr::Ready_Proto(const COMPONENT_TYPE& _eComType, CComponent* pComponent)
{
	CComponent* pPrototype = Find_Prototype(_eComType);

	if (nullptr != pPrototype)
		return E_FAIL;

	m_mapProto_Enum.emplace(_eComType, pComponent);

	return S_OK;
}
CComponent * CProtoMgr::Clone_Texture(const _tchar * pTextureTag, CGameObject* _pOwnerObject)
{
	CComponent* pPrototype = Find_Texture(pTextureTag);

	NULL_CHECK_RETURN(pPrototype, nullptr);

	return pPrototype->Clone(_pOwnerObject);
}

CComponent* CProtoMgr::Clone_Proto(const COMPONENT_TYPE& _eComType, CGameObject* _pOwnerObject)
{
	CComponent* pPrototype = Find_Prototype(_eComType);

	NULL_CHECK_RETURN(pPrototype, nullptr);

	return pPrototype->Clone(_pOwnerObject);
}

CComponent * CProtoMgr::Find_Texture(const _tchar * pTextureTag)
{
	auto		iter = find_if(m_mapProto_Char.begin(), m_mapProto_Char.end(), CTag_Finder(pTextureTag));

	if (iter == m_mapProto_Char.end())
		return nullptr;
	
	return iter->second;
}

CComponent* CProtoMgr::Find_Prototype(const COMPONENT_TYPE& _eComType)
{
	auto	iter = m_mapProto_Enum.find(_eComType);

	if (iter == m_mapProto_Enum.end())
		return nullptr;

	return iter->second;
}

void CProtoMgr::Free()
{
	for_each(m_mapProto_Char.begin(), m_mapProto_Char.end(), CDeleteMap());
	m_mapProto_Char.clear();

	for_each(m_mapProto_Enum.begin(), m_mapProto_Enum.end(), CDeleteMap());
	m_mapProto_Enum.clear();
}
