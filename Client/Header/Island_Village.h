#pragma once

#include "Island.h"

class CIsland_Village : public CIsland
{
public:
	explicit CIsland_Village(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CIsland_Village(const CIsland_Village& rhs);
	virtual ~CIsland_Village();

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
	static CIsland_Village* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void		Free() override;

};