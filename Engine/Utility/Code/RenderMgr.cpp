#include "..\..\Header\RenderMgr.h"
#include "CameraMgr.h"
#include "Management.h"
#include "Export_Function.h"

IMPLEMENT_SINGLETON(CRenderMgr)

CRenderMgr::CRenderMgr()
{

}

CRenderMgr::~CRenderMgr()
{
	Free();
}

void CRenderMgr::Add_RenderGroup(RENDERID eType, CGameObject * pGameObject)
{
	if (RENDER_END <= eType || nullptr == pGameObject)
		return;

	m_RenderGroup[eType].push_back(pGameObject);

	pGameObject->AddRef(); // ����̽��� ����Ǿ����Ƿ� ���۷���ī��Ʈ�� ������Ų��.
}

void CRenderMgr::Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	// ���� �켱 ������ ���� �� ���� �Լ��� ȣ���Ѵ�.
	Render_Priority(pGraphicDev);
	Render_Nonalpha(pGraphicDev);
	Render_Alpha(pGraphicDev);
	Render_UI(pGraphicDev);

	// ���� �׷��� ����.
	Clear_RenderGroup();
}

void CRenderMgr::Clear_RenderGroup()
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for_each(m_RenderGroup[i].begin(), m_RenderGroup[i].end(), CDeleteObj()); // ������ �ƴ϶� �߰� �� �÷ȴ� ���۷��� ī��Ʈ ������
		m_RenderGroup[i].clear();
	}
}

void CRenderMgr::Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev)
{
	for (auto iter : m_RenderGroup[RENDER_PRIORITY])
	{
		if (!iter->Is_Active()) continue;

		iter->Render_Object();
	}
}

void CRenderMgr::Render_Nonalpha(LPDIRECT3DDEVICE9& pGraphicDev)
{

	for (auto iter : m_RenderGroup[RENDER_NONALPHA])
	{
		if (!iter->Is_Active()) continue;

		iter->Render_Object();
	}

}

void CRenderMgr::Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev)
{
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // z ���� �ڵ� ���� ���� (���� ���� ���ؼ�)

	if (m_RenderGroup[RENDER_ALPHA].size() > 0)
	{
		int k = 0;
	}
	m_RenderGroup[RENDER_ALPHA].sort([&](CGameObject* pDst, CGameObject* pSrc) { return pDst->Get_ViewZ() > pSrc->Get_ViewZ(); });

	for (auto iter : m_RenderGroup[RENDER_ALPHA])
	{
		if (!iter->Is_Active()) continue;
		if (iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_1 ||
			iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_2 ||
			iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_3) continue;

		float z = iter->Get_ViewZ();

		iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_ALPHA])
	{
		if (!iter->Is_Active()) continue;
		if (iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_1 ||
			iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_2 ||
			iter->Get_ID() == OBJ_ID::EFFECT_CLOUD_3) 
				iter->Render_Object();	
	}

	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE); // �ٽ� z ���� �ڵ����� �Ҵ�.
	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CRenderMgr::Render_UI(LPDIRECT3DDEVICE9& pGraphicDev)
{
	// ���� �ɼ�
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);    // Z���� OFF

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // ���ķ����� ON

	pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	// ���� UI ����
	for (auto iter : m_RenderGroup[RENDER_WDUI])
	{
		if (UI_LAYER::LV0 == iter->Get_LayerLv())
			iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_WDUI])
	{
		if (UI_LAYER::LV1 == iter->Get_LayerLv())
			iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_WDUI])
	{
		if (UI_LAYER::LV2 == iter->Get_LayerLv())
			iter->Render_Object();
	}
		


	// ���� ��� ���� ��� 
	D3DVIEWPORT9 BackUpViewPort;
	_matrix		 BackUpProj;
	_matrix		 BackUpView;
	
	if (SCENE_TYPE::INTRO != CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		NULL_CHECK((CCameraMgr::GetInstance()->Get_CurCamera()))
		BackUpViewPort = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();
		BackUpProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
		BackUpView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
	}
	
	// UI �� ���ο� �� ��Ʈ ���� �� ����
	D3DVIEWPORT9 UiViewPort;
	UiViewPort.X = 0;
	UiViewPort.Y = 0;
	UiViewPort.Width = WINCX;
	UiViewPort.Height = WINCY;
	UiViewPort.MinZ = 0;
	UiViewPort.MaxZ = 1;
	pGraphicDev->SetViewport(&UiViewPort);

	// �� �����̽�
	_matrix matView;
	pGraphicDev->SetTransform(D3DTS_VIEW, D3DXMatrixIdentity(&matView)); // �׵���ķ� ����� �� ��� �ʱ�ȭ.

	// ���� 
	_matrix    m_matProj;
	D3DXMatrixOrthoOffCenterLH(&m_matProj, 0, WINCX, 0, WINCY, 0.f, 1.f);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);   // �������� ��� ����.

	for (auto iter : m_RenderGroup[RENDER_VIEWUI])
	{
		if (UI_LAYER::LV0 == iter->Get_LayerLv())
			iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_VIEWUI])
	{
		if (UI_LAYER::LV1 == iter->Get_LayerLv())
			iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_VIEWUI])
	{
		if (UI_LAYER::LV2 == iter->Get_LayerLv())
			iter->Render_Object();
	}
	for (auto iter : m_RenderGroup[RENDER_VIEWUI])
	{
		if (UI_LAYER::LV3 == iter->Get_LayerLv())
			iter->Render_Object();
	}

	if (SCENE_TYPE::INTRO != CManagement::GetInstance()->Get_CurScene()->Get_SceneType())
	{
		// �ٽ� ���� ��� ���� ����
		pGraphicDev->SetViewport(&BackUpViewPort);                   // UI ��ü ��� �� ����ص� ���� ����Ʈ�� �ǵ���.
		pGraphicDev->SetTransform(D3DTS_PROJECTION, &BackUpProj);    // UI ��ü ��� �� �ٽ� �������� ��� ����.
		pGraphicDev->SetTransform(D3DTS_VIEW, &BackUpView);
	}

	pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // ���ķ����� OFF
	pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // Z���� ON

}

void CRenderMgr::Free()
{
	Clear_RenderGroup();
}
