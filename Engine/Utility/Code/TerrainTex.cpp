#include "..\..\Header\TerrainTex.h"

CTerrainTex::CTerrainTex()
{
}

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev, COMPONENT_TYPE::BUFFER_TERRAIN_TEX)
{
}

CTerrainTex::CTerrainTex(const CTerrainTex & rhs, CGameObject* _pOwnerObject)
	: CVIBuffer(rhs, _pOwnerObject)
	, m_hFile(rhs.m_hFile)
	, m_fH(rhs.m_fH)
	, m_iH(rhs.m_iH)
	, m_pPos(rhs.m_pPos)
{
}


CTerrainTex::~CTerrainTex()
{
}

HRESULT CTerrainTex::Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	/*
	
		���̸��� ����ϱ� ���ؼ��� ������ ���� �������� ���̸� bmp ������ �ȼ� ������ ���ų� ���ƾ� �Ѵ�.

	*/

	m_dwFVF = FVF_TEX;
	m_dwTriCnt = (dwCntX - 1) * (dwCntZ - 1) * 2;
	m_dwVtxCnt = dwCntX * dwCntZ;
	m_dwVtxSize = sizeof(VTXTEX);

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	//m_hFile = CreateFile(L"../Bin/Resource/Texture/Terrain/Height1.bmp", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	//_ulong	dwByte = 0;

	//ReadFile(m_hFile, &m_fH, sizeof(BITMAPFILEHEADER), &dwByte, NULL); 
	//ReadFile(m_hFile, &m_iH, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	/*
	
		��Ʈ���� �������, ���� ���, �ȼ� ���� �� 3���� ���� ������ ����ȴ�.

		���� ����� �ü������ �����ϱ� ���� �����͸� ���� �ִ�.

		���� ����� ���� �̹��� ������ ���� ���� ���̵� ������ ���� �ִ�. -> ����ü ���� ����

		���������� �ȼ����� ����Ǿ� �ְ� ���̸ʿ��� ���Ǵ� ���̴� (r, g, b�� b ���� ����Ѵ�). -> 0x000000ff ��Ʈ����
	
	*/

	//_ulong*		pPixel = new _ulong[m_iH.biHeight * m_iH.biWidth];

	//ReadFile(m_hFile, pPixel, sizeof(_ulong) * m_iH.biHeight * m_iH.biWidth, &dwByte, NULL);

	//CloseHandle(m_hFile);

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	m_pPos = new _vec3[m_dwVtxCnt];
	VTXTEX*		pVertex = nullptr;
	_plane		tPlane;

	_ulong		dwIndex = 0;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (_ulong i = 0; i < dwCntZ; ++i)
	{
		for (_ulong j = 0; j < dwCntX; ++j)
		{
			dwIndex = i * dwCntX + j;

			pVertex[dwIndex].vPosition =
			{
				_float(j * dwVtxItv),
				0.f,
				//_float(pPixel[dwIndex] & 0x000000ff) / 30.f,
				/*
					*	rgb�� b�� ����� �뵵�� ��Ʈ ���� 0x000000ff �׸��� 30.f�� ���� ���̱� ���� ��� ��
				*/
				_float(i * dwVtxItv)
			};

			// pVertex[dwIndex].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

			m_pPos[dwIndex] = pVertex[dwIndex].vPosition;

			//m_vVertex[dwIndex] = pVertex[dwIndex].vPosition; // >> : �߰�

			pVertex[dwIndex].vTexUV = 
			{
				_float(j) / (dwCntX - 1) * 10.f, 
				_float(i) / (dwCntZ - 1) * 10.f 
				/*
				
					*	������ ��
			
					*	�ؽ�ó UV ��ǥ�� ���� 0 ~ 1 ������ �������� 1�� �Ѿ�� �ٽ� 0���� �����ϴ� ���� �����ϴ� (����Ʈ �ɼ�)
					*	�� �⺻ 1 * 1 �̶�� �� ��ǥ�� 20�� ���ϸ� 20 * 20���� ����� �ȴ�.
					*	���� �ܰ迡�� �� ���õǹǷ� ���귮�� ���̴� ����
			
				*/
			};
		}
	}
	m_pVB->Unlock();

	//Safe_Delete_Array(pPixel);

	_ulong		dwTriCnt = 0;

	INDEX32*			pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_ulong i = 0; i < dwCntZ - 1; ++i)
	{
		for (_ulong j = 0; j < dwCntX - 1; ++j)
		{
			dwIndex = i * dwCntX + j;

			// ������ ��
			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;
			dwTriCnt++;

			// ���� �Ʒ�
			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;
			dwTriCnt++;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

void CTerrainTex::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CTerrainTex * CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	const _ulong& dwCntX,
	const _ulong& dwCntZ,
	const _ulong& dwVtxItv)
{
	CTerrainTex *	pInstance = new CTerrainTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(dwCntX, dwCntZ, dwVtxItv)))
	{
		Safe_Release(pInstance);
		MSG_BOX("TerrainTex Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CTerrainTex::Clone(CGameObject* _pOwnerObject)
{
	return new CTerrainTex(*this, _pOwnerObject);
}

void CTerrainTex::Free()
{
	CVIBuffer::Free();
	if (m_bClone == false) {
		if (nullptr != m_pPos)
		{
			delete[] m_pPos;
			m_pPos = nullptr;
		}
	}

}
