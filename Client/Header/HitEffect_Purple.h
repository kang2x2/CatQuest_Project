#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END


class CHitEffect_Purple : public CEffect
{
protected:
	explicit CHitEffect_Purple(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);
	explicit CHitEffect_Purple(const CEffect& rhs);
	virtual ~CHitEffect_Purple();

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
	static CHitEffect_Purple* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& _pPos);


protected:
	virtual void			Free() override;





};

