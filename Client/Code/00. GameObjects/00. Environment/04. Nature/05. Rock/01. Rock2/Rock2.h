#pragma once
#include "GameObject.h"
#include "Rock.h"

BEGIN(Engine)

class CCollider;

END

class CRock2 : public CRock
{
protected:
	explicit CRock2(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRock2(const CRock& rhs);
	virtual ~CRock2();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

private:
	HRESULT				Add_Component();

public:
	static				CRock2* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

