#pragma once
#include "Environment.h"

BEGIN(Engine)

class CCollider;

END

class CBingo_Launcher : public CEnvironment
{
protected:
	explicit CBingo_Launcher(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBingo_Launcher(const CBingo_Launcher& rhs);
	virtual ~CBingo_Launcher();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

	_bool				Get_ShowReady() { return m_bShowUI; }
	void				Set_ShowReady(_bool _isReady) { m_bShowUI = _isReady; }

private:
	HRESULT				Add_Component();
	_bool				m_bShowUI;

public:
	static				CBingo_Launcher* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void		Free() override;

};

