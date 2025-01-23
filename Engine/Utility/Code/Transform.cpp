#include "..\..\Header\Transform.h"

#include "CameraMgr.h"
#include "GameObject.h"
#include "Export_Function.h"

CTransform::CTransform()
	: m_vAngle(vec3.zero)
	, m_vScale(vec3.one)
	, m_vDir(vec3.right)
{
	ZeroMemory(m_vInfo, sizeof(m_vInfo));
	D3DXMatrixIdentity(&m_matWorld);
}

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev, COMPONENT_TYPE::TRANSFORM)
{
	ZeroMemory(&m_vAngle	, sizeof(_vec3));
	ZeroMemory(&m_vScale	, sizeof(_vec3));
	ZeroMemory(&m_quatQ		, sizeof(_quat));
	ZeroMemory(&m_vInfo		, sizeof(_vec3) * INFO_END);
	ZeroMemory(& m_vDir     , sizeof(_vec3));
	D3DXMatrixIdentity(&m_matWorld);

	Cal_WorldMat();
}

CTransform::CTransform(const CTransform & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	Ready_Transform();
}

CTransform::~CTransform()
{
}

void CTransform::Translate(const DIRID& _eDir, const _float& fSpeed, const SPACEID _eSpace)
{
	// 현재 자신의 위치에서 지정한 방향으로 이동한다. (eDir : 축, _eSpace 스페이스 공간)
	// 축 : 로컬 혹은 월드를 기준으로한 자신의 x, y, z 총 6가지 방향

	// SPACEID가 로컬일 경우 자신의 고유의 축을 기준으로 이동하고, 월드일 경우 월드의 축을 기준으로 이동한다.

	if (LOCAL == _eSpace)
		m_vInfo[INFO_POS] += m_vInfo[_eDir] * fSpeed;
	else
		switch (_eDir)
		{
		case DIR_UP:
			m_vInfo[INFO_POS] += vec3.up * fSpeed;
			break;
		case DIR_RIGHT:
			m_vInfo[INFO_POS] += vec3.right * fSpeed;
			break;
		case DIR_FORWARD:
			m_vInfo[INFO_POS] += vec3.forward * fSpeed;
		// 임시 추가 
		case DIR_DOWN:
			m_vInfo[INFO_POS] += vec3.down * fSpeed;
			break;
		}

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Translate(const _vec3 & _vDir, const _float & fSpeed)
{
	// 현재 자신의 위치에서 매개변수로 받은 '임의의 방향'으로 이동한다.
	
	_vec3 vDir{};

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &_vDir) * fSpeed;

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Translate(const _float& fSpeed)
{
	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&m_vDir, &m_vDir) * fSpeed;

	memcpy(&m_matWorld.m[INFO_POS][0], &m_vInfo[INFO_POS], sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Rotate(const DIRID & _eDir, const _float& fSpeed, const SPACEID _eSpace)
{
	// 현재 자신의 회전 상태에서 매개변수로 받은 축을 기준으로 매개변수로 받은 값 만큼 회전한다.(eDir : 축, _eSpace 스페이스 공간)
	// 축 : 로컬 혹은 월드를 기준으로한 자신의 x, y, z 총 6가지 방향

	// SPACEID가 로컬일 경우 자신의 고유의 축을 기준으로 이동하고, 월드일 경우 월드의 축을 기준으로 이동한다.

	
	*(((_float*)&m_vAngle) + _eDir) += fSpeed;	//회전 정보 세이브 (이 정보를 바탕으로 쿼터니언과 회전행렬을 다시 구한다)
																				

	if (LOCAL == _eSpace)
		D3DXQuaternionRotationYawPitchRoll(&m_quatQ, m_vAngle.y, m_vAngle.x, m_vAngle.z);	
		// DXQuaternionRotationAxis(&quat, &vAxis, *(((_float*)&m_vAngle) + _eDir));
		// 위 함수를 사용하고자 한다면, x, y, z에 대한 쿼터니언을 모두 구한뒤 모두 곱해주어야 한다.
	else
	{
		//// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=spinx85&logNo=140120555548
		//_quat	qX, qY, qZ;

		//D3DXQuaternionRotationAxis(&qX	, &vec3.right	, m_vAngle.x);
		//D3DXQuaternionRotationAxis(&qY	, &vec3.up		, m_vAngle.y);
		//D3DXQuaternionRotationAxis(&qZ	, &vec3.forward	, m_vAngle.z);

		//m_quatQ = qY * qX * qZ;
		//
		//D3DXQuaternionNormalize(&m_quatQ, &m_quatQ);
	}

	Cal_WorldMat();				
}




void CTransform::Set_Pos(const _vec3 & _vPos)
{
	// 월드 기준 _vPos로 포지션을 세팅한다.

	memcpy(&m_matWorld.m[3][0]	, _vPos, sizeof(_vec3));
	memcpy(&m_vInfo[INFO_POS]	, _vPos, sizeof(_vec3));

	Cal_WorldMat();
}

void CTransform::Set_Rot(const _vec3& _vRot, const SPACEID _eSpace)
{
	if (LOCAL == _eSpace)
		D3DXQuaternionRotationYawPitchRoll(&m_quatQ, _vRot.y, _vRot.x, _vRot.z);

	Cal_WorldMat();

}

void CTransform::Set_Scale(const _vec3& _vPos)
{ 
	memcpy(&m_vScale, &_vPos, sizeof(_vec3));  Cal_WorldMat();  
	Cal_WorldMat();
}

void CTransform::Set_PosY(const _float& _fHeight)
{
	m_matWorld.m[3][1] = _fHeight;
	m_vInfo[INFO_POS].y = _fHeight;

	Cal_WorldMat();
}

void CTransform::Reverse()
{
	m_vScale.x *= -1;
	Cal_WorldMat();
}


_vec3& CTransform::Lerp(const _vec3& vStart, const _vec3& vTarget, const _float& fLerpTime, const _float& fTimeDelta, const LERP_MODE& _eMode)
{
	if (m_fCurTime == fLerpTime)
	{
		m_bStart = false;
		m_fCurTime = 0;
		return _vec3{ -99, -99, -99 };
	}

	if (!m_bStart)
	{
		m_bStart = true;
		m_vStart = vStart;
		m_eLerpMod = _eMode;
	}

	m_fCurTime += fTimeDelta;
	if (m_fCurTime >= fLerpTime)
	{
		m_fCurTime = fLerpTime;
	}

	_vec3 vOut;
	_float t = m_fCurTime / fLerpTime;

	switch (m_eLerpMod)
	{
	case Engine::LERP_MODE::DEFAULT:
	{
	}
	break;
	case Engine::LERP_MODE::EASE_OUT:
	{
		t = sinf(t * D3DX_PI * 0.5f);
	}
	break;
	case Engine::LERP_MODE::EASE_IN:
	{
		t = 1.f - cosf(t * D3DX_PI * 0.5f);
	}
	break;
	case Engine::LERP_MODE::EXPONENTIAL:
	{
		t = t * t;
	}
	break;
	case Engine::LERP_MODE::SMOOTHSTEP:
	{
		t = t * t * (3.f - 2.f * t);
	}
	break;
	case Engine::LERP_MODE::SMOOTHERSTEP:
	{
		t = t * t * t * (t * (6.f * t - 15.f) + 10.f);
	}
	break;
	}

	D3DXVec3Lerp(&vOut, &m_vStart, &vTarget, t);


	return vOut;
}

_vec3& CTransform::Normal_Lerp(const _vec3& vStart, const _vec3& vTarget, const _float& fLerpTime, const _float& fTimeDelta)
{
	if (m_fCurTime == fLerpTime)
	{
		m_bStart = false;
		m_fCurTime = 0;
		return _vec3{ -99, -99, -99 };
	}

	if (!m_bStart)
	{
		m_bStart = true;
		m_vStart = vTarget;
	}

	m_fCurTime += fTimeDelta;
	if (m_fCurTime >= fLerpTime)
	{
		m_fCurTime = fLerpTime;
	}

	_vec3 vOut;
	_float fTime = m_fCurTime / fLerpTime;
	D3DXVec3Lerp(&vOut, &vStart, &m_vStart, fTime);

	return vOut;
}

void CTransform::Reset_Lerp()
{
	m_bStart = false;
	m_fCurTime = 0;
}

void CTransform::Cal_WorldMat()
{
	// 저장된 정보를 바탕으로 최종 월드행렬을 계산한다.

	_matrix matS, matR;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	
	D3DXMatrixRotationQuaternion(&matR, &m_quatQ);

	matS *= matR;

	if (nullptr != m_pOwnerObject && OBJ_TYPE::CAMERA != m_pOwnerObject->Get_Type() && OBJ_TYPE::TERRAIN != m_pOwnerObject->Get_Type())
	{
		_matrix matBill;
		matS *= CCameraMgr::GetInstance()->Get_Billboard_X();// *CCameraMgr::GetInstance()->Get_Billboard_Y();

		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_matWorld.m[i], &matS.m[i], sizeof(_vec3));

		// 빌보드는 렌더를 위한 회전이므로 인포에는 영향을 미치면 안된다. -> 월드 행렬을 인포에 복사하면 안됨
	}
	else
	{
		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_matWorld.m[i], &matS.m[i], sizeof(_vec3));

		for (_int i = 0; i < INFO_POS; ++i)
			memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));
	}
	
}

HRESULT CTransform::Ready_Transform()
{
	// 모든 트랜스폼 정보를 초기화한다.

	ZeroMemory(&m_quatQ, sizeof(_quat));
	ZeroMemory(&m_vAngle, sizeof(_vec3));
	memcpy(&m_vScale, &vec3.one, sizeof(_vec3));
	D3DXMatrixIdentity(&m_matWorld);
	for (_int i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	m_vDir = vec3.right;

	m_bStart = false;
	m_fCurTime = 0.f;

	return S_OK;
}

_int CTransform::Update_Component(const _float& fTimeDelta)
{
	Cal_WorldMat();
	return 0;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTransform*		pInstance = new CTransform(pGraphicDev);

	if (FAILED(pInstance->Ready_Transform()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTransform::Clone(CGameObject* _pOwnerObject)
{
	return new CTransform(*this, _pOwnerObject);
}

void CTransform::Free()
{
	CComponent::Free();
}
