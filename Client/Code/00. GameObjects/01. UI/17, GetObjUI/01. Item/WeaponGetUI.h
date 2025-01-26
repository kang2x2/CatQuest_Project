#pragma once
#include "UI.h"
#include "Skill.h"

BEGIN(Engine)

class CTexture;

END

class CWeaponGetUI : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:
	explicit CWeaponGetUI(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon);
	explicit CWeaponGetUI(const CWeaponGetUI& rhs);
	virtual ~CWeaponGetUI();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	_int			 m_iTranslucent;
	_bool			 m_bDelete;
	CGameObject*	 m_pWeapon;

	CTexture*		 m_pBackTexCom;
	_matrix			 m_matBack;
					 
	CTexture*		 m_pBaseTexCom;
	_matrix			 m_matBase;
					 
	CTexture*		 m_pWeaponTexCom;
	_matrix			 m_matWeapon;
					 
	CTexture*		 m_pInventoryTexCom;
	_matrix			 m_matInventory;
					 
	CTexture*		 m_pArrowTexCom;
	_matrix			 m_matArrow;

	CTexture*		 m_pHeartTexCom;
	_matrix			 m_matHeart;
	CTexture*		 m_pDamageTexCom;
	_matrix			 m_matDamage;
	CTexture*		 m_pArmorTexCom;
	_matrix			 m_matArmor;

	// 일반 무기 폰트
	LERP_FLOAT_INFO m_tStatLerp;
	_int			m_iStatTranslucent;

	RECT			m_rcName;
	RECT			m_rcnNavigation;

	RECT			m_rcHeart;
	RECT			m_rcDamage;
	RECT			m_rcArmor;


public:
	static CWeaponGetUI* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon);

protected:
	virtual void			Free() override;
};

