#pragma once
#include "Projectile.h"




class CBasicProjectile : public CProjectile
{

protected:
	explicit CBasicProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CBasicProjectile(const CProjectile& rhs);
	virtual ~CBasicProjectile();

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

	CTexture*				m_pTextureCom;
	CAIComponent*			m_pAICom;


protected:
	virtual void		Free() override;






};

