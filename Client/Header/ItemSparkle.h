#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CItemSparkle : public CEffect
{
	explicit CItemSparkle(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CItemSparkle(const CItemSparkle& rhs);
	virtual ~CItemSparkle();

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
	_float	  m_fSize;
	_bool	  m_bSizeUp, m_bPositionUp, m_bPlay;
	_int	  m_iReplayTime;
	_matrix matWorld;

public:
	static CItemSparkle* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject); 

private:
	virtual void				Free() override;
};

