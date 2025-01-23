#pragma once
#include "UI.h"

class CMonster;

class CBossHpUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:

	explicit CBossHpUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBossHpUI(const CBossHpUI& rhs);
	virtual ~CBossHpUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

	void					Set_Owner(CGameObject* pMonster) { m_pMonster = pMonster; }

	void					Caulate_Purple_Bar();
	void					Caulate_Red_Bar();
	
private:
	CTransform*				m_pUITransformCom[5];

	CGameObject*			m_pMonster;
	_float					m_fHpRatio;
	_float					m_fCurRatio;

	_float					m_fCapSizeX;
	_float					m_fCapSizeY;

	_float					m_fBarMultiX;
	_float					m_fBarMultiY;
	_float					m_fCapMultiX;
	_float					m_fCapMultiY;

	_float					m_fBarRealX;
	_float					m_fBarRealY;
	_float					m_fCapRealX;
	_float					m_fCapRealY;


	_matrix					m_matUI[5];
	LERP_FLOAT_INFO			m_tSize;

	_bool					m_bPurpleEnd;
	_bool					m_bRedEnd;

	LERP_FLOAT_INFO			m_tAlphaBlack;
	_uint					m_fAlphaBlack;
	_bool					m_bStart;
	_bool					m_bWork;
	_bool					m_bCheck;

	_bool					m_bDead;


public:
	static CBossHpUI* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* pMonster);


protected:
	virtual void			Free() override;
};


