#pragma once
#include "BasicProjectile.h"
class CRedStar_Bullet : public CBasicProjectile   //  Shooting Star Pattern Use
{
protected:
	explicit CRedStar_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);
	explicit CRedStar_Bullet(const CProjectile& rhs);
	virtual  ~CRedStar_Bullet();

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

public:

	static					CRedStar_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);

private:
	_vec3			m_vOriginPos;
	_bool			m_bChase;

	_bool			m_bInit;

	LERP_FLOAT_INFO m_tAlpha;
	LERP_VEC3_INFO  m_tPos;


	_bool				m_check1;
	_bool				m_check2;

	_bool				m_bBack;
	_bool				m_bTargetChase;



private:
	_float					m_fDamage;

protected:
	virtual void		Free() override;


};

