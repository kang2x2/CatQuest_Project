#pragma once
#include "GameObject.h"
#include "Dungeon.h"

BEGIN(Engine)

class CCollider;

END

class CDungeon_Temple : public CDungeon
{
protected:
	explicit CDungeon_Temple(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDungeon_Temple(const CDungeon& rhs);
	virtual ~CDungeon_Temple();

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
	static				CDungeon_Temple* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

