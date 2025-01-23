#pragma once
#include "GameObject.h"
#include "Bush.h"

BEGIN(Engine)

class CCollider;

END

class CLargeIceBush : public CBush
{
protected:
	explicit CLargeIceBush(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLargeIceBush(const CBush& rhs);
	virtual ~CLargeIceBush();

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
	static				CLargeIceBush* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

