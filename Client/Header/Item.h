#pragma once

#include "GameObject.h"
#include "AIComponent.h"

BEGIN(Engine)

class CTexture;

END

class CItem : public Engine:: CGameObject
{
protected:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CItem(const CItem& rhs);
	virtual ~CItem();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);


private:
	HRESULT					Add_Component();

#pragma region Access Methood

#pragma region STATINFO

public:

	const STATINFO&		Get_StatInfo() const { return m_tStatInfo; }

	const _bool&		Is_Dead() const { return m_tStatInfo.bDead; }

	void				Set_Dead(const _bool& _bDead = TRUE) { m_tStatInfo.bDead = _bDead; }

	void				Set_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP = _fMaxHp; }
	void				Set_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP = _fCurHp; }

	void				Set_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP = _fMaxMp; }
	void				Set_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP = _fCurMp; }

	void				Set_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp = _fMaxExp; }
	void				Set_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp = _fCurExp; }

	void				Set_AD(const _float& _fAD) { m_tStatInfo.fAD = _fAD; }
	void				Set_DF(const _float& _fDF) { m_tStatInfo.fDF = _fDF; }

	void				Set_Gold(const _float& _fGold) { m_tStatInfo.fGold = _fGold; }

	void				Add_MaxHP(const _float& _fMaxHp) { m_tStatInfo.fMaxHP += _fMaxHp; }
	void				Add_CurHP(const _float& _fCurHp) { m_tStatInfo.fCurHP += _fCurHp; }

	void				Add_MaxMP(const _float& _fMaxMp) { m_tStatInfo.fMaxMP += _fMaxMp; }
	void				Add_CurMP(const _float& _fCurMp) { m_tStatInfo.fCurMP += _fCurMp; }

	void				Add_MaxExp(const _float& _fMaxExp) { m_tStatInfo.fMaxExp += _fMaxExp; }
	void				Add_CurExp(const _float& _fCurExp) { m_tStatInfo.fCurExp += _fCurExp; }

	void				Add_AD(const _float& _fAD) { m_tStatInfo.fAD += _fAD; }
	void				Add_DF(const _float& _fDF) { m_tStatInfo.fDF += _fDF; }

	void				Add_Gold(const _float& _fGold) { m_tStatInfo.fGold += _fGold; }

#pragma endregion

	void				Play_ColLogic(const _float& fTimeDelta) {}; // 각 아이템 클래스에서 세부적으로 설정

	ITEM_TYPE			Get_ItemType() { return m_eItemType; }

	_uint&				Get_ItemValue() { return m_iItemValue; }

#pragma endregion
	// 성혁 추가
	_bool				Get_IsCol() { return m_bCol; }
	virtual void		Set_InvenTrans(_float _fPosX, _float _fPosY)
	{
		m_ItemMatWorld._11 = 193.f * 0.5f;
		m_ItemMatWorld._22 = 128.f * 0.5f;
		m_ItemMatWorld._41 = _fPosX;
		m_ItemMatWorld._42 = _fPosY;
	}

protected:

	STATINFO				m_tStatInfo;    // Item Info
	CTexture*				m_pTextureCom;  // Texture com
	CAIComponent*			m_pAICom;
	_float					m_fJumpingSpeed; // jumping motion use
	
	ITEM_TYPE				m_eItemType;     // ItemType
	_vec3					m_vImageSize;	 // Image Size

	//성혁 추가
	_bool					m_bCol;
	_matrix					m_ItemMatWorld;

	//준 추가
	_uint					m_iItemValue;



	
protected:
	virtual void			Free() override;
};

