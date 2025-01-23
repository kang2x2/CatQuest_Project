#include "..\..\Header\LineCollider.h"

#include "Transform.h"
#include "CameraMgr.h"
#include "CollisionMgr.h"

CLineCollider::CLineCollider()
{

}

CLineCollider::CLineCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCollider(pGraphicDev, COMPONENT_TYPE::COL_LINE)
{
	ZeroMemory(&m_vPointList, sizeof(_vec3) * 2);
	ZeroMemory(&m_vOverlapLine, sizeof(_vec3));
}

CLineCollider::CLineCollider(const CLineCollider& rhs, CGameObject* _pOwnerObject)
	: CCollider(rhs, _pOwnerObject)
	, m_vOverlapLine(rhs.m_vOverlapLine)

{
	Ready_Collider();
}

CLineCollider::~CLineCollider()
{

}

HRESULT CLineCollider::Ready_Collider()
{

	return S_OK;
}

CLineCollider* CLineCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLineCollider* pInstance = new CLineCollider(pGraphicDev);

	if (FAILED(pInstance->Ready_Collider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Line Collider Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CLineCollider::Clone(CGameObject* _pOwnerObject)
{
	return new CLineCollider(*this, _pOwnerObject);
}

void CLineCollider::Free()
{
	CCollider::Free();
}

void CLineCollider::Render_Collider()
{
	// 0. 월드 매트릭스 설정 (뷰 행렬 * 투영 행렬)
	_matrix matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);

	matWorld = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView() *
		CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();

	// 1. 라인 생성
	ID3DXLine* ILine;
	if (FAILED(D3DXCreateLine(m_pGraphicDev, &ILine)))
	{
		MSG_BOX("Line Create Failed");
		return;
	}

	ILine->SetWidth(2.f);
	ILine->SetAntialias(TRUE);
	ILine->Begin();


	if(Is_Collision())
		ILine->DrawTransform(m_vPointList, 2, &matWorld, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
	else
		ILine->DrawTransform(m_vPointList, 2, &matWorld, D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	ILine->End();
	ILine->Release();
}
