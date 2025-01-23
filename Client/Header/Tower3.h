#pragma once
#include "GameObject.h"
#include "Tower.h"

BEGIN(Engine)

class CCollider;

END

class CTower3 : public CTower
{
protected:
	explicit CTower3(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTower3(const CTower& rhs);
	virtual ~CTower3();

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
	static				CTower3* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

