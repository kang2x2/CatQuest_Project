#include "FogMgr.h"
#include "stdafx.h"
#include "Export_Function.h"

#include "EventMgr.h"

IMPLEMENT_SINGLETON(CFogMgr)

CFogMgr::CFogMgr()
{
	m_bReady = FALSE;
	ZeroMemory(&m_tLerpColor, sizeof(LERP_VEC3_INFO));
	ZeroMemory(&m_tLerpNear, sizeof(LERP_VEC3_INFO));
	ZeroMemory(&m_tLerpFar, sizeof(LERP_VEC3_INFO));

}

CFogMgr::~CFogMgr()
{
}

HRESULT CFogMgr::Ready_FogMgr(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	m_bReady = TRUE;

	m_pGraphicDev = _pGraphicDev;

	m_tLerpNear.fCurValue	= 40.f; 
	m_tLerpFar.fCurValue	= 130.f;
	m_tLerpColor.vCurVec	= _vec3{ 255.f, 255.f, 255.f };

	Set_Fog();
	
	return S_OK;
}

void CFogMgr::Update_FogMgr(const _float& fTimeDelta)
{
	m_tLerpColor.Update_Lerp(fTimeDelta);
	m_tLerpNear.Update_Lerp(fTimeDelta);
	m_tLerpFar.Update_Lerp(fTimeDelta);

	Set_Fog();
}


void CFogMgr::Start_Lerp_Near(const _float& _fTime, const _float& _fStart, const _float& _fEnd, const LERP_MODE& _eMode)
{
	m_tLerpNear.Init_Lerp(_eMode);
	m_tLerpNear.Set_Lerp(_fTime, _fStart, _fEnd);
}

void CFogMgr::Start_Lerp_Far(const _float& _fTime, const _float& _fStart, const _float& _fEnd, const LERP_MODE& _eMode)
{
	m_tLerpFar.Init_Lerp(_eMode);
	m_tLerpFar.Set_Lerp(_fTime, _fStart, _fEnd);
}


void CFogMgr::Set_Fog()
{
	float Start		= m_tLerpNear.fCurValue; // 40.f; 
	float End		= m_tLerpFar.fCurValue; //  130.f;

	FLOAT Density	= 0.5f;
	BOOL UseRange	= TRUE;
	DWORD Mode		= D3DFOG_LINEAR;
	int iAlpha		= 40;


	m_pGraphicDev->SetRenderState(D3DRS_FOGENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(iAlpha, (_int)m_tLerpColor.vCurVec.x, (_int)m_tLerpColor.vCurVec.y, (_int)m_tLerpColor.vCurVec.z));

	if (D3DFOG_LINEAR == Mode)
	{
		m_pGraphicDev->SetRenderState(D3DRS_FOGTABLEMODE, Mode); // D3DRS_FOGVERTEXMODE
		m_pGraphicDev->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
		m_pGraphicDev->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
	}
	else
	{
		m_pGraphicDev->SetRenderState(D3DRS_FOGTABLEMODE, Mode); // D3DRS_FOGVERTEXMODE
		m_pGraphicDev->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
	}

	if (UseRange)
		m_pGraphicDev->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}


void CFogMgr::Free()
{
	//__super::Free();
}
