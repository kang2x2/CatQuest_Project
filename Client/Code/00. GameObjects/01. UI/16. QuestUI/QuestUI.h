#pragma once
#include "UI.h"

class CQuestUI : public CUI     
{

protected:

	explicit CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CQuestUI(const CQuestUI& rhs);
	virtual ~CQuestUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	CTexture*   m_pQuestUITexCom;
	_matrix		m_matQuestUI;
	RECT		m_QuestTitleRc;
	RECT		m_QuestContentRc;

	// ���̾�α� ����
	// ��ġ
	LERP_FLOAT_INFO			m_tRightUpPosLerpX;
	LERP_FLOAT_INFO			m_tRightUpPosLerpY;
	LERP_FLOAT_INFO			m_tLeftDownPosLerpX;
	LERP_FLOAT_INFO			m_tLeftDownPosLerpY;

	// ũ��
	LERP_FLOAT_INFO			m_tSizeUpLerpX;
	LERP_FLOAT_INFO			m_tSizeUpLerpY;
	LERP_FLOAT_INFO			m_tSizeDownLerpX;
	LERP_FLOAT_INFO			m_tSizeDownLerpY;

	_bool					m_bLeftDownPos;
	_bool					m_bShowFont;

public:

	static CQuestUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;
};

