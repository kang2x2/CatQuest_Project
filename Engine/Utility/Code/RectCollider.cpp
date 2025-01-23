#include "..\..\Header\RectCollider.h"

#include "Transform.h"

CRectCollider::CRectCollider()
{
}

CRectCollider::CRectCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_RECT)
{
	ZeroMemory(&m_vSize, sizeof(_vec3));
	ZeroMemory(&m_vOverlapRect, sizeof(_vec3));

}

CRectCollider::CRectCollider(const CRectCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	, m_vSize(rhs.m_vSize)
	, m_vOverlapRect(rhs.m_vOverlapRect)
{
	NULL_CHECK(m_pOwnerObject);
	NULL_CHECK(m_pOwnerObject->Get_Transform());

	m_vSize = m_pOwnerObject->Get_Transform()->Get_Scale();

	D3DXCreateBox(m_pGraphicDev, m_vSize.x, m_vSize.y, 0.f, &m_pMesh, NULL);
	NULL_CHECK_MSG(m_pMesh, L"Failed Create Rect Mesh");
}

CRectCollider::~CRectCollider()
{
}

HRESULT CRectCollider::Ready_Collider()
{

	return S_OK;
}

CRectCollider* CRectCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRectCollider* pInstance = new CRectCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Rect Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CRectCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CRectCollider(*this, _pOwnerObject);
}

void CRectCollider::Free()
{
	CCollider::Free();
}

void CRectCollider::Render_Collider()
{

	if (!m_bActive) return;

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (0 < m_iCol)
		m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.red));
	else
	{
		if(OBJ_TYPE::ENVIRONMENT == m_pOwnerObject->Get_Type())
			m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
		else
			m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.green));
	}

	m_pMesh->DrawSubset(0);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void CRectCollider::Set_Size(const _vec3& _vSize)
{
	m_vSize = _vSize;

	if (m_bClone)
	{
		if (nullptr != m_pMesh)
			Safe_Release(m_pMesh);
	}

	D3DXCreateBox(m_pGraphicDev, m_vSize.x, m_vSize.y, 0.f, &m_pMesh, NULL);

	NULL_CHECK_MSG(m_pMesh, L"Failed Create Rect Mesh");
}