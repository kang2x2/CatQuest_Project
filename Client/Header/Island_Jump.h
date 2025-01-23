#pragma once

#include "Island.h"

class CIsland_Jump : public CIsland
{
public:
	explicit CIsland_Jump(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIsland_Jump(const CIsland_Jump& rhs);
	virtual ~CIsland_Jump();

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
	static CIsland_Jump* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void		Free() override;

};