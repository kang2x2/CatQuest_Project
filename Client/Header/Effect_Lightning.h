#pragma once

#include "SkillEffect.h"

class CEffect_Lightning :
	public CSkillEffect
{
protected:
	explicit CEffect_Lightning(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_Lightning(const CEffect& rhs);
	virtual ~CEffect_Lightning();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CEffect_Lightning* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

