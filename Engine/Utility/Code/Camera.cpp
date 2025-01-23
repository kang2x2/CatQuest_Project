#include "..\..\Header\Camera.h"

#include "GameObject.h"
#include "Transform.h"

#include "Export_System.h"

CCamera::CCamera()
	: m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(PERSPECTIVE)
	, m_fSpeedZoom(50.f)
	, m_fDistance(0.f)
	, m_pHwnd(nullptr)
	, m_bShake(FALSE)
	, m_fIntensity(0.f)
	, m_fShakeTime(0.f)
	, m_fAccTime(0.f)
	, m_fInitLookY(0.f)
	, m_bAction(FALSE)
{
	ZeroMemory(&m_tVspace, sizeof(VIEWSPACE));

	ZeroMemory(&m_tProj, sizeof(PROJECTION));
	ZeroMemory(&m_tVport, sizeof(D3DVIEWPORT9));
	ZeroMemory(&m_matBillboardX, sizeof(_matrix));
	ZeroMemory(&m_matBillboardY, sizeof(_matrix));
	ZeroMemory(&m_matWorld, sizeof(_matrix));
	ZeroMemory(&m_matProj, sizeof(_matrix));
	ZeroMemory(&m_matView, sizeof(_matrix));
	ZeroMemory(&m_tFOVLerp, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tVec3Lerp, sizeof(LERP_VEC3_INFO));
	ZeroMemory(&m_tHeightLerp, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tDistanceLerp, sizeof(LERP_FLOAT_INFO));

}

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev, HWND* _pHwnd)
	: CComponent(pGraphicDev, COMPONENT_TYPE::CAMERA)
	, m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(PERSPECTIVE)
	, m_fSpeedZoom(100.f)
	, m_fDistance(10.f)
	, m_pHwnd(_pHwnd)
	, m_bShake(FALSE)
	, m_fIntensity(0.f)
	, m_fShakeTime(0.f)
	, m_fAccTime(0.f)
	, m_fInitLookY(0.f)
	, m_bAction(FALSE)

{
	ZeroMemory(&m_tVspace, sizeof(VIEWSPACE));
	ZeroMemory(&m_tProj, sizeof(PROJECTION));
	ZeroMemory(&m_tVport, sizeof(D3DVIEWPORT9));
	ZeroMemory(&m_matBillboardX, sizeof(_matrix));
	ZeroMemory(&m_matBillboardY, sizeof(_matrix));
	ZeroMemory(&m_matWorld, sizeof(_matrix));
	ZeroMemory(&m_matProj, sizeof(_matrix));
	ZeroMemory(&m_matView, sizeof(_matrix));
	ZeroMemory(&m_tFOVLerp, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tVec3Lerp, sizeof(LERP_VEC3_INFO));
	ZeroMemory(&m_tHeightLerp, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_tDistanceLerp, sizeof(LERP_FLOAT_INFO));

}

