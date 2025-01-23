#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CGameObject*						Get_GameObject(const _tchar* pObjTag);

	CComponent*							Get_Component(const _tchar* pObjTag, 
														const COMPONENT_TYPE& _eComponentType, 
														COMPONENTID eID);

	multimap<const _tchar*, CGameObject*>&	Get_ObjectMap() { return m_mapObject; }

public:
	HRESULT								Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);

	HRESULT								Delete_GameObject(CGameObject* pGameObject);
	HRESULT								Return_GameObject(CGameObject* pGameObject);

	HRESULT								Ready_Layer();
	_int								Update_Layer(const _float& fTimeDelta);
	void								LateUpdate_Layer();

	//¡ÿ √ﬂ∞°
	const _bool&						Is_LayerActive() const { return m_bActive; }
	void								Layer_SetActive(const _bool& bActive) { m_bActive = bActive; }
	
private:
	multimap<const _tchar*, CGameObject*>	m_mapObject;

	_bool	m_bActive;

public:
	static CLayer*						Create();
	virtual	void						Free();
};

END