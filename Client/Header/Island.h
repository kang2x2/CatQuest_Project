#pragma once


/*

	*	�� ������Ʈ�� �ش� Ŭ������ ��ӹ޾� �����ȴ�.
	
	*	��������� ������������Ʈ ���͸� ���� ������, �ش� ������������Ʈ���� �÷��̾�� �浹�� �ش� Ŭ������ Enter ~ Exit Player �Լ��� ȣ���ϰ� �ȴ�.
	
	*	������ �������z ���ʹ� �浹 �˻���̸�, ������ ���� �� ó���� �ش� Ŭ������ ��ӹ޾� ������ �Ļ�Ŭ�������� �����Ѵ�.

*/

enum class PLAYER_COLLISION { ENTER, STAY, EXIT, NONE, TYPEEND };

#include "GameObject.h"

class CRangeObj;

class CIsland : public Engine::CGameObject
{
public:
	explicit CIsland(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CIsland(const CIsland& rhs);
	virtual ~CIsland();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;

public:
	virtual void		OnCollision_Enter(CGameObject* _pColObj);
	virtual void		OnCollision_Stay(CGameObject* _pColObj);
	virtual void		OnCollision_Exit(CGameObject* _pColObj);

public:
	void				Change_Scene() { m_iCurIn = 0.f; }

private:
	HRESULT				Add_Component(void);

protected:
	virtual HRESULT		Add_RangeObj() PURE;

public:
	void				Check_Player_Collision();
	virtual void		Enter_Player() PURE;
	virtual void		Stay_Player() PURE;
	virtual void		Exit_Player() PURE;
	const _bool			Is_In_Player() const { return 0 < m_iCurIn; }


protected:

	_int				m_iCurIn;
	_int				m_iPrevIn;

	PLAYER_COLLISION	m_eCurCollison;
	vector<CRangeObj*>	m_vecRangeObj;

protected:
	virtual void		Free() override;

};