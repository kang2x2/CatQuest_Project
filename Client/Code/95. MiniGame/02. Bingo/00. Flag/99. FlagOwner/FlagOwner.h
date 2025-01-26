#pragma once
#include "GameObject.h"

class CFlag;

BEGIN(Engine)

END

class CFlagOwner : public Engine::CGameObject
{
protected:
	explicit CFlagOwner(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CFlagOwner(const CFlagOwner& rhs);
	virtual ~CFlagOwner();

public:
	HRESULT				Ready_Object();

public:
	void				Check_Player_Collision(const OBJ_ID& _eID);
	vector<CFlag*>		Get_FlagVector() { return m_vecFlag; }

private:
	vector<CFlag*>		m_vecFlag;
public:
	static				CFlagOwner* Create(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
protected:
	virtual void			Free() override;
};

