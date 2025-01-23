#pragma once
#include "GameObject.h"
#include "Terrain.h"

class CTerrain_World : public CTerrain
{
public:
	explicit CTerrain_World(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrain_World(const CTerrain& rhs);
	virtual ~CTerrain_World();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT					Add_Component();

public:
	static				CTerrain_World* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;
};

