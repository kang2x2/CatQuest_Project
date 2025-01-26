#pragma once
#include "GameObject.h"
#include "Sweets.h"

BEGIN(Engine)

class CCollider;

END

class CSweets2 : public CSweets
{
protected:
	explicit CSweets2(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSweets2(const CSweets& rhs);
	virtual ~CSweets2();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	HRESULT				Add_Component();

public:
	static				CSweets2* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

