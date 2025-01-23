#include "stdafx.h"
#include "Dungeon_Ice.h"

#include "Export_Function.h"

CDungeon_Ice::CDungeon_Ice(LPDIRECT3DDEVICE9 pGraphicDev)
	: CDungeon(pGraphicDev, OBJ_ID::ENVIRONMENT_ENTERANCE_DUNGEON_ICE)
{
}

CDungeon_Ice::CDungeon_Ice(const CDungeon& rhs)
	: CDungeon(rhs)
{
}

CDungeon_Ice::~CDungeon_Ice()
{
}

HRESULT CDungeon_Ice::Ready_Object()
{
	CDungeon::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 80.f });	

	m_szName = L"Dungeon_Ice";

	return S_OK;
}

_int CDungeon_Ice::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDungeon_Ice::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDungeon_Ice::Render_Object()
{
	__super::Render_Object();
}

void CDungeon_Ice::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDungeon_Ice::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDungeon_Ice::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDungeon_Ice::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Dungeon_Ice", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDungeon_Ice* CDungeon_Ice::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDungeon_Ice* pInstance = new CDungeon_Ice(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Dungeon_Ice Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDungeon_Ice::Free()
{
	__super::Free();
}
