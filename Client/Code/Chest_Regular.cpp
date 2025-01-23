#include "stdafx.h"
#include "Chest_Regular.h"

#include "Export_Function.h"

CChest_Regular::CChest_Regular(LPDIRECT3DDEVICE9 pGraphicDev)
	: CChest(pGraphicDev, OBJ_ID::ENVIRONMENT_CHEST__REGULAR)
{
}

CChest_Regular::CChest_Regular(const CChest& rhs)
	: CChest(rhs)
{
}

CChest_Regular::~CChest_Regular()
{
}

HRESULT CChest_Regular::Ready_Object()
{
	CChest::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_INSPECT;

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 100.f , m_pTransformCom->Get_Scale().y, 80.f });

	m_szName = L"Regular_Chest";

	return S_OK;
}

_int CChest_Regular::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CChest::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CChest_Regular::LateUpdate_Object()
{
	CChest::LateUpdate_Object();
}

void CChest_Regular::Render_Object()
{
	CChest::Render_Object();
}

void CChest_Regular::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CChest_Regular::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CChest_Regular::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CChest_Regular::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Regular_Chest", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CChest_Regular* CChest_Regular::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CChest_Regular* pInstance = new CChest_Regular(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Chest_Regular Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CChest_Regular::Free()
{
	CChest::Free();
}
