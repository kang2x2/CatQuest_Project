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
	_int				   m_iQuestID; // ���� �������� ����Ʈ ID
	map<_int, CQuestData*> m_mapQuestList; // ��� ����Ʈ ���

	_bool				   m_bInit = false;

	// �� ��ȯ �� �� ���ǽø� ��� �����ϱ� ������ nullptr ������ ����.
	// �̹� ����Ʈ���� ��ȯ �Ŀ� nullptr üũ�� ������ ���� ���ϴ� �κе� �ֱ� ������
	// m_bIsAble�� false��� �ƿ� ���ǹ��� ���� �ȵǰ� �Ѵ�.
	_bool				   m_bIsAble;

	CGameObject*		   m_pIndicator;

private:
	virtual void			Free();
};

END

