#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
public:
	explicit CTerrainTex();
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTex(const CTerrainTex& rhs, CGameObject* _pOwnerObject);
	virtual ~CTerrainTex();

public:
	HRESULT						Ready_Buffer(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);
	void						Render_Buffer(void);

public:
	const _vec3* Get_VtxPos() const { return m_pPos; }

private:
	HANDLE						m_hFile;	// 파일 핸들
	BITMAPFILEHEADER			m_fH;		// 비트맵 중 헤더 파일 정보
	BITMAPINFOHEADER			m_iH;		// 비트맵 중 인포 파일 정보

	//_vec3						m_vVertex[VTXCNTX * VTXCNTZ ]; // height 보관배열 (행렬)
	_vec3*						m_pPos;
public:
	static CTerrainTex*			Create(LPDIRECT3DDEVICE9 pGraphicDev,
														const _ulong& dwCntX = VTXCNTX,
														const _ulong& dwCntZ = VTXCNTZ,
														const _ulong& dwVtxItv = VTXITV);

	virtual CComponent*			Clone(CGameObject* _pOwnerObject);

private:
	virtual	void				Free(void);
};

END