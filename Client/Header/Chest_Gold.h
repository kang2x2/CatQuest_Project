#pragma once
#include "GameObject.h"
#include "Chest.h"

BEGIN(Engine)

class CCollider;

END

class CChest_Gold : public CChest
{
protected:
	explicit CChest_Gold(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CChest_Gold(const CChest& rhs);
	virtual ~CChest_Gold();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component();

public:
	static				CChest_Gold* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

