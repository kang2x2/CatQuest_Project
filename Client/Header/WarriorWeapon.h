#pragma once
#include "Item_Weapon.h"

BEGIN(Engine)


END

class CWarriorWeapon : public CItem_Weapon
{
protected:
	explicit CWarriorWeapon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWarriorWeapon(const CItem& rhs);
	virtual ~CWarriorWeapon();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();



public:
	static				CWarriorWeapon* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

