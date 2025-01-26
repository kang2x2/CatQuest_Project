#pragma once
#include "GameObject.h"
#include "Npc.h"

BEGIN(Engine)

class CCollider;

END

class CNpc_Soldier : public CNpc
{
protected:
	explicit CNpc_Soldier(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CNpc_Soldier(const CNpc& rhs);
	virtual ~CNpc_Soldier();

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
	static				CNpc_Soldier* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

