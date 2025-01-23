#include "..\..\Header\CameraObject.h"

#include "ProtoMgr.h"

CCameraObject::CCameraObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::CAMERA, OBJ_ID::CAMERA_TARGET_OBJ)
	, m_pCameraCom(nullptr)
{
	
}

CCameraObject::CCameraObject(const CCameraObject & rhs)
	: Engine::CGameObject(rhs)
	, m_pCameraCom(rhs.m_pCameraCom)
{
	
}

CCameraObject::~CCameraObject()
{
}

HRESULT CCameraObject::Ready_Object(void)
{
	CGameObject::Ready_Object();

	CComponent*			pComponent = nullptr;

	pComponent = m_pCameraCom = dynamic_cast<CCamera*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::CAMERA, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::CAMERA, pComponent);

	return S_OK;
}

void CCameraObject::Free()
{
	CGameObject::Free();
}
