#pragma once
#include "Item_Object.h"

BEGIN(Engine)

class CCollider;

END

class CKey : public CItem_Object
{
protected:
	explicit CKey(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CKey(const CItem& rhs);
	virtual ~CKey();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT					Add_Component();


public:
	static				CKey* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

