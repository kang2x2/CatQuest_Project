#include "stdafx.h"
#include "..\Header\Terrain_World.h"

#include "Export_Function.h"

CTerrain_World::CTerrain_World(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTerrain(pGraphicDev)
{
}

CTerrain_World::CTerrain_World(const CTerrain& rhs)
	: CTerrain(rhs)
{
}

CTerrain_World::~CTerrain_World()
{
}

HRESULT CTerrain_World::Ready_Object(void)
{
	return E_NOTIMPL;
}

_int CTerrain_World::Update_Object(const _float& fTimeDelta)
{
	return _int();
}

void CTerrain_World::LateUpdate_Object(void)
{
}

void CTerrain_World::Render_Object(void)
{
}

HRESULT CTerrain_World::Add_Component()
{
	return E_NOTIMPL;
}

CTerrain_World* CTerrain_World::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return nullptr;
}

void CTerrain_World::Free()
{
}
