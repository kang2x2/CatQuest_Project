#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CTexture;
class CAIComponent;

END

class CProjectile : public Engine:: CGameObject
{
protected:
	explicit CProjectile(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CProjectile(const CProjectile& rhs);
	virtual ~CProjectile();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);

	CGameObject*			Get_Owner() { return m_pOwner; }

private:
	HRESULT					Add_Component();


protected:
	CGameObject*		m_pOwner;

	CTexture*			m_pTextureCom;
	CAIComponent*		m_pAICom;

	_vec3				m_vDir;
	_vec3				m_vPos;
	_float				m_fSpeed;

	CGameObject*		m_pTarget;

	_float				m_fAccTime;

protected:
	virtual void		Free() override;


};

