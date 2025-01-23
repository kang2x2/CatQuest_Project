#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CGreenBullet : public CBasicProjectile    // 정해진 방향으로 이동 하는 Bullet
{
protected:
	explicit CGreenBullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);
	explicit CGreenBullet(const CProjectile& rhs);
	virtual ~CGreenBullet();

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

	static					CGreenBullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, _vec3 _vDir, CGameObject* pOwner);

private:

	LERP_FLOAT_INFO      m_tAlpha;

	_bool				m_bInit;
	_bool				m_bEnd;

	_bool				m_Check;
protected:
	virtual void		Free() override;


};

