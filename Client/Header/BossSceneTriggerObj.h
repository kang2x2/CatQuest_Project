#pragma once

#include "GameObject.h"

class CRangeObj;

class CBossSceneTriggerObj : public CGameObject
{
public:
	explicit CBossSceneTriggerObj(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossSceneTriggerObj(const CBossSceneTriggerObj& rhs);
	virtual ~CBossSceneTriggerObj();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component(void);
	HRESULT				Add_RangeObj(void);

private:
	CRangeObj*			m_pRangeObj;
	_bool				m_bInPlayer;

public:
	static CBossSceneTriggerObj* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};