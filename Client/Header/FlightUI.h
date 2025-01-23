#pragma once
#include "UI.h"

class CPlayer;

class CFlightUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CFlightUI(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer);
	explicit CFlightUI(const CFlightUI& rhs);
	virtual ~CFlightUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	CPlayer*	m_pPlayer;

public:

	static CFlightUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CPlayer* pPlayer);


protected:
	virtual void			Free() override;
};

