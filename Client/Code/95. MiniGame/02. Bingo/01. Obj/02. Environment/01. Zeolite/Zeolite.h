#pragma once
#include "GameObject.h"
#include "Npc.h"

BEGIN(Engine)

class CCollider;

END

class CZeolite : public CNpc
{
protected:
	explicit CZeolite(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CZeolite(const CNpc& rhs);
	virtual ~CZeolite();

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
	_bool				Get_IsDelete() { return m_bDelete; }
	void				Set_IsDelete() { m_bDelete = true; }

private:
	LERP_FLOAT_INFO		m_tPosDownLerpY;
	LERP_FLOAT_INFO		m_tPosDownLerpZ;
	LERP_FLOAT_INFO		m_tDustCreateLerp;
	LERP_FLOAT_INFO     m_tAlphaLerp;

	_float				m_fAlpha;
	_bool				m_bDelete;

public:
	static				CZeolite* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

