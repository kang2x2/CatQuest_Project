#include "..\..\Header\TerrainRcTex.h"

CTerrainRcTex::CTerrainRcTex()
{
}

CTerrainRcTex::CTerrainRcTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev, COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX)
{
}

CTerrainRcTex::CTerrainRcTex(const CTerrainRcTex& rhs, CGameObject* _pOwnerObject)
	: CVIBuffer(rhs, _pOwnerObject)
{
}

CTerrainRcTex::~CTerrainRcTex()
{
}

HRESULT CTerrainRcTex::Ready_Buffer()
{
	m_dwFVF = FVF_TEX;
	m_dwTriCnt = 2;
	m_dwVtxCnt = 4;
	m_dwVtxSize = sizeof(VTXTEX);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 0.f, 1.f };
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPosition = { 1.f, 0.f, 1.f };
	pVertex[1].vTexUV = { 1.f, 0.f };

	pVertex[2].vPosition = { 1.f, 0.f, -1.f };
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPosition = { -1.f, 0.f, -1.f };
	pVertex[3].vTexUV = { 0.f, 1.f };

	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// ������ ��
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	// ���� �Ʒ�
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();


	return S_OK;
}

void CTerrainRcTex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CTerrainRcTex* CTerrainRcTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainRcTex* pInstance = new CTerrainRcTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		MSG_BOX("TerrainRcTex Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent* CTerrainRcTex::Clone(CGameObject* _pOwnerObject)
{
	return new CTerrainRcTex(*this, _pOwnerObject);
}

void CTerrainRcTex::Free()
{
	CVIBuffer::Free();
}
