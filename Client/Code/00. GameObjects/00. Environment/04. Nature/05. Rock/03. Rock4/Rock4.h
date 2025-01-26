#pragma once
#include "GameObject.h"
#include "Rock.h"

BEGIN(Engine)

class CCollider;

END

class CRock4 : public CRock
{
protected:
	explicit CRock4(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRock4(const CRock& rhs);
	virtual ~CRock4();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	HRESULT				Add_Component();

public:
	static				CRock4* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

