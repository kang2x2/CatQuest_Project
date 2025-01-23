#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CProtoMgr : public CBase
{
	DECLARE_SINGLETON(CProtoMgr)

private:
	explicit CProtoMgr();
	virtual ~CProtoMgr();

public:
	HRESULT			Ready_Texture(const _tchar* pTextureTag, CComponent* pComponent);
	CComponent*		Clone_Texture(const _tchar* pTextureTag, CGameObject* _pOwnerObject);

	HRESULT			Ready_Proto(const COMPONENT_TYPE& _eComType, CComponent* pComponent);
	CComponent*		Clone_Proto(const COMPONENT_TYPE& _eComType, CGameObject* _pOwnerObject);

private:
	CComponent*		Find_Texture(const _tchar* pTextureTag);
	CComponent*		Find_Prototype(const COMPONENT_TYPE& _eComType);

private:
	map<const _tchar*, CComponent*>			m_mapProto_Char;
	map<COMPONENT_TYPE, CComponent*>		m_mapProto_Enum;

public:
	virtual void Free();
};

END