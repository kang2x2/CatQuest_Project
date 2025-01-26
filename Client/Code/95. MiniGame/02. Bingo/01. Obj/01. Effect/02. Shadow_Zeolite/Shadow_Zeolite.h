#pragma once
#include "Effect.h"

class CZeolite;

BEGIN(Engine)

class CTexture;

END

class CShadow_Zeolite : public CEffect
{
	explicit CShadow_Zeolite(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CShadow_Zeolite(const CShadow_Zeolite& rhs);
	virtual ~CShadow_Zeolite();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture* m_pTextureCom;
	_float	  m_fPosZ;

	_float			m_fAlpha;
	LERP_FLOAT_INFO m_tAlphaLerp;

public:
	static CShadow_Zeolite* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

