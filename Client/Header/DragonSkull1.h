#pragma once
#include "GameObject.h"
#include "Skull.h"

BEGIN(Engine)

class CCollider;

END

class CDragonSkull1 : public CSkull
{
protected:
	explicit CDragonSkull1(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDragonSkull1(const CSkull& rhs);
	virtual ~CDragonSkull1();

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
	static				CDragonSkull1* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

