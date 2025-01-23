#pragma once
#include "Item.h"

BEGIN(Engine)

class CTexture;

END

class CItem_Equipment : public CItem
{

protected:
	explicit CItem_Equipment(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CItem_Equipment(const CItem& rhs);
	virtual ~CItem_Equipment();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;


private:
	HRESULT					Add_Component();


protected:

	virtual void		Free() override;


};

