#pragma once
#include "UI.h"

class CTabUI : public CUI  // ����Ʈ ��� | ��ŷ�� ������ ������ UI �Դϴ�
{

protected:

	explicit CTabUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTabUI(const CTabUI& rhs);
	virtual ~CTabUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;
	void					Picking_UI();


protected:
	bool					m_bPick;
	RECT					m_rcUI;

public:
	static CTabUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;

};

