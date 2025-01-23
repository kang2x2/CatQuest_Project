#pragma once
#include "Effect.h"

BEGIN(Engine)
class CTexture;
END

class CCircle_Stemp : public CEffect
{
	explicit CCircle_Stemp(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CCircle_Stemp(const CCircle_Stemp& rhs);
	virtual ~CCircle_Stemp();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
private:
	CTexture*   m_pTextureCom;
	CTransform* m_pTransformCom;

	_vec3		m_vPos;

	_matrix		matWorld;

	LERP_FLOAT_INFO m_tLerpSize;
	LERP_FLOAT_INFO	m_tLerpAlpha;

public:
	static CCircle_Stemp* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);

private:
	virtual void				Free() override;
};

