#pragma once

#include "Base.h"
#include "Engine_Define.h"

class CIsland;

enum class ISLAND_TYPE { VILLAGE, ICE, DEATH, KING, JUMP, TYPEEND };

BEGIN(Engine)

class CMiniGameMgr_Jump : public CBase
{
	DECLARE_SINGLETON(CMiniGameMgr_Jump)

private:
	explicit CMiniGameMgr_Jump();
	virtual ~CMiniGameMgr_Jump();

public:
	HRESULT					Init(LPDIRECT3DDEVICE9 _pGraphicDev);
	void					Update(const _float& _fDelta);

public:
	HRESULT					Start_MiniGame();
	HRESULT					End_MiniGame();

private:
	void					Check_MiniGame(const _float& _fDelta);
	HRESULT					Die_Player();

public:
	HRESULT					Create_Islands();
	const _bool&			Is_Init() const { return m_bInit; }


private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	CIsland*				m_arrIsland[(UINT)ISLAND_TYPE::TYPEEND];
	_bool					m_bInit;
	_bool					m_bActive;

private:
	virtual void			Free();
};

END

