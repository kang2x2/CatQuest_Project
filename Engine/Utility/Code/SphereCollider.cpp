#include "..\..\Header\SphereCollider.h"

#include "Transform.h"

CSphereCollider::CSphereCollider()
{
}

CSphereCollider::CSphereCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_SPHERE)
{
	//ZeroMemory(&m_vSize, sizeof(_vec3));
	//ZeroMemory(&m_vOverlapRect, sizeof(_vec3));

}

CSphereCollider::CSphereCollider(const CSphereCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	//, m_vSize(rhs.m_vSize)
	//, m_vOverlapRect(rhs.m_vOverlapRect)
{
	NULL_CHECK(m_pOwnerObject);
	NULL_CHECK(m_pOwnerObject->Get_Transform());

	m_fRadius = 8.f;

	D3DXCreateSphere(m_pGraphicDev, m_fRadius, m_fRadius * 1.5f, m_fRadius * 1.5f, &m_pMesh, NULL);
	NULL_CHECK_MSG(m_pMesh, L"Failed Create Sphere Mesh");
}

CSphereCollider::~CSphereCollider()
{
}

HRESULT CSphereCollider::Ready_Collider()
{
	return S_OK;
}

CSphereCollider* CSphereCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSphereCollider* pInstance = new CSphereCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Sphere Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CSphereCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CSphereCollider(*this, _pOwnerObject);
}

void CSphereCollider::Free()
{
	__super::Free();
}

void CSphereCollider::Render_Collider()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (0 < m_iCol)
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.red));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.yellow));

	m_pMesh->DrawSubset(0);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CSphereCollider::Set_Radius(const _float& _fRadius)
{
	m_fRadius = _fRadius;

	_float fMag = 2.f;

	if (30.f < _fRadius) fMag = 0.3f;

	if (m_bClone)
	{
		if (nullptr != m_pMesh)
			Safe_Release(m_pMesh);
	}

	// D3DXCreateSphere 함수의 매개변수 중 슬라이스와 스택의 값이 너무 크다면 메시가 생성되지 않는다.
	D3DXCreateSphere(m_pGraphicDev, m_fRadius, m_fRadius * fMag, m_fRadius * fMag, &m_pMesh, NULL);
	NULL_CHECK_MSG(m_pMesh, L"Failed Create Sphere Mesh");
}
