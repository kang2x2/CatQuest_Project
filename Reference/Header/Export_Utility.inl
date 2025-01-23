#include "Export_Utility.h"
CComponent*			Get_Component(const OBJ_TYPE& _eObjType,
									const _tchar* pObjTag,
									const COMPONENT_TYPE& _eComponentType,
									COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(_eObjType, pObjTag, _eComponentType, eID);
}


HRESULT		Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppInstance)
{
	CManagement*		pManagement = CManagement::GetInstance();
	NULL_CHECK_RETURN(pManagement, E_FAIL);

	*ppInstance = pManagement;

	return S_OK;
}

inline const _bool& Is_Enter_InGame()
{
	return CManagement::GetInstance()->Is_Enter_InGame();
}

inline void Set_Enter_InGame(const _bool& _b)
{
	CManagement::GetInstance()->Set_Enter_InGame(_b);
}

inline CGameObject* Get_Player()
{
	return CManagement::GetInstance()->Get_Player();
}

inline const SCENE_TYPE& Get_PrevSceneType()
{
	return CManagement::GetInstance()->Get_PrevSceneType();
}

inline const _bool& Is_Start_EndingVideo()
{
	return CManagement::GetInstance()->Is_Start_EndingVideo();
}

inline void Set_Start_EndingVideo()
{
	CManagement::GetInstance()->Set_Start_EndingVideo();
}

HRESULT		Set_Scene(CScene* pScene)
{
	return CManagement::GetInstance()->Set_Scene(pScene);
}
_int			Update_Scene(const _float& fTimeDelta)
{
	return CManagement::GetInstance()->Update_Scene(fTimeDelta);
}
void			LateUpdate_Scene()
{
	CManagement::GetInstance()->LateUpdate_Scene();
}
void			Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagement::GetInstance()->Render_Scene(pGraphicDev);
}

HRESULT			Ready_Texture(const _tchar* pProtoTag, CComponent* pComponent)
{
	return CProtoMgr::GetInstance()->Ready_Texture(pProtoTag, pComponent);
}
CComponent*		Clone_Texture(const _tchar* pProtoTag, CGameObject* _pOwnerObject)
{
	return CProtoMgr::GetInstance()->Clone_Texture(pProtoTag, _pOwnerObject);
}

inline HRESULT Ready_Proto(const COMPONENT_TYPE& _eComType, CComponent* pComponent)
{
	return CProtoMgr::GetInstance()->Ready_Proto(_eComType, pComponent);
}

inline CComponent* Clone_Proto(const COMPONENT_TYPE& _eComType, CGameObject* _pOwnerObject)
{
	return CProtoMgr::GetInstance()->Clone_Proto(_eComType, _pOwnerObject);
}

inline HRESULT Add_Obj(const _tchar* pObjTag, CGameObject* const _pObj)
{
	return CEventMgr::GetInstance()->Add_Obj(pObjTag, _pObj);
}

inline HRESULT Delete_Obj(CGameObject* const _pObj)
{
	return CEventMgr::GetInstance()->Delete_Obj(_pObj);
}

inline HRESULT Return_Obj(CGameObject* const _pObj)
{
	return CEventMgr::GetInstance()->Return_Obj(_pObj);
}

inline HRESULT Change_Scene(CScene* const _pScene)
{
	return CEventMgr::GetInstance()->Change_Scene(_pScene);
}

void			Add_RenderGroup(RENDERID eType, CGameObject* pGameObject)
{
	CRenderMgr::GetInstance()->Add_RenderGroup(eType, pGameObject);
}
void			Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev) 
{
	CRenderMgr::GetInstance()->Render_GameObject(pGraphicDev);
}
void			Clear_RenderGroup()
{
	CRenderMgr::GetInstance()->Clear_RenderGroup();
}

inline CCameraObject * Get_Camera(const _tchar * pCameraTag)
{
	return CCameraMgr::GetInstance()->Get_Camera(pCameraTag);
}

inline CCameraObject * Get_CurCamera()
{
	return CCameraMgr::GetInstance()->Get_CurCamera();
}

inline HRESULT Add_Camera(const _tchar * pCameraTag, CCameraObject * pCameraObject)
{
	return CCameraMgr::GetInstance()->Add_Camera(pCameraTag, pCameraObject);
}

inline HRESULT Set_MainCamera(const _tchar * pCameraTag)
{
	return CCameraMgr::GetInstance()->Set_MainCamera(pCameraTag);
}

inline HRESULT Change_Camera(const _tchar * pCameraTag)
{
	return CCameraMgr::GetInstance()->Change_Camera(pCameraTag);
}

inline _bool Is_Blending()
{
	return CCameraMgr::GetInstance()->Is_Blending();
}

inline HRESULT Set_ViewSpace()
{
	return CCameraMgr::GetInstance()->Set_ViewSpace();
}

inline HRESULT Set_Projection()
{
	return CCameraMgr::GetInstance()->Set_Projection();
}

inline HRESULT Set_Viewport()
{
	return CCameraMgr::GetInstance()->Set_Viewport();
}

inline HRESULT Set_LookAt(CGameObject * pLookAt)
{
	return CCameraMgr::GetInstance()->Set_LookAt(pLookAt);
}

inline HRESULT Set_Follow(CGameObject * pFollow)
{
	return CCameraMgr::GetInstance()->Set_Follow(pFollow);
}

inline const _matrix& Get_Billboard_X()
{
	return CCameraMgr::GetInstance()->Get_Billboard_X();
}

inline const _matrix& Get_WorldMat()
{
	return CCameraMgr::GetInstance()->Get_WorldMat();
}

inline void Shake_Camera(const _float& _fTime, const _float& _fIntensity)
{
	CCameraMgr::GetInstance()->Shake_Camera(_fTime, _fIntensity);
}

inline const _bool& Is_Shake_Camera()
{
	return CCameraMgr::GetInstance()->Is_Shake_Camera();
}

inline void Stop_Shake()
{
	CCameraMgr::GetInstance()->Stop_Shake();
}

inline HRESULT Start_Action(const CAMERA_ACTION& _eMode, const _vec3& _vStartPos, const _vec3& _vEndPos, const _bool& _bFix)
{
	return CCameraMgr::GetInstance()->Start_Action(_eMode, _vStartPos, _vEndPos, _bFix);
}

inline const CAMERA_ACTION& Get_CurCameraAction()
{
	return CCameraMgr::GetInstance()->Get_CurCameraAction();
}

inline const _bool& Is_Fix()
{
	return CCameraMgr::GetInstance()->Is_Fix();
}

inline void Start_Fade(const FADE_MODE& _eMode)
{
	CCameraMgr::GetInstance()->Start_Fade(_eMode);
}

inline const _bool& Is_Fade()
{
	return CCameraMgr::GetInstance()->Is_Fade();
}

inline const _bool& Is_BackView()
{
	return CCameraMgr::GetInstance()->Is_BackView();
}

inline void Check_Collision(const OBJ_TYPE& _eType1, const OBJ_TYPE& _eType2, const OBJ_TYPE& _eParentType, COL_TYPE& _eColType1, const COL_TYPE& _eColType2)
{
	CCollisionMgr::GetInstance()->Check_Collision(_eType1, _eType2, _eParentType, _eColType1, _eColType2);
}



void			Release_Utility()
{
	CProtoMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();
	CRenderMgr::GetInstance()->DestroyInstance();
	CCameraMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CEventMgr::GetInstance()->DestroyInstance();
}