CCamera::CCamera(const CCamera & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
	, m_pLookAt(nullptr)
	, m_pFollow(nullptr)
	, m_eProjectID(rhs.m_eProjectID)
	, m_fSpeedZoom(rhs.m_fSpeedZoom)
	, m_tVspace(rhs.m_tVspace)
	, m_tProj(rhs.m_tProj)
	, m_tVport(rhs.m_tVport)
	, m_fDistance(rhs.m_fDistance)
	, m_pHwnd(rhs.m_pHwnd)
	, m_bShake(FALSE)
	, m_fIntensity(0.f)
	, m_fShakeTime(0.f)
	, m_fAccTime(0.f)
	, m_fInitLookY(0.f)
	, m_bAction(FALSE)
	, m_tFOVLerp(rhs.m_tFOVLerp)
	, m_tVec3Lerp(rhs.m_tVec3Lerp)
	, m_tHeightLerp(rhs.m_tHeightLerp)
	, m_tDistanceLerp(rhs.m_tDistanceLerp)

{
}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Camera()
{
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc;
	GetClientRect(*m_pHwnd, &rc);

	// View Space
	m_tVspace.Eye		= vec3.zero;
	m_tVspace.LookAt	= vec3.forward;
	m_tVspace.Up		= vec3.up;

	// Projection
	m_tProj.FOV			= D3DXToRadian(60.f);
	m_tProj.Aspect		= (float)rc.right / (float)rc.bottom;
	m_tProj.Near		= 0.1f;
	m_tProj.Far			= 1000.0f;

	// View Port
	m_tVport.X			= 0;
	m_tVport.Y			= 0;
	m_tVport.Width		= (rc.right - rc.left);
	m_tVport.Height		= (rc.bottom - rc.top);
	m_tVport.MinZ		= 0.f; // Default
	m_tVport.MaxZ		= 1.f; // Default

	return S_OK;
}

_int CCamera::Update_Component(const _float & fTimeDelta)
{
	return 0;
}
HRESULT CCamera::Set_ViewSpace()
{
	// 뷰스페이스에 대한 데이터 m_tVspace는 클라에서 구현한 개별 카메라에서 세팅한다. (컴포넌트의 필드는 퍼블릭이다.)
	
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);

	D3DXMatrixIdentity(&m_matView);
	
	if (m_bShake) Apply_Shake();
	
	m_pGraphicDev->SetTransform(D3DTS_VIEW,
		D3DXMatrixLookAtLH(&m_matView, &m_tVspace.Eye, &m_tVspace.LookAt, &m_tVspace.Up));

	// 여러 곳에서 카메라의 월드행렬을 사용하기 위해 세팅
	D3DXMatrixInverse(&m_matWorld, NULL, &m_matView);

	// 뷰스페이스 설정 때 빌보드X 행렬을 세팅해둔다 (셋트랜스폼 최소화)
	D3DXMatrixIdentity(&m_matBillboardX);

	m_matBillboardX._22 = m_matView._22;
	m_matBillboardX._23 = m_matView._23;
	m_matBillboardX._32 = m_matView._32;
	m_matBillboardX._33 = m_matView._33;

	D3DXMatrixInverse(&m_matBillboardX, NULL, &m_matBillboardX);

	// 뷰스페이스 설정 때 빌보드Y 행렬을 세팅해둔다 (셋트랜스폼 최소화)
	D3DXMatrixIdentity(&m_matBillboardY);

	m_matBillboardX._11 = m_matView._11;
	m_matBillboardX._33 = m_matView._33;
	m_matBillboardX._31 = m_matView._31;
	m_matBillboardX._33 = m_matView._33;

	D3DXMatrixInverse(&m_matBillboardY, NULL, &m_matBillboardY);

	return S_OK;
}

HRESULT CCamera::Set_Projection()
{
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc{};
	GetClientRect(*m_pHwnd, &rc);

	D3DXMatrixIdentity(&m_matProj);

	if (PERSPECTIVE == m_eProjectID)
	{
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, 
			D3DXMatrixPerspectiveFovLH(&m_matProj, m_tProj.FOV, m_tProj.Aspect, m_tProj.Near, m_tProj.Far));
	}
	else if (ORTHOGRAPHIC == m_eProjectID)
	{
		/*m_pGraphicDev->SetTransform(D3DTS_PROJECTION, 
			D3DXMatrixPerspectiveFovLH(&matProj, m_tProj.FOV, m_tProj.Aspect, m_tProj.Near, m_tProj.Far));*/
	}

	//cout << m_tProj.FOV << endl;
	return S_OK;
}

HRESULT CCamera::Set_Viewport()
{
	NULL_CHECK_RETURN(m_pGraphicDev, E_FAIL);
	NULL_CHECK_RETURN(m_pHwnd, E_FAIL);

	RECT rc{};
	GetClientRect(*m_pHwnd, &rc);

	m_pGraphicDev->SetViewport(&m_tVport);

	return S_OK;
}


HRESULT CCamera::Set_ViewSpace(const _matrix& _matView)
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &_matView);
	return S_OK;
}

HRESULT CCamera::Set_Projection(const _matrix& _matProj)
{
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &_matProj);
	return S_OK;
}

