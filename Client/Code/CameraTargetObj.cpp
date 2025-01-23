#include "stdafx.h"
#include "..\Header\CameraTargetObj.h"

#include "Export_Function.h"

CCameraTargetObj::CCameraTargetObj(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::PLAYER, OBJ_ID::CAMERA_TARGET_OBJ)
{
}

CCameraTargetObj::CCameraTargetObj(const CCameraTargetObj& rhs)
	: Engine::CGameObject(rhs)
	, m_tMoveInfo(rhs.m_tMoveInfo)
{

}

CCameraTargetObj::~CCameraTargetObj()
{
}

HRESULT CCameraTargetObj::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 0.f, m_pTransformCom->Get_Scale().y, 0.f });

	// Camera Setting
	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())
	{
		CCameraMgr::GetInstance()->Set_Follow(this);
		CCameraMgr::GetInstance()->Set_LookAt(this);
	}

	m_tMoveInfo.fMoveSpeed *= 3.f;
	return S_OK;
}

Engine::_int CCameraTargetObj::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);

	return iExit;
}

void CCameraTargetObj::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CCameraTargetObj::Render_Object()
{

}

HRESULT CCameraTargetObj::Add_Component()
{
	return S_OK;
}

void CCameraTargetObj::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(vec3.forward + -vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(-vec3.forward + vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S) && CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(-vec3.forward - vec3.right, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_W))
		m_pTransformCom->Translate(DIR_FORWARD, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_S))
		m_pTransformCom->Translate(DIR_FORWARD, fTimeDelta * -m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_D))
		m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * m_tMoveInfo.fMoveSpeed);
	else if (CInputDev::GetInstance()->Get_DIKeyState(DIKEYBOARD_A))
		m_pTransformCom->Translate(DIR_RIGHT, fTimeDelta * -m_tMoveInfo.fMoveSpeed);
}

void CCameraTargetObj::Free()
{
	__super::Free();
}

CCameraTargetObj* CCameraTargetObj::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCameraTargetObj* pInstance = new CCameraTargetObj(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("CameraTargetObj Create Failed");
		return nullptr;
	}

	return pInstance;
}
