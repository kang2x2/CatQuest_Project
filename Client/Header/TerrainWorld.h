#pragma once

#include "GameObject.h"
#include "Terrain.h"

BEGIN(Engine)

class CRcCol;
class CTerrainRcTex;

END

class CTerrainWorld : public CTerrain
{
protected:
	explicit CTerrainWorld(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainWorld(const CTerrain& rhs);
	virtual ~CTerrainWorld();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

public:
	static CTerrainWorld* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};