HRESULT CCamera::Set_Viewport(const D3DVIEWPORT9& _tViewport)
{
	m_pGraphicDev->SetViewport(&_tViewport);
	return S_OK;
}

void CCamera::Lerp_Distance(const _float& _fTime, const _float _fStartDist, const _float _fEndDist, const LERP_MODE& _eMode)
{
	m_tDistanceLerp.Init_Lerp(_eMode);
	m_tDistanceLerp.Set_Lerp(_fTime, _fStartDist, _fEndDist);
}

void CCamera::Lerp_FOV(const _float& _fTime, const _float _fStartFOV, const _float _fEndFOV, const LERP_MODE& _eMode)
{
	m_tFOVLerp.Init_Lerp(_eMode);
	m_tFOVLerp.Set_Lerp(_fTime, _fStartFOV, _fEndFOV);
}

void CCamera::Lerp_Vec3(const _float& _fTime, const _vec3 _vStartVec3, const _vec3 _vEndVec3, const LERP_MODE& _eMode)
{
	m_tVec3Lerp.Init_Lerp(_eMode);
	m_tVec3Lerp.Set_Lerp(_fTime, _vStartVec3, _vEndVec3);
}

void CCamera::Lerp_Height(const _float& _fTime, const _float _fStartH, const _float _fEndH, const LERP_MODE& _eMode)
{
	m_tHeightLerp.Init_Lerp(_eMode);
	m_tHeightLerp.Set_Lerp(_fTime, _fStartH, _fEndH);
}

const VIEWSPACE CCamera::Calculate_Nonelerp_Eye(const _vec3& _vTargetPos)
{
	VIEWSPACE vNoneLerpView{};

	NULL_CHECK_RETURN(m_pLookAt, vNoneLerpView);
	NULL_CHECK_RETURN(m_pFollow, vNoneLerpView);

	_vec3 vDir1 = m_tVspace.Eye - _vTargetPos;
	_vec3 vDir2 = { vDir1.x, 0.f, vDir1.z };

	D3DXVec3Normalize(&vDir1, &vDir1);
	D3DXVec3Normalize(&vDir2, &vDir2);

	_float fTheta = D3DXVec3Dot(&vDir1, &vDir2);
	_float fY = sinf(fTheta) * m_fDistance * CAM_HEIGHT_MAG;

	vNoneLerpView.Eye = _vec3{ _vTargetPos.x, fY, _vTargetPos.z - m_fDistance };
	vNoneLerpView.LookAt = m_pLookAt->Get_Transform()->Get_Info(INFO_POS);
	vNoneLerpView.Up = vec3.up;

	return vNoneLerpView;
}

void CCamera::Shake_Camera(const _float& _fTime, const _float& _fIntensity)
{
	m_bShake = TRUE;
	m_fShakeTime = _fTime;
	m_fIntensity = _fIntensity;
	m_fAccTime = 0.f;
}

void CCamera::Stop_Shake()
{
	if (m_bShake)
	{
		m_bShake = FALSE;
		m_fShakeTime = 0.f;
		m_fIntensity = 0.f;
		m_fAccTime = 0.f;
	}
}

void CCamera::Apply_Shake()
{

	m_fAccTime += Engine::Get_TimeDelta(L"Timer_FPS65");

	if (m_fShakeTime <= m_fAccTime)
	{
		Stop_Shake();
		return;
	}
	
	_vec3 vShakeDelta { _float(rand() % (_int)m_fIntensity),
							_float(rand() % (_int)m_fIntensity),
							0.f };

	vShakeDelta *= 0.01f;	

	m_tVspace.Eye += vShakeDelta;

	m_tVspace.LookAt += vShakeDelta;
}

CCamera * CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, HWND* const _pHwnd)
{
	CCamera*		pInstance = new CCamera(pGraphicDev, _pHwnd);

	if (FAILED(pInstance->Ready_Camera()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CCamera::Clone(CGameObject* _pOwnerObject)
{
	return new CCamera(*this, _pOwnerObject);
}

void CCamera::Free()
{
	CComponent::Free();
}
