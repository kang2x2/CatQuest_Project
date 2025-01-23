#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CRenderMgr : public CBase
{
	DECLARE_SINGLETON(CRenderMgr)

public:
	explicit CRenderMgr();
	virtual ~CRenderMgr();

public:
	void						Add_RenderGroup(RENDERID eType, CGameObject* pGameObject); // �� �����Ӹ��� �����Ѵ�.
	void						Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);  // CManagement�� �����Լ����� ȣ���Ѵ�.
								// ����̽��� ���� Ÿ�ֿ̹��� �ʿ��ϹǷ� �����ÿ��� �Ű������� �޴´�.
								// �Ű������� ������ ������ ���� �Ű����� ����� ���� ���۷��� ī��Ʈ ������ ���ϱ� ���ؼ���.

	void						Clear_RenderGroup(); 

public:							// �׷캰�� ������ ���� �Լ��� ���� �����ȴ�.
	void						Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_Nonalpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_UI(LPDIRECT3DDEVICE9& pGraphicDev);

private:
	list<CGameObject*>			m_RenderGroup[RENDER_END]; // ����Ǵ� ���� ������Ʈ�� ���� ������Ʈ���� �׷����� ������.

private:
	virtual void				Free();
};

END
