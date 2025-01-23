#pragma once

#include "GameObject.h"

class CRangeObj;
class CFlagOwner;

BEGIN(Engine)

class CTexture;

END

enum class PLAYER_COLLISION2 { ENTER, STAY, EXIT, NONE, TYPEEND };


class CFlag : public Engine::CGameObject
{
protected:
	explicit CFlag(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CFlag(const CFlag& rhs);
	virtual ~CFlag();

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

protected:
	virtual HRESULT		Add_RangeObj();

public:
	void				Check_Player_Collision();
	virtual void		Enter_Player();
	virtual void		Exit_Player();
	const _bool			Is_In_Player() const { return 0 < m_iCurIn; }

public:
	virtual FLAG_TAG    Get_FlagTag() { return m_eFlagTag; }
	virtual _float		Get_Translucent() { return m_fTranslucent; }
	
	virtual _bool		Get_Create() { return m_bCreate; }
	virtual void		Set_Create() { m_bCreate = true; }
	virtual _bool		Get_Delete() { return m_bDelete; }
	virtual void		Set_Delete() { m_bDelete = true; }
protected:
	_int				m_iCurIn;
	_int				m_iPrevIn;

	PLAYER_COLLISION2	m_eCurCollison;
	CRangeObj*			m_pRangeObj; 

	_bool				m_bCol; // �浹 ����(�Ⱦ�)

protected:
	CTexture*	m_pFlagTexCom;
	CFlagOwner* m_pFlagOwner;

	_float				m_fTranslucent; // ����
	LERP_FLOAT_INFO		m_tCreateLerp; // ���� ���� ����
	LERP_FLOAT_INFO		m_tDeleteLerp; // ���� �Ҹ� ����
	_bool				m_bCreate; // ���� ���� ����
	_bool				m_bDelete; // �Ҹ� ���� ����.

	FLAG_TAG			m_eFlagTag; // ���� Ÿ��
protected:
	virtual void			Free() override;
};

