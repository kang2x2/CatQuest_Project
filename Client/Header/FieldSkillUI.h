#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CPlayer;
class CSkill;

class CFieldSkillUI : public CUI  // ����Ʈ ��� | ��ŷ�� ������ ������ UI �Դϴ�
{

protected:

	explicit CFieldSkillUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFieldSkillUI(const CFieldSkillUI& rhs);
	virtual ~CFieldSkillUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;
	void					Picking_UI();
	void					Mouse_Input();
	void					Reset_SkillUI();
	void					Play_SKill();

	void					Set_Skill();

	void					Mouse_Update();


private:
	CPlayer*				m_pPlayer;
	// UI�� ��Ʈ����
	_matrix					m_matWorldUI[17];
	_matrix					m_matMouse;
	// ��, ������
	_float					m_RingSizeX[2];
	_float					m_RingSizeY[2];
	_float					m_RingPosX[5];
	_float					m_RingPosY[5];
	_bool					m_bShirnk;
	// ȭ��
	_float					m_ArrowSizeX;
	_float					m_ArrowSizeY;
	_float					m_ArrowPosX[4];
	_float					m_ArrowPosY[4];
	_bool					m_bReach;
	_float					m_fReach;
	// ��ų
	_uint					m_iSkillKind[4];
	_float					m_SkillSizeX;
	_float					m_SkillSizeY;
	_float					m_ManaSizeX;
	_float					m_ManaSizeY;
	_float					m_SkillPosX[4];
	_float					m_SkillPosY[4];
	
	// ��ŷ��
	RECT					m_rcPick[4];
	_bool					m_bPick[4];

	CTexture*				m_pUITextureCom[4];
	CTexture*				m_pCursorTexCom;

	CTransform*				m_pUITransform[5];
	// ��Ʈ����
	RECT					m_rcFont[4];
	

	_bool					m_bIsOn;
	_bool					m_bSkill[4];
	
	CSkill*					m_pPlayerSkill[4];
	_uint					m_SkillKind[4];

	_bool					m_bPlaySound;

public:
	static CFieldSkillUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);


protected:
	virtual void			Free() override;

};

