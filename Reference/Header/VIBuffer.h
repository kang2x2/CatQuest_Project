#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer : public CComponent
{
protected:
	explicit CVIBuffer();
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphicDev, const COMPONENT_TYPE& _eType);
	explicit CVIBuffer(const CVIBuffer& rhs, CGameObject* _pOwnerObject);
	virtual ~CVIBuffer();

public:
	virtual HRESULT				Ready_Buffer();
	virtual void				Render_Buffer();

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

	// VB
	_ulong						m_dwVtxCnt;
	_ulong						m_dwVtxSize;
	_ulong						m_dwTriCnt;
	_ulong						m_dwFVF;

	// IB
	_ulong						m_dwIdxSize;
	D3DFORMAT					m_IdxFmt;

public:
	virtual	void				Free();
};

END