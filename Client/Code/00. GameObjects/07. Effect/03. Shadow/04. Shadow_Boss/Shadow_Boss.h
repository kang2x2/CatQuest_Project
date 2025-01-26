#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CShadow_Boss : public CEffect
{
	explicit CShadow_Boss(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CShadow_Boss(const CShadow_Boss& rhs);
	virtual ~CShadow_Boss();

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

	LERP_FLOAT_INFO m_tIntorLerpX;
	LERP_FLOAT_INFO m_tIntorLerpZ;

	LERP_FLOAT_INFO m_tFullUpLerpX;
	LERP_FLOAT_INFO m_tFullUpLerpZ;

	LERP_FLOAT_INFO m_tFullDownLerpX;
	LERP_FLOAT_INFO m_tFullDownLerpZ;

	_bool			m_bUp;
	_bool			m_bDown;

public:
	static CShadow_Boss* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);

private:
	virtual void				Free() override;
};

