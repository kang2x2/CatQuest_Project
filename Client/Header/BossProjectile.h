#pragma once
#include "Projectile.h"
class CBossProjectile : public CProjectile
{
protected:
	explicit CBossProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CBossProjectile(const CProjectile& rhs);
	virtual ~CBossProjectile();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT					Add_Component();


protected:

	CTexture* m_pTextureCom;
	CAIComponent* m_pAICom;

	LERP_FLOAT_INFO	m_tLerp;
	LERP_VEC3_INFO	m_tvecLerp;

protected:
	virtual void		Free() override;




};

