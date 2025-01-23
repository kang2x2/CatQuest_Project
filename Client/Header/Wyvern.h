#pragma once
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)

class CCubeCol;
class CCollider;

END

class CWyvern : public CMonster
{
protected:

	explicit CWyvern(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWyvern(const CMonster& rhs);
	virtual ~CWyvern();


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


private:

	_float					m_fAccTime;


public:
	static				CWyvern* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;




};

