#include "..\..\Header\CircleCollider.h"

#include "Transform.h"

CCircleCollider::CCircleCollider()
{
}

CCircleCollider::CCircleCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_CIRCLE)
	, m_fRadius(0.f)
{

}

CCircleCollider::CCircleCollider(const CCircleCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	, m_fRadius(rhs.m_fRadius)
{
	Ready_Collider();
}

CCircleCollider::~CCircleCollider()
{
}

HRESULT CCircleCollider::Ready_Collider()
{
	return S_OK;
}

CCircleCollider* CCircleCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCircleCollider* pInstance = new CCircleCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Circle Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CCircleCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CCircleCollider(*this, _pOwnerObject);
}

void CCircleCollider::Free()
{
	CCollider::Free();
}

void CCircleCollider::Render_Collider()
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (0 < m_iCol)
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.red));
	else
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
