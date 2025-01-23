#pragma once
#include "SkillEffect.h"

BEGIN(Engine)

END

class CEffect_Heal :
	public CSkillEffect
{
protected:
	explicit CEffect_Heal(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_Heal(const CEffect& rhs);
	virtual ~CEffect_Heal();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	virtual void			Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one);

private:
	HRESULT					Add_Component();

private:
	CTexture*				m_pUITexutre[2];
	CTransform*			    m_pUITransform[2];

	_uint					m_iPawScale;
	_bool					m_bPawExpand;

public:
	static CEffect_Heal* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

protected:
	virtual void			Free() override;
};

