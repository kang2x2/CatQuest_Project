#pragma once

#include "Engine_Define.h"
#include "Base.h"
#include "Scene.h"


BEGIN(Engine)

class CGraphicDev;

class ENGINE_DLL CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit CManagement();
	virtual ~CManagement();

#pragma region Access Methods

public:

	CScene*				Get_CurScene	() const { return m_pCurScene; }
	HRESULT				Set_Scene		(CScene* pScene);
	HRESULT				Change_Scene	(CScene* _pScene);

	CLayer*				Get_Layer		(const OBJ_TYPE& _eType);

	CGameObject*		Get_GameObject	(const OBJ_TYPE& _eObjType, 
											const _tchar* pObjTag);
	HRESULT				Add_Object		(const OBJ_TYPE& _eObjType,
											const _tchar* _pObjTag, CGameObject* _pObj);

	CComponent*			Get_Component	(const OBJ_TYPE& _eObjType,
											const _tchar* pObjTag,
											const COMPONENT_TYPE& _eComponentType,
											COMPONENTID eID);
	CGameObject*		Get_Player();

	const PLAY_MODE&	Get_PlayMode	() const { return m_ePlayMode; }
	const GAME_STATUS&	Get_GameStatus	() const { return m_eGameStatus; }
	const SCENE_TYPE& Get_PrevSceneType() const { return m_ePrevSceneType; }




	void				Set_PlayMode	(const PLAY_MODE& _eMode) { m_ePlayMode = _eMode; }
	void				Set_GameStatus  (const GAME_STATUS& _eStatus) {m_eGameStatus = _eStatus; }
	void				Set_Debug_Toggle() { m_bDebug = !m_bDebug; }
	const _bool&		Is_Debug() const { return m_bDebug; }
	const _bool&		Is_Enter_InGame() const { return m_bEnterInGame; }
	void				Set_Enter_InGame(const _bool& _b) { m_bEnterInGame = _b; }

	const _bool&		Is_Start_EndingVideo() const { return m_bStartEndingVideo; }
	void				Set_Start_EndingVideo() { m_bStartEndingVideo = TRUE; }

public:

#pragma endregion

public:
	_int				Update_Scene(const _float& fTimeDelta);
	void				LateUpdate_Scene();
	void				Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CScene*				m_pCurScene;
	SCENE_TYPE			m_ePrevSceneType;
	PLAY_MODE			m_ePlayMode;
	GAME_STATUS			m_eGameStatus;
	_bool				m_bDebug;
	_bool				m_bEnterInGame; //월드에 최초로 진입했는지

	_bool				m_bStartEndingVideo;

public:
	virtual void		Free();
};

END