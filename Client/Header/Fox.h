#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CSkill_Monster_Fire;

class CFox : public CMonster
{

protected:
		
	explicit CFox(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFox(const CMonster& rhs);
	virtual ~CFox();


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
	static				CFox* Create(LPDIRECT3DDEVICE9 pGraphicDev);


private:

	_float				m_fAttackTime;

protected:
	virtual void		Free() override;


};

