#pragma once
#include "Projectile.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CTrapBigFist : public CProjectile
{
	explicit CTrapBigFist(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos);
	explicit CTrapBigFist(const CProjectile& rhs);
	virtual ~CTrapBigFist();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

public:
	virtual void				OnCollision_Enter(CGameObject* _pColObj);



	_float& Get_BallDamage() { return m_fDamage; }

	LERP_FLOAT_INFO Get_DropLerp() { return m_tDropLerp; }
	LERP_FLOAT_INFO Get_UpLerp() { return m_tDropLerp; }

	_bool			Get_IsDust() { return m_bCreateDust; }
	void			Set_IsDust(_bool isDust) { m_bCreateDust = isDust; }

private:
	HRESULT						Add_Component();

private:
	CTexture*		m_pTextureCom;
	LERP_FLOAT_INFO m_tDropLerp;
	LERP_FLOAT_INFO m_tUpLerp;

	_float			m_fDamage;
	_bool			m_bCreateDust;

	_vec3			m_vPos;
public:
	static CTrapBigFist* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos);

private:
	virtual void				Free() override;
};

