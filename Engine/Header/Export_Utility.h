#ifndef Export_Utility_h__
#define Export_Utility_h__

// Strucutre & SingleTon
#include "Management.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"

// Manager
#include "ProtoMgr.h"
#include "RenderMgr.h"
#include "CameraMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"

// Component
#include "TerrainTex.h"
#include "TerrainRcTex.h"
#include "RcCol.h"
#include "RcTex.h"

#include "Transform.h"
#include "Texture.h"
#include "Camera.h"

#include "Collider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "RectCollider.h"
#include "SphereCollider.h"

#include "StateMachine.h"
#include "Animator.h"

#include "AIComponent.h"

#include "RigidBody.h"

// Object
#include "CameraObject.h"
#include "LineObject.h"


BEGIN(Engine)

// Component
inline CComponent*		Get_Component(const OBJ_TYPE& _eObjType,
										const _tchar* pObjTag,
										const COMPONENT_TYPE& _eComponentType,
										COMPONENTID eID);

// Management
inline HRESULT			Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppInstance);
inline const _bool&		Is_Enter_InGame();
inline void				Set_Enter_InGame(const _bool& _b);
inline CGameObject*		Get_Player();
inline const SCENE_TYPE& Get_PrevSceneType();
inline const _bool&		Is_Start_EndingVideo();
inline void				Set_Start_EndingVideo();
// Scene
inline HRESULT			Set_Scene(CScene* pScene);
inline _int				Update_Scene(const _float& fTimeDelta);
inline void				LateUpdate_Scene();
inline void				Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

// ProtoMgr
inline HRESULT			Ready_Texture(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*		Clone_Texture(const _tchar* pProtoTag, CGameObject* _pOwnerObject);
inline HRESULT			Ready_Proto(const COMPONENT_TYPE& _eComType, CComponent* pComponent);
inline CComponent*		Clone_Proto(const COMPONENT_TYPE& _eComType, CGameObject* _pOwnerObject);


// EventMgr
inline HRESULT			Add_Obj(const _tchar* pObjTag, CGameObject* const _pObj);
inline HRESULT			Delete_Obj(CGameObject* const _pObj);
inline HRESULT			Return_Obj(CGameObject* const _pObj);
inline HRESULT			Change_Scene(CScene* const _pScene);

// Renderer
inline void				Add_RenderGroup(RENDERID eType, CGameObject* pGameObject);
inline void				Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void				Clear_RenderGroup();

// CameraMgr
inline CCameraObject*	Get_Camera(const _tchar* pCameraTag);
inline CCameraObject*	Get_CurCamera();
inline HRESULT			Add_Camera(const _tchar* pCameraTag, CCameraObject* pCameraObject);
inline HRESULT			Set_MainCamera(const _tchar* pCameraTag);
inline HRESULT			Change_Camera(const _tchar* pCameraTag);
inline _bool			Is_Blending();
inline HRESULT			Set_ViewSpace();
inline HRESULT			Set_Projection();
inline HRESULT			Set_Viewport();
inline HRESULT			Set_LookAt(CGameObject* pLookAt);
inline HRESULT			Set_Follow(CGameObject* pFollow);
inline const _matrix&   Get_Billboard_X();
inline const _matrix&   Get_WorldMat();
inline void				Shake_Camera(const _float& _fTime = DF_CAMERA_SHAKE_TIME, const _float& _fIntensity = DF_CAMERA_SHAKE_INTENSITY);
inline const _bool&		Is_Shake_Camera();
inline void				Stop_Shake();
inline HRESULT			Start_Action(const CAMERA_ACTION& _eMode, const _vec3& _vStartPos = vec3.one, const _vec3& _vEndPos = vec3.one, const _bool& _bFix = FALSE);
inline const CAMERA_ACTION& Get_CurCameraAction();
inline const _bool&		Is_Fix();
inline void				Start_Fade(const FADE_MODE& _eMode);
inline const _bool&		Is_Fade();
inline const _bool&		Is_BackView();

// CollisionMgr
inline void				Check_Collision(const OBJ_TYPE& _eType1, const OBJ_TYPE& _eType2, const OBJ_TYPE& _eParentType, const COL_TYPE& _eColType1, const COL_TYPE& _eColType2);



// Release
inline void				Release_Utility(); // ΩÃ±€≈Ê µΩ∫∆Æ∑Œ¿Ã

#include "Export_Utility.inl"

END

#endif // Export_Utility_h__


