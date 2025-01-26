#pragma once
#include "GameObject.h"
#include "Chest.h"

BEGIN(Engine)

class CCollider;

END

class CChest_Regular : public CChest
{
protected:
	explicit CChest_Regular(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CChest_Regular(const CChest& rhs);
	virtual ~CChest_Regular();

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
	static				CChest_Regular* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

