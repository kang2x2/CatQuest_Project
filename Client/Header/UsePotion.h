#pragma once
#include "Item.h"

BEGIN(Engine)


END

class CUsePotion : public CItem
{
protected:
	explicit CUsePotion(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUsePotion(const CItem& rhs);
	virtual ~CUsePotion();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void		Set_InvenTrans(_float _fPosX, _float _fPosY)
	{
		m_ItemMatWorld._11 = 193.f * 0.5f;
		m_ItemMatWorld._22 = 128.f * 0.5f;
		m_ItemMatWorld._41 = _fPosX;
		m_ItemMatWorld._42 = _fPosY;
	}
	_int				Get_Amount() { return m_iAmount; }
	void				Set_Amount(_int _iAmount) { m_iAmount = _iAmount; }

private:
	HRESULT					Add_Component();
	_matrix					m_ItemMatWorld;
	_int					m_iAmount;


public:
	static				CUsePotion* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;



};

