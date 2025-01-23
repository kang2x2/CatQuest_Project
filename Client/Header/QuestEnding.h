#pragma once
#include "QuestData.h"

class CQuestEnding : public CQuestData
{
public:
	explicit CQuestEnding(wstring _QuestName, LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer);
	virtual ~CQuestEnding();

public:
	virtual void  Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer)   override;
	virtual _bool Update(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pIndicator, _bool* _IsAble) override;

private:
	_bool	m_bEndingScene;
	_int	m_iStayEndingTime;

};

