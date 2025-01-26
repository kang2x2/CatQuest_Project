#pragma once

#include "GameObject.h"
#include "Terrain.h"

BEGIN(Engine)

class CRcCol;
class CTerrainRcTex;

END

class CTerrainTemple : public CTerrain
{
protected:
	explicit CTerrainTemple(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTemple(const CTerrain& rhs);
	virtual ~CTerrainTemple();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

public:
	static CTerrainTemple* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};