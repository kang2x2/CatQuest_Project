#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CCloud2 : public CEffect
{
	// 구름이 생성되는 위치를 위해서라도 주인이 필요할 듯
	explicit CCloud2(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos);
	explicit CCloud2(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CCloud2(const CCloud2& rhs);
	virtual ~CCloud2();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

public:
	_uint& Get_CloudAlpha() { return m_iAlpha; }

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

	const _float				Get_Distance_From_Camera();
	void						Set_RandomSize();
	const _float				Set_RandomHeight();

private:
	CTexture*  m_pTextureCom;
	_vec3	   m_vCloudPos;

	_float	  m_fAccTime;
	_float	  m_fDeadTime;
	_uint	  m_iAlpha;

	LERP_FLOAT_INFO m_tLerpAlpha;

	_bool	  m_bDead_Start;
	_bool	  m_bStart;

	_float	  m_fSpeed;

public:
	static CCloud2* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos = vec3.zero); // 구름이 생성되는 위치를 위해서라도 주인이 필요할 듯

private:
	virtual void				Free() override;
};

