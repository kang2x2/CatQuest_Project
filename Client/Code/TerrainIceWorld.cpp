#include "stdafx.h"
#include "..\Header\TerrainIceWorld.h"

#include "Export_Function.h"

CTerrainIceWorld::CTerrainIceWorld(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTerrain(pGraphicDev, OBJ_ID::TERRAIN_ICEWORLD)
{
	m_bTool = false;
}

CTerrainIceWorld::CTerrainIceWorld(const CTerrain& rhs)
	: CTerrain(rhs)
{
}

CTerrainIceWorld::~CTerrainIceWorld()
{
}

HRESULT CTerrainIceWorld::Ready_Object(void)
{
	CTerrain::Ready_Object();

	//m_pTransformCom->Set_Scale(_vec3(100.f, 0.f, 100.f));
	//m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 10.f });

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3(100.f, 0.f, 100.f));
	m_pTransformCom->Set_Pos(_vec3{ m_pTransformCom->Get_Scale().x,
									m_pTransformCom->Get_Scale().y,
									m_pTransformCom->Get_Scale().z });

	m_szName = L"TerrainWorld_Ice";

	return S_OK;

}

_int CTerrainIceWorld::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CTerrain::Update_Object(fTimeDelta);

	return iExit;
}

void CTerrainIceWorld::LateUpdate_Object(void)
{
	CTerrain::LateUpdate_Object();
}

void CTerrainIceWorld::Render_Object(void)
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	CTerrain::Render_Object();
}

HRESULT CTerrainIceWorld::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Terrain_IW", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTerrainIceWorld* CTerrainIceWorld::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainIceWorld* pInstance = new CTerrainIceWorld(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TerrainIceWorld Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrainIceWorld::Free()
{
	CTerrain::Free();
}
