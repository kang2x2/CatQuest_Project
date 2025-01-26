#pragma once
#include "GameObject.h"
#include "Grass.h"

BEGIN(Engine)

class CCollider;

END

class CGrass1 : public CGrass
{
protected:
	explicit CGrass1(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGrass1(const CGrass& rhs);
	virtual ~CGrass1();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	HRESULT				Add_Component();

public:
	static				CGrass1* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

