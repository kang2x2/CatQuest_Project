#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;

END

class CDialogUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
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
	// 텍스처랑 매트릭스
	CTexture*				m_pUITextureCom[3];
	CTransform*				m_pUITransform;
	_matrix					m_matUI[2];
	// 화자 판단 및 화자텍스처
	OBJ_ID					m_eObjID;
	SPIRITEMO_TYPE			m_eEmo;
	_uint					m_iNpc;
	// 띄울 텍스트랑 타이핑이펙트용 변수
	RECT					m_rcText;
	wstring					m_strDialog;
	wstring					m_strTyping;
	_uint					m_iTextCnt;
	_float					m_fAcc;

	// 내리고 올릴 변수
	_bool					m_bUp;
	_bool					m_bDown;
	// 줄이고 늘릴 변수
	_bool					m_bExpand;
	_bool					m_bShrink;
	// 다이얼로그 끝났는지 판단할 불값
	_bool					m_bEnd;

	// 다이얼로그 타입
	DIALOG_TYPE				m_bDialogType;
	// 다이얼로그 러프
	LERP_FLOAT_INFO			m_tSizeUpLerpX;
	LERP_FLOAT_INFO			m_tSizeUpLerpY;
	LERP_FLOAT_INFO			m_tSizeDownLerpX;
	LERP_FLOAT_INFO			m_tSizeDownLerpY;

	// 알파
	LERP_FLOAT_INFO			m_tAlphaUpLerp;
	LERP_FLOAT_INFO			m_tAlphaDownLerp;
	_float					m_fAlpha; 

public:

	static CDialogUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, OBJ_ID eNpc, wstring strDialog, DIALOG_TYPE _bDialogType = DIALOG_TYPE::DIALOG_NORMAL, SPIRITEMO_TYPE eEmo = SPIRITEMO_TYPE::HAPPY);


protected:
	virtual void			Free() override;
};

