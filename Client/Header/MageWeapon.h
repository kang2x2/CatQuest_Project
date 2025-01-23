#pragma once
#include "Item_Weapon.h"

BEGIN(Engine)


END

class CMageWeapon : public CItem_Weapon
{
protected:
	explicit CMageWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMageWeapon(const CItem& rhs);
	virtual ~CMageWeapon();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

public:
	static				CMageWeapon* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;



};

