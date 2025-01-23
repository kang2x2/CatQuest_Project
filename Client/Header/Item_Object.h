#pragma once
#include "Item.h"

BEGIN(Engine)

class CTexture;

END

class CItem_Object : public CItem
{
protected:
	explicit CItem_Object(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CItem_Object(const CItem& rhs);
	virtual ~CItem_Object();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();

private:
	LERP_VEC3_INFO			m_tLerp;

protected:

	virtual void		Free() override;





};

