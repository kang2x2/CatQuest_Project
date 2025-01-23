#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CFirework_Bullet : public CBasicProjectile    // 타겟을 따라다니며 이동 하는 Bullet
{
protected:
	explicit CFirework_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);
	explicit CFirework_Bullet(const CProjectile& rhs);
	virtual ~CFirework_Bullet();

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

	static					CFirework_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);

private:
	_bool					m_bDelete;

	_float					m_fDamage;

	LERP_FLOAT_INFO			m_tScale;
	LERP_FLOAT_INFO			m_tPosY;

	_float					m_fScale;;

	_bool					m_bShrink;


protected:
	virtual void		Free() override;


};
