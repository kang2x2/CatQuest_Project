#pragma once
#include "Item_Weapon.h"

BEGIN(Engine)


END

class CNinjaWeapon : public CItem_Weapon
{
protected:
	explicit CNinjaWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNinjaWeapon(const CItem& rhs);
	virtual ~CNinjaWeapon();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();



public:
	static				CNinjaWeapon* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;



};

