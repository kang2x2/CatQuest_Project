#pragma once

#include "GameObject.h"
#include "Monster.h"
class CEffect;

BEGIN(Engine)

class CCollider;

END

class CCuteMonster : public CMonster
{
protected:
	explicit CCuteMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCuteMonster(const CMonster& rhs);
	virtual ~CCuteMonster();

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
	void				Move(const _float& fTimeDelta);

protected:
	MOVEINFO			m_tMoveInfo;
	STATINFO			m_tStatInfo;

	CEffect*			m_pEffect;

public:
	static				CCuteMonster* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

