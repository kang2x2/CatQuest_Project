#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CPlayerSlash : public CEffect
{
	explicit CPlayerSlash(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, _bool _IsRising);
	explicit CPlayerSlash(const CPlayerSlash& rhs);
	virtual ~CPlayerSlash();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture*	m_pTexRisingCom;
	CTexture*	m_pTexChoppingCom;
	CAnimation* m_pAnimation;
	
	_bool		m_bRight;
	_bool		m_bRisign;
public:
	static CPlayerSlash* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, _bool _IsRising);

private:
	virtual void				Free() override;
};

