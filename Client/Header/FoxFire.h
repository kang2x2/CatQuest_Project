#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CFoxFire : public CBasicProjectile    // ������ �������� �̵� �ϴ� Bullet
{
protected:
	explicit CFoxFire(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);
	explicit CFoxFire(const CProjectile& rhs);
	virtual ~CFoxFire();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;



public:

	virtual void			OnCollision_Enter(CGameObject* _pColObj);
	virtual void			OnCollision_Stay(CGameObject* _pColObj);
	virtual void			OnCollision_Exit(CGameObject* _pColObj);


	_float& Get_BallDamage() { return m_fDamage; }


private:
	HRESULT					Add_Component();

private:
	_float					m_fDamage;

public:

	static					CFoxFire* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);

private:

	LERP_FLOAT_INFO      m_tAlpha;

	_bool				m_bInit;
	_bool				m_bEnd;

	_bool				m_Check;
protected:
	virtual void		Free() override;


};

