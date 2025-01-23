#pragma once

#include "SkillEffect.h"

class CEffect_Cast_Blue :
    public CSkillEffect
{
protected:
	explicit CEffect_Cast_Blue(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_Cast_Blue(const CEffect& rhs);
	virtual ~CEffect_Cast_Blue();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();

public:
	static CEffect_Cast_Blue* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

