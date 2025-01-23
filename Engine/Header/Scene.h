#pragma once

#include "Layer.h"

BEGIN(Engine)

class ENGINE_DLL CScene : public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev, const SCENE_TYPE& _eType);
	virtual ~CScene();

public:
	CLayer*							Get_Layer(const OBJ_TYPE& _eType);

	CGameObject*					Get_GameObject(const OBJ_TYPE& _eObjType,
													const _tchar* pObjTag);

	CComponent*						Get_Component(const OBJ_TYPE& _eObjType,
													const _tchar * pObjTag,
													const COMPONENT_TYPE& _eComponentType,
													COMPONENTID eID);

	HRESULT							Add_Object(const OBJ_TYPE& _eObjType,
													const _tchar* pObjTag, CGameObject* _pObj);

	const SCENE_TYPE&				Get_SceneType() const { return m_eType; }

	vector<CGameObject*>			Get_MaintainObj() const { return m_vecMaintain; }
	HRESULT							Release_MaintainObj();

public:
	// 성혁 추가
	HRESULT							Empty_Layer(const OBJ_TYPE& _eObjType);

public:
	virtual HRESULT					Ready_Scene();
	virtual _int					Update_Scene(const _float& fTimeDelta);
	virtual void					LateUpdate_Scene();
	virtual void					Render_Scene()PURE; 

private:
	virtual void					Update_Fade() {};

protected:
	LPDIRECT3DDEVICE9				m_pGraphicDev;
	map<OBJ_TYPE, CLayer*>			m_mapLayer;
	vector<CGameObject*>			m_vecMaintain; // 씬 변경시 살려둘 오브젝트

	SCENE_TYPE						m_eType;

	_bool							m_bStartFade;

public:
	virtual void					Free();
};

END