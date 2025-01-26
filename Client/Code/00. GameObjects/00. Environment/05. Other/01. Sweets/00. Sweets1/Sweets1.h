#pragma once
#include "GameObject.h"
#include "Sweets.h"

BEGIN(Engine)

class CCollider;

END

class CSweets1 : public CSweets
{
protected:
	explicit CSweets1(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSweets1(const CSweets& rhs);
	virtual ~CSweets1();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	HRESULT				Add_Component();

public:
	static				CSweets1* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

