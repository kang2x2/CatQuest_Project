#pragma once
#include "Projectile.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CTrapFist : public CProjectile
{
	explicit CTrapFist(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTrapFist(const CProjectile& rhs);
	virtual ~CTrapFist();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

public:

	virtual void				OnCollision_Enter(CGameObject* _pColObj);


	_float& Get_BallDamage() { return m_fDamage; }


private:
	HRESULT						Add_Component();

private:
	CTexture*	    m_pTextureCom;
	LERP_FLOAT_INFO m_tDropLerp;
	LERP_FLOAT_INFO m_tDeAlphaLerp;
	_float			m_fTranslucent;

	_float			m_fDamage;
	_bool			m_bCreateDust;

	random_device	m_Random; // 난수 생성기
public:
	static CTrapFist* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void				Free() override;
};

