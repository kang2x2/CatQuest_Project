#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CPollen : public CEffect
{
	explicit CPollen(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos);
	explicit CPollen(const CPollen& rhs);
	virtual ~CPollen();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture* m_pTextureCom;
	_float    m_fSpeed;
	_vec3     m_InitPos;

	_float	  m_fDirZ;

	_vec3	  m_vWindVelo;
	_float    m_fdriftAngle;

	_float	  m_fAccTime;

public:
	static CPollen* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos);

private:
	virtual void				Free() override;
};

