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
	
		높이맵을 사용하기 위해서는 지형의 정점 개수보다 높이맵 bmp 파일의 픽셀 개수가 같거나 많아야 한다.

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
	
		비트맵은 파일헤더, 인포 헤더, 픽셀 정보 총 3가지 계층 구조로 저장된다.

		파일 헤더는 운영체제에게 제공하기 위한 데이터를 갖고 있다.

		인포 헤더는 실제 이미지 파일의 가로 세로 길이등 정보를 갖고 있다. -> 구조체 정의 ㄱㄱ

		마지막으로 픽셀값이 저장되어 있고 높이맵에서 사용되는 값이다 (r, g, b중 b 값만 사용한다). -> 0x000000ff 비트연산
	
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
					*	rgb중 b만 사용할 용도로 비트 연산 0x000000ff 그리고 30.f는 편차 줄이기 위한 상수 값
				*/
				_float(i * dwVtxItv)
			};

			// pVertex[dwIndex].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

			m_pPos[dwIndex] = pVertex[dwIndex].vPosition;

			//m_vVertex[dwIndex] = pVertex[dwIndex].vPosition; // >> : 추가

			pVertex[dwIndex].vTexUV = 
			{
				_float(j) / (dwCntX - 1) * 10.f, 
				_float(i) / (dwCntZ - 1) * 10.f 
				/*
				
					*	디테일 맵
			
					*	텍스처 UV 좌표는 원래 0 ~ 1 사이의 값이지만 1을 넘어가면 다시 0부터 시작하는 것이 가능하다 (디폴트 옵션)
					*	즉 기본 1 * 1 이라면 각 좌표에 20씩 곱하면 20 * 20으로 출력이 된다.
					*	레디 단계에서 다 세팅되므로 연산량의 차이는 없다
			
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

			// 오른쪽 위
			pIndex[dwTriCnt]._0 = dwIndex + dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;
			dwTriCnt++;

			// 왼쪽 아래
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
