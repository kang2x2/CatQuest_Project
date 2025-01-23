#include "..\..\Header\GraphicDev.h"

IMPLEMENT_SINGLETON(CGraphicDev)

CGraphicDev::CGraphicDev()
	: m_pSDK(nullptr), m_pGraphicDev(nullptr)
{
}

CGraphicDev::~CGraphicDev()
{
	Free();
}

HRESULT CGraphicDev::Ready_GraphicDev(HWND hWnd,
										WINMODE eMode,
										const _uint & iSizeX,
										const _uint & iSizeY, 
										CGraphicDev ** ppGraphicDev)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_RETURN(m_pSDK, E_FAIL);

	D3DCAPS9				DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	FAILED_CHECK_RETURN(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps), E_FAIL);

	_ulong		dwFlag = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	else
		dwFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;


	D3DPRESENT_PARAMETERS				d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = iSizeX;
	d3dpp.BackBufferHeight = iSizeY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	
	d3dpp.Windowed = eMode;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	FAILED_CHECK_RETURN(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwFlag, &d3dpp, &m_pGraphicDev), E_FAIL);

	*ppGraphicDev = this;

	if(FAILED(D3DXCreateFont(m_pGraphicDev, 30, 10, 650, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"고딕", &m_pFont)))
	{
		MSG_BOX("Create Font Failed");
		return E_FAIL;
	}

	// 타이틀 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 30, 10, 650, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"Germania One", &m_pTitleFont)))
	{
		MSG_BOX("Create TitleFont Failed");
		return E_FAIL;
	}
	// 인게임 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 40, 22, 550, 1, false, DEFAULT_CHARSET, OUT_TT_PRECIS, ANTIALIASED_QUALITY, 0, L"CookieRun Bold", &m_pInGameFont)))
	{
		MSG_BOX("Create InGameFont Failed");
		return E_FAIL;
	}
	// 레벨UI 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 80, 30, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pLevelFont)))
	{
		MSG_BOX("Create LevelFont Failed");
		return E_FAIL;
	}

	// 스킬UI 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 60, 20, 500, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pSkillFont)))
	{
		MSG_BOX("Create SkillFont Failed");
		return E_FAIL;
	}

	// 이펙트 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 105, 0, 900, 1, false, DEFAULT_CHARSET, OUT_TT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pEffectFont1)))
	{
		MSG_BOX("Create EffectFont Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateFont(m_pGraphicDev, 92, 43, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pEffectFont2)))
	{
		MSG_BOX("Create EffectFont2 Failed");
		return E_FAIL;
	}

	// Xp 폰트
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 80, 0, 580, 1, false, DEFAULT_CHARSET, OUT_TT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pXpFont1)))
	{
		MSG_BOX("Create SkillFont Failed");
		return E_FAIL;
	}
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 70, 32, 0, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 0, L"Chela One", &m_pXpFont2)))
	{
		MSG_BOX("Create EffectFont2 Failed");
		return E_FAIL;
	}
	
	// 퀘스트 제목
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 25, 16, 550, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"CookieRun Bold", &m_pQuestTitleFont)))
	{
		MSG_BOX("Create QuestTitle Failed");
		return E_FAIL;
	}

	// 퀘스트 내용
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 20, 12, 550, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, L"CookieRun Bold", &m_pQuestContentFont)))
	{
		MSG_BOX("Create QuestContent Failed");
		return E_FAIL;
	}

	// 퀘스트 내용
	if (FAILED(D3DXCreateFont(m_pGraphicDev, 32, 14, 500, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Chela One", &m_pLevelUPFont)))
	{
		MSG_BOX("Create LevelUPFont Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicDev::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color, 1.f, 0);

	m_pGraphicDev->BeginScene();
}

void CGraphicDev::Render_End()
{
	m_pGraphicDev->EndScene();
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr); // 
}

void CGraphicDev::Free()
{
	_ulong	dwRefCnt = 0;

	if (dwRefCnt = Safe_Release(m_pFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pTitleFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pInGameFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pLevelFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pSkillFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pEffectFont1))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pEffectFont2))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pXpFont1))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pXpFont2))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pLevelUPFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pQuestTitleFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pQuestContentFont))
		MSG_BOX("m_pFont Release Failed");

	if (dwRefCnt = Safe_Release(m_pGraphicDev))
		MSG_BOX("m_pGraphicDev Release Failed");

	if (dwRefCnt = Safe_Release(m_pSDK))
		MSG_BOX("m_pSDK Release Failed");

}
