#pragma once

#include "GameObject.h"

BEGIN(Engine)

END

class CCameraTargetObj : public Engine::CGameObject
{
private:
	explicit CCameraTargetObj(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCameraTargetObj(const CCameraTargetObj& rhs);
	virtual ~CCameraTargetObj();

public:
	virtual HRESULT		Ready_Object() override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object() override;
	virtual void		Render_Object() override;


public:
	const MOVEINFO& Get_MoveInfo() const { return m_tMoveInfo; }

	void				Set_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed = _fMoveSpeed; }
	void				Set_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed = _fRotSpeed; }

	void				Add_MoveSpeed(const _float& _fMoveSpeed) { m_tMoveInfo.fMoveSpeed += _fMoveSpeed; }
	void				Add_RotSpeed(const _float& _fRotSpeed) { m_tMoveInfo.fRotSpeed += _fRotSpeed; }

private:
	HRESULT				Add_Component();
	void				Key_Input(const _float& fTimeDelta);

private:
	MOVEINFO			m_tMoveInfo;


public:
	static CCameraTargetObj* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free() override;

};

