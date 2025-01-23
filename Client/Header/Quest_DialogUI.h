#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CQuest_DialogUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:
	explicit CQuest_DialogUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CQuest_DialogUI(const CQuest_DialogUI& rhs);
	virtual ~CQuest_DialogUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	_bool&					Is_DialogEnd() { return m_bEnd; }
	_bool&					Is_DialogDead() { return m_bDead; }
	HRESULT					Ready_Dialog(wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL);
	_bool					EndLerp_Dialog();

	void					End_Dialog();

private:
	virtual HRESULT			Add_Component() override;
	void					Typing_Effect(const _float& fTimeDelta);

private:
	// �ؽ�ó�� ��Ʈ����
	CTexture*				m_pUITextureCom;
	CTransform*				m_pUITransform;
	_matrix					m_matUI;
	

	// ��� �ؽ�Ʈ�� Ÿ��������Ʈ�� ����
	RECT					m_rcText;
	wstring					m_strDialog;
	wstring					m_strTyping;
	_uint					m_iTextCnt;
	_float					m_fAcc;

	// ������ �ø� ����
	_bool					m_bUp;
	_bool					m_bDown;
	
	// ���̾�α� �������� �Ǵ��� �Ұ�
	_bool					m_bEnd;
	_bool					m_bDead;

	// ���̾�α� Ÿ��
	DIALOG_TYPE				m_bDialogType;
	// ���̾�α� ����
	LERP_FLOAT_INFO			m_tSizeUpLerpX;
	LERP_FLOAT_INFO			m_tSizeUpLerpY;
	LERP_FLOAT_INFO			m_tSizeDownLerpX;
	LERP_FLOAT_INFO			m_tSizeDownLerpY;

	// ����
	LERP_FLOAT_INFO			m_tAlphaUpLerp;
	LERP_FLOAT_INFO			m_tAlphaDownLerp;
	_float					m_fAlpha;

	//
	LERP_FLOAT_INFO			m_tAlphaFont;
	_float					m_fAlphaFont;

public:
	static CQuest_DialogUI* Create(LPDIRECT3DDEVICE9 pGraphicDev, wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL);


protected:
	virtual void			Free() override;
};


