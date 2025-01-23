#pragma once
#include "UI.h"

class CPlayer;

class CLevelUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CLevelUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CLevelUI(const CLevelUI& rhs);
	virtual ~CLevelUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	CPlayer*	m_pPlayer;

	wstring		m_strPlayerLevel;
	RECT		m_rcLevel;

public:

	static CLevelUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

