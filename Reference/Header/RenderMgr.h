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
	void						Add_RenderGroup(RENDERID eType, CGameObject* pGameObject); // 매 프레임마다 갱신한다.
	void						Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);  // CManagement의 렌더함수에서 호출한다.
								// 디바이스는 렌더 타이밍에만 필요하므로 렌더시에만 매개변수로 받는다.
								// 매개변수가 참조인 이유는 굳이 매개변수 복사로 인한 레퍼런스 카운트 관리를 피하기 위해서다.

	void						Clear_RenderGroup(); 

public:							// 그룹별로 별개의 렌더 함수를 통해 렌더된다.
	void						Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_Nonalpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void						Render_UI(LPDIRECT3DDEVICE9& pGraphicDev);

private:
	list<CGameObject*>			m_RenderGroup[RENDER_END]; // 공통되는 렌더 스테이트를 가진 오브젝트끼리 그룹으로 나눈다.

private:
	virtual void				Free();
};

END
