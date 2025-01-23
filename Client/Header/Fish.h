#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CFish : public CMonster
{
protected:

	explicit CFish(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFish(const CMonster& rhs);
	virtual ~CFish();


public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;


public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj) override;
	virtual void		OnCollision_Stay(CGameObject* _pColObj) override;
	virtual void		OnCollision_Exit(CGameObject* _pColObj) override;

private:
	HRESULT				Add_Component();



public:
	static				CFish* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;




};

