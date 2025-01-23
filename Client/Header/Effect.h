#pragma once

#include "GameObject.h"

BEGIN(Engine)

END

class CEffect :
	public CGameObject
{
protected:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID);
	explicit CEffect(const CEffect& rhs);
	virtual ~CEffect();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) {};

private:
	HRESULT					Add_Component();

protected:
	CGameObject*			m_pOwnerobject;
	_vec3					m_vOffSet;
	_vec3					m_vSize;
	_vec3					m_vRot;
	_int					m_iAlpha;

protected:
	virtual void			Free() override;
};

