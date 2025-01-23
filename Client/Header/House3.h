#pragma once
#include "GameObject.h"
#include "House.h"

BEGIN(Engine)

class CCollider;

END

class CHouse3 : public CHouse
{
protected:
	explicit CHouse3(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CHouse3(const CHouse& rhs);
	virtual ~CHouse3();

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
	static				CHouse3* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

