#pragma once
#include "Item_Object.h"

BEGIN(Engine)

END

class CExpCoin : public CItem_Object
{
protected:
	explicit CExpCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CExpCoin(const CItem& rhs);
	virtual ~CExpCoin();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT		Add_Component();


private:
	LERP_FLOAT_INFO       m_tAlpha;
	LERP_VEC3_INFO		 m_tLerpPos;

public:
	static				CExpCoin* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;


};

