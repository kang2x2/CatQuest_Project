#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CDialogUI : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:
	explicit CDialogUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CDialogUI(const CDialogUI& rhs);
	virtual ~CDialogUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	_bool					Is_DialogEnd() { return m_bEnd; }
	HRESULT					Ready_Dialog(OBJ_ID eNpc, wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL, SPIRITEMO_TYPE eEmo = SPIRITEMO_TYPE::HAPPY);
	_bool					EndLerp_Dialog();
private:
	virtual HRESULT			Add_Component() override;
	void					Select_Npc(OBJ_ID eNpc, SPIRITEMO_TYPE eEmo);
	void					Typing_Effect(const _float& fTimeDelta);

private:
	// �ؽ�ó�� ��Ʈ����
	CTexture*				m_pUITextureCom[3];
	CTransform*				m_pUITransform;
	_matrix					m_matUI[2];
	// ȭ�� �Ǵ� �� ȭ���ؽ�ó
	OBJ_ID					m_eObjID;
	SPIRITEMO_TYPE			m_eEmo;
	_uint					m_iNpc;
	// ��� �ؽ�Ʈ�� Ÿ��������Ʈ�� ����
	RECT					m_rcText;
	wstring					m_strDialog;
	wstring					m_strTyping;
	_uint					m_iTextCnt;
	_float					m_fAcc;

	// ������ �ø� ����
	_bool					m_bUp;
	_bool					m_bDown;
	// ���̰� �ø� ����
	_bool					m_bExpand;
	_bool					m_bShrink;
	// ���̾�α� �������� �Ǵ��� �Ұ�
	_bool					m_bEnd;

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

public:

	static CDialogUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, OBJ_ID eNpc, wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL, SPIRITEMO_TYPE eEmo = SPIRITEMO_TYPE::HAPPY);


protected:
	virtual void			Free() override;
};

