#pragma once

#include "SkillEffect.h"

class CEffect_SpellBrust_Purple :
	public CSkillEffect
{
protected:
	explicit CEffect_SpellBrust_Purple(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_SpellBrust_Purple(const CEffect& rhs);
	virtual ~CEffect_SpellBrust_Purple();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CEffect_SpellBrust_Purple* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

