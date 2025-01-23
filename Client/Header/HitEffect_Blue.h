#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END


class CHitEffect_Blue : public CEffect
{
protected:
	explicit CHitEffect_Blue(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CHitEffect_Blue(const CEffect& rhs);
	virtual ~CHitEffect_Blue();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	HRESULT					Add_Component();



private:

	CTexture* m_pTextureCom;
	CGameObject* m_pOwnerObj;
	CAnimation* m_pAnimation;

	_vec3	  m_vPos;
	


public:
	static CHitEffect_Blue* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);


protected:
	virtual void			Free() override;





};

