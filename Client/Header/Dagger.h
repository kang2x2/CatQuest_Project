#pragma once
#include "BasicProjectile.h"
class CDagger : public CBasicProjectile    // Converging Fire Pattern Use
{
protected:
	explicit CDagger(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);
	explicit CDagger(const CProjectile& rhs);
	virtual  ~CDagger();

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

	static					CDagger* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);

private:
	

	_bool				m_bNonTarget;

	_bool				m_bInit;


	_bool				m_bStop;
	_bool				m_bWide;
	_bool				m_bShoot;


	_bool				m_check1;
	_bool				m_check2;
	_bool				m_check3;

	LERP_FLOAT_INFO		m_tAlpha;
	LERP_VEC3_INFO      m_tPos;


private:
	_float					m_fDamage;

protected:
	virtual void		Free() override;


};

