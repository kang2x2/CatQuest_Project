#pragma once
#include "BasicProjectile.h"

BEGIN(Engine)

class CTexture;
class CCollider;

END

class CPile_Bullet : public CBasicProjectile    // 타겟을 따라다니며 이동 하는 Bullet
{
protected:
	explicit CPile_Bullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);
	explicit CPile_Bullet(const CProjectile& rhs);
	virtual ~CPile_Bullet();

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

	static					CPile_Bullet* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 _vPos, CGameObject* pTarget, CGameObject* pOwner);

private:
	CVIBuffer*				m_pCrossBuffer;

	_bool					m_bDelete;

	_float					m_fDamage;
	_float					m_fLength;

	LERP_FLOAT_INFO			m_tAlpha;
	LERP_FLOAT_INFO			m_tSpeed;

	_uint					m_iAlpha;


protected:
	virtual void		Free() override;


};
