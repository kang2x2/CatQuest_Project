#include "stdafx.h"
#include "..\Header\Tool_Camera.h"

#include "Export_Function.h"

CTool_Camera::CTool_Camera(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CCameraObject(pGraphicDev)
{

}
CTool_Camera::CTool_Camera(const CTool_Camera& rhs)
	: Engine::CCameraObject(rhs)
{

}
CTool_Camera::~CTool_Camera()
{
}

HRESULT CTool_Camera::Ready_Object(void)
{
	CCameraObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fDefaultHeight = 80.f;
	m_fNearZoom = CAM_DISTANCE_DEFAULT;
	m_fFarZoom = 60.f;
	m_pCameraCom->m_fDistance = m_fNearZoom * 3.f;

	m_pTransformCom->Set_Pos(_vec3{ 0.f, m_fDefaultHeight, -m_pCameraCom->m_fDistance });
	m_pCameraCom->m_fSpeedZoom = 100.f;

	m_eView = TOOL_VIEW::DEFAULT;

	return S_OK;
}

Engine::_int CTool_Camera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);

	switch (m_eView)
	{
	case TOOL_VIEW::DEFAULT:
		Update_Perspevtive(fTimeDelta);
		break;
	case TOOL_VIEW::INGAME:
		Update_Perspevtive(fTimeDelta);
		break;
	case TOOL_VIEW::LINE:
		Update_Perspevtive(fTimeDelta);
		break;
	case TOOL_VIEW::TYPEEND:
		break;
	default:
		break;
	}
	return iExit;
}

void CTool_Camera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CTool_Camera::Key_Input(const _float& fTimeDelta)
{
	if (CInputDev::GetInstance()->Key_Down(VK_F1))
	{
		m_eView = TOOL_VIEW::DEFAULT;

		// Set Up
		m_pCameraCom->m_fDistance = m_fNearZoom * 2.f;
		CCameraMgr::GetInstance()->Set_Projection();
		CCameraMgr::GetInstance()->Set_Viewport();
	}
	else if (CInputDev::GetInstance()->Key_Down(VK_F2))
	{
		m_eView = TOOL_VIEW::INGAME;

		// Set Up
		m_pCameraCom->m_fDistance = m_fNearZoom;
		CCameraMgr::GetInstance()->Set_Projection();
		CCameraMgr::GetInstance()->Set_Viewport();
	}
	else if (CInputDev::GetInstance()->Key_Down(VK_F3))
	{
		m_eView = TOOL_VIEW::LINE;
		m_pCameraCom->m_fDistance = 30.f;

		_matrix    matProj;
		D3DXMatrixOrthoLH(&matProj, WINCX, WINCY, 0.1f, 500.f);
		m_pCameraCom->Set_Projection(matProj);  
	}
}


HRESULT CTool_Camera::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	return S_OK;
}

void CTool_Camera::Update_Perspevtive(const _float& fTimeDelta)
{
	_long dwMouse = 0;


	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (TOOL_VIEW::DEFAULT == m_eView || TOOL_VIEW::LINE == m_eView)
		{
			if (0 < dwMouse)
				m_pCameraCom->m_fDistance -= m_pCameraCom->m_fSpeedZoom * fTimeDelta * 10.f;
			else
				m_pCameraCom->m_fDistance += m_pCameraCom->m_fSpeedZoom * fTimeDelta * 10.f;

		}
		else if (TOOL_VIEW::INGAME == m_eView)
		{
			m_pCameraCom->m_fDistance = m_fNearZoom;
		}
	}

	// 02. Update View Space Data
	NULL_CHECK(m_pCameraCom->m_pLookAt);
	NULL_CHECK(m_pCameraCom->m_pFollow);
	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);

	// 03. 타겟까지의 디스턴스에 따른 카메라의 높이값을 구한다.
	_vec3 vDir1 = m_pTransformCom->Get_Info(INFO_POS) - m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };
	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);
	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_pCameraCom->m_fDistance * CAM_HEIGHT_MAG;

	if (TOOL_VIEW::LINE == m_eView)
	{
		m_pTransformCom->Set_Pos(_vec3{ vFollowPos.x,
										m_pCameraCom->m_fDistance,
										vFollowPos.z});

		m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
		m_pCameraCom->m_tVspace.LookAt = m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
		m_pCameraCom->m_tVspace.Up = m_pTransformCom->Get_Info(INFO_UP);
	}
	else
	{
		m_pTransformCom->Set_Pos(_vec3{ vFollowPos.x,
										fY,
										vFollowPos.z - m_pCameraCom->m_fDistance });

		m_pCameraCom->m_tVspace.Eye = m_pTransformCom->Get_Info(INFO_POS);
		m_pCameraCom->m_tVspace.LookAt = m_pCameraCom->m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
		m_pCameraCom->m_tVspace.Up = vec3.up;
	}

}

void CTool_Camera::Update_Orthographic(const _float& fTimeDelta)
{
	_long dwMouse = 0;
	_matrix matView;
	D3DXMatrixIdentity(&matView);

	if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
	{
		if (0 < dwMouse)
			m_pCameraCom->m_fDistance -= m_pCameraCom->m_fSpeedZoom * fTimeDelta;
		else
			m_pCameraCom->m_fDistance += m_pCameraCom->m_fSpeedZoom * fTimeDelta;
	}

	NULL_CHECK(m_pCameraCom->m_pLookAt);
	NULL_CHECK(m_pCameraCom->m_pFollow);

	_vec3 vFollowPos = m_pCameraCom->m_pFollow->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vCamPos = { vFollowPos.x, m_pCameraCom->m_fDistance, vFollowPos.z };
	
	D3DXMatrixLookAtLH(&matView, &vCamPos, &vFollowPos, &vec3.up);

	m_pCameraCom->Set_ViewSpace(matView);

	/*_vec3 vPos = vFollowPos;
	cout <<  vPos.x << "\t" << vPos.y << "\t" << vPos.z << endl;*/
}

void CTool_Camera::Free()
{
	__super::Free();
}

CTool_Camera* CTool_Camera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTool_Camera* pInstance = new CTool_Camera(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}
