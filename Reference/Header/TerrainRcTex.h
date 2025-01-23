#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainRcTex : public CVIBuffer
{
public:
	explicit CTerrainRcTex();
	explicit CTerrainRcTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainRcTex(const CTerrainRcTex& rhs, CGameObject* _pOwnerObject);
	virtual ~CTerrainRcTex();

public:
	virtual HRESULT			Ready_Buffer();
	virtual void			Render_Buffer();

public:
	static CTerrainRcTex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone(CGameObject* _pOwnerObject);

private:
	virtual	void	Free();
};

END

