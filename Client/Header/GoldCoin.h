#pragma once
#include "Item_Object.h"

BEGIN(Engine)

class CCollider;

END

class CGoldCoin : public CItem_Object
{
protected:
	explicit CGoldCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGoldCoin(const CItem& rhs);
	virtual ~CGoldCoin();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();


public:
	static				CGoldCoin* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private: 

	LERP_FLOAT_INFO       m_tAlpha;

	LERP_VEC3_INFO		 m_tLerpPos;
protected:
	virtual void		Free() override;


};

