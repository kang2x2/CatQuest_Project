#pragma once
#include "UI.h"

class CBingo_SuccesUI : public CUI
{

protected:

	explicit CBingo_SuccesUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBingo_SuccesUI(const CBingo_SuccesUI& rhs);
	virtual ~CBingo_SuccesUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

	void					Ready_Lerp();
private:
	virtual HRESULT			Add_Component() override;

private:
	// ���� ����
	LERP_FLOAT_INFO			m_tSizeUpLerp;
	LERP_FLOAT_INFO			m_tSizeReturnLerp;

	// �Ҹ� ����
	LERP_FLOAT_INFO			m_tDelSizeUpLerp;
	LERP_FLOAT_INFO			m_tDelSizeDownLerp;

	// ���� ����
	LERP_FLOAT_INFO			m_tDeleteLerp;

	// ���� ������
	_float					m_fCurSize;

	// ���� ����
	_int					m_iLerpLevel;
public:

	static CBingo_SuccesUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

