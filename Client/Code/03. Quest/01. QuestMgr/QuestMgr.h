#pragma once
#include "GameObject.h"
#include "QuestData.h"

BEGIN(Engine)

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)
private:
	explicit CQuestMgr();
	virtual ~CQuestMgr();

public:
	HRESULT	Init(LPDIRECT3DDEVICE9 m_pGraphicDev, CGameObject* _pPlayer);
	void	Update(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	_bool	Get_IsInit() { return m_bInit; }
	_bool	Get_IsAble() { return m_bIsAble; }
	void 	Set_IsAble(_bool _IsAble) { m_bIsAble = _IsAble; }

	void	Set_ReadyNext();

	CQuestData* Get_Quest();
private:
	_int				   m_iQuestID; // 현재 진행중인 퀘스트 ID
	map<_int, CQuestData*> m_mapQuestList; // 모든 퀘스트 담기

	_bool				   m_bInit = false;

	// 씬 전환 할 때 엔피시를 모두 삭제하기 때문에 nullptr 에러가 난다.
	// 이미 퀘스트에서 전환 후에 nullptr 체크를 하지만 잡지 못하는 부분도 있기 때문에
	// m_bIsAble가 false라면 아예 조건문도 실행 안되게 한다.
	_bool				   m_bIsAble;

	CGameObject*		   m_pIndicator;

private:
	virtual void			Free();
};

END

