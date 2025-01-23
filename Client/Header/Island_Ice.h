#pragma once

#include "Island.h"

class CIsland_Ice : public CIsland
{
public:
	explicit CIsland_Ice(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIsland_Ice(const CIsland_Ice& rhs);
	virtual ~CIsland_Ice();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

private:
	HRESULT				Add_Component(void);

protected:
	virtual HRESULT		Add_RangeObj() override;

public:
	virtual void		Enter_Player() override;
	virtual void		Stay_Player() override;
	virtual void		Exit_Player() override;

protected:

public:
	static CIsland_Ice* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void		Free() override;

};