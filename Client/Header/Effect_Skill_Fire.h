#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CEffect_Skill_Fire :
    public CEffect
{
protected:
	explicit CEffect_Skill_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CEffect_Skill_Fire(const CEffect_Skill_Fire& rhs);
	virtual ~CEffect_Skill_Fire();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture*					m_pTextureCom; // 장판 텍스처 -> 빌보드 적용 제외시켜야 한다. (Effect의 트랜스폼에서)

public:
	static CEffect_Skill_Fire*	Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};