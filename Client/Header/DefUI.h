#pragma once
#include "UI.h"

class CPlayer;

class CDefUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CDefUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDefUI(const CDefUI& rhs);
	virtual ~CDefUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Follow_Player();

private:
	CTransform*				m_pUITransformCom[3];

	CPlayer*				m_pPlayer;
	_float					m_fDefRatio;

	LERP_FLOAT_INFO			m_tAlpha;
	_uint					m_iAlpha;
	_bool					m_bStart;
	_bool					m_bWork;

public:
	static CDefUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

