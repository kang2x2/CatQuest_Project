#pragma once

#include "GameObject.h"
#include "Terrain.h"

BEGIN(Engine)

class CRcCol;
class CTerrainTex;

END

class CTerrainTool : public CTerrain
{
protected:
	explicit CTerrainTool(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrainTool(const CTerrain& rhs);
	virtual ~CTerrainTool();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

public:
	static CTerrainTool* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};