#pragma once
#include "GameObject.h"
#include "Dungeon.h"

BEGIN(Engine)

class CCollider;

END

class CDungeon_Grass : public CDungeon
{
protected:
	explicit CDungeon_Grass(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeon_Grass(const CDungeon& rhs);
	virtual ~CDungeon_Grass();

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
	static				CDungeon_Grass* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

