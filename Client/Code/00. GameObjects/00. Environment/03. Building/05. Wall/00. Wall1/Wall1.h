#pragma once
#include "GameObject.h"
#include "Wall.h"

BEGIN(Engine)

class CCollider;

END

class CWall1 : public CWall
{
protected:
	explicit CWall1(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWall1(const CWall& rhs);
	virtual ~CWall1();

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
	static				CWall1* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

