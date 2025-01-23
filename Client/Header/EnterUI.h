#pragma once
#include "UI.h"
#include "GameObject.h"

class CEnterUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CEnterUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CEnterUI(const CEnterUI& rhs);
	virtual ~CEnterUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	void					EnterUI_On(UIENTER_TYPE eUIEnter, CGameObject* pObj);
	void					EnterUI_Off();

private:
	virtual HRESULT			Add_Component() override;

private:
	UIENTER_TYPE			m_eUIEnter;

	_bool					m_bIsOn;

	_bool					m_bIsStart;
	_bool					m_bIsEnd;

	_bool					m_bIsShirk;
	_bool					m_bIsExpand;


public:

	static CEnterUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

