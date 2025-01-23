#pragma once
#include "GameObject.h"
#include "Skull.h"

BEGIN(Engine)

class CCollider;

END

class CDragonSkull3 : public CSkull
{
protected:
	explicit CDragonSkull3(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonSkull3(const CSkull& rhs);
	virtual ~CDragonSkull3();

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
	static				CDragonSkull3* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

