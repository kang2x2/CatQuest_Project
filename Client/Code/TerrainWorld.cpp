#include "stdafx.h"
#include "..\Header\TerrainWorld.h"

#include "Export_Function.h"

CTerrainWorld::CTerrainWorld(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTerrain(pGraphicDev, OBJ_ID::TERRAIN_WORLD)
{
}

CTerrainWorld::CTerrainWorld(const CTerrain& rhs)
	: CTerrain(rhs)
{
}

CTerrainWorld::~CTerrainWorld()
{
}

HRESULT CTerrainWorld::Ready_Object(void)
{	
	/*--------------------- ! 수정이나 추가시 반드시 팀장 보고 !  ---------------------*/

	CTerrain::Ready_Object();

	//m_pTransformCom->Set_Scale(_vec3(100.f, 0.f, 100.f));
	//m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 10.f });

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3(TERRAIN_SIZE_WORLD, 0.f, TERRAIN_SIZE_WORLD));
	m_pTransformCom->Set_Pos(_vec3{ m_pTransformCom->Get_Scale().x,
									m_pTransformCom->Get_Scale().y,  
									m_pTransformCom->Get_Scale().z });
	
	m_szName = L"Terrain_World";

	return S_OK;
}

_int CTerrainWorld::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CTerrain::Update_Object(fTimeDelta);

	//Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return _int();
}

void CTerrainWorld::LateUpdate_Object(void)
{
	CTerrain::LateUpdate_Object();
}

void CTerrainWorld::Render_Object(void)
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	// m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	CTerrain::Render_Object();
	// m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CTerrainWorld::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Terrain_World", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTerrainWorld* CTerrainWorld::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainWorld* pInstance = new CTerrainWorld(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TerrainWorld Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrainWorld::Free()
{
	CTerrain::Free();
}
