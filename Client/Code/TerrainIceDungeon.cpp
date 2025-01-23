#include "stdafx.h"
#include "../Header/TerrainIceDungeon.h"

#include "Export_Function.h"

CTerrainIceDungeon::CTerrainIceDungeon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTerrain(pGraphicDev, OBJ_ID::TERRAIN_ICEWORLD)
{
	m_bTool = false;
}

CTerrainIceDungeon::CTerrainIceDungeon(const CTerrain& rhs)
	: CTerrain(rhs)
{
}

CTerrainIceDungeon::~CTerrainIceDungeon()
{
}

HRESULT CTerrainIceDungeon::Ready_Object(void)
{
	CTerrain::Ready_Object();

	//m_pTransformCom->Set_Scale(_vec3(100.f, 0.f, 100.f));
	//m_pTransformCom->Set_Pos(_vec3{ VTXCNTX / 2.f, m_pTransformCom->Get_Scale().y, 10.f });

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 100.f, 
										0.f, 
										100.f });

	m_pTransformCom->Set_Pos(_vec3{ m_pTransformCom->Get_Scale().x,
									m_pTransformCom->Get_Scale().y,
									m_pTransformCom->Get_Scale().z });

	m_szName = L"TerrainDungeon_Ice";

	return S_OK;

}

_int CTerrainIceDungeon::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CTerrain::Update_Object(fTimeDelta);

	return iExit;
}

void CTerrainIceDungeon::LateUpdate_Object(void)
{
	CTerrain::LateUpdate_Object();
}

void CTerrainIceDungeon::Render_Object(void)
{
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	CTerrain::Render_Object();
}

HRESULT CTerrainIceDungeon::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Terrain_ID", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTerrainIceDungeon* CTerrainIceDungeon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrainIceDungeon* pInstance = new CTerrainIceDungeon(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TerrainIceWorld Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTerrainIceDungeon::Free()
{
	CTerrain::Free();
}
