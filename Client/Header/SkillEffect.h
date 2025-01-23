#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CSkillEffect :
	public CEffect
{
protected:
	explicit CSkillEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID);
	explicit CSkillEffect(const CEffect& rhs);
	virtual ~CSkillEffect();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one);
	const _bool&			Is_End() const { return m_bEnd; }

private:
	HRESULT					Add_Component();

protected:
	CTexture*				m_pTextureCom;
	CAnimation*				m_pAnimation;
	_bool					m_bEnd;

protected:
	virtual void			Free() override;
};

