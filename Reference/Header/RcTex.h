#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex :	public CVIBuffer
{
public:
	explicit CRcTex();
	explicit CRcTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRcTex(const CRcTex& rhs, CGameObject* _pOwnerObject);
	virtual ~CRcTex();

public:
	virtual HRESULT			Ready_Buffer();
	virtual void			Render_Buffer();

public:
	static CRcTex*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(CGameObject* _pOwnerObject);

private:
	virtual	void	Free();
};

END