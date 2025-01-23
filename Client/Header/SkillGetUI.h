#pragma once
#include "UI.h"
#include "Skill.h"

BEGIN(Engine)

class CTexture;

END

class CSkillGetUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:
	explicit CSkillGetUI(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill);
	explicit CSkillGetUI(const CSkillGetUI& rhs);
	virtual ~CSkillGetUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	_int	  m_iTempLv;
	_int	  m_iTranslucent;
	_bool     m_bDelete;
	CSkill*   m_pSkill;

	CTexture* m_pBackTexCom;
	_matrix	  m_matBack;

	CTexture* m_pBaseTexCom;
	_matrix	  m_matBase;

	CTexture* m_pSkillTexCom;
	_matrix   m_matSkill;

	CTexture* m_pInventoryTexCom;
	_matrix	  m_matInventory;

	CTexture* m_pArrowTexCom;
	_matrix	  m_matArrow;

	// 일반 스킬 폰트
	LERP_FLOAT_INFO m_tLvPrevLerp;
	LERP_FLOAT_INFO m_tLvCurLerp;
	_int			m_iLvPrevTranslucent;
	_int			m_iLvCurTranslucent;
	RECT			m_rcName;
	RECT			m_rcnNavigation;
	RECT			m_rcLv1;
	RECT			m_rcLv2;
	RECT			m_rcLv3;
	// 냥다람쥐 폰트
	RECT			m_rcFlyNavigation;
	RECT			m_rcFlyGet;


public:
	static CSkillGetUI* Create(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill);

protected:
	virtual void			Free() override;
};

