#pragma once
#include "GameObject.h"
#include "Environment.h"

BEGIN(Engine)

class CCollider;

END

class CPresent : public CEnvironment
{
protected:
	explicit CPresent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPresent(const CPresent& rhs);
	virtual ~CPresent();

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
	static				CPresent* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

