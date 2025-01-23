#pragma once

#include "SkillEffect.h"

class CEffect_ThornAttack :
	public CSkillEffect
{
protected:
	explicit CEffect_ThornAttack(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_ThornAttack(const CEffect_ThornAttack& rhs);
	virtual ~CEffect_ThornAttack();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	virtual void			Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one);

private:
	HRESULT					Add_Component();

public:
	static CEffect_ThornAttack* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};