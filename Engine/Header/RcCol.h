#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcCol :	public CVIBuffer
{
public:
	explicit CRcCol();
	explicit CRcCol(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRcCol(const CRcCol& rhs, CGameObject* _pOwnerObject);
	virtual ~CRcCol();

public:
	virtual HRESULT			Ready_Buffer(void);
	virtual void			Render_Buffer(void);

public:
	static CRcCol*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(CGameObject* _pOwnerObject);

private:
	virtual	void	Free(void);
};

END