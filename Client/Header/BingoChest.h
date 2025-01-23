#pragma once
#include "GameObject.h"
#include "Chest.h"

BEGIN(Engine)

class CCollider;

END

class CBingoChest : public CChest
{
protected:
	explicit CBingoChest(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBingoChest(const CChest& rhs);
	virtual ~CBingoChest();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

private:
	HRESULT				Add_Component();

public:
	_bool				Get_IsOpen() { return m_bOpen; }
	void				Set_IsOpen() { m_bOpen = true; }

private:
	_bool				m_bOpen;

public:
	static				CBingoChest* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

