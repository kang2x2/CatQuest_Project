#include "stdafx.h"
#include "WorldTree.h"

#include "Export_Function.h"

CWorldTree::CWorldTree(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTree(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_WORLD_TREE)
{
}

CWorldTree::CWorldTree(const CTree& rhs)
	: CTree(rhs)
{
}

CWorldTree::~CWorldTree()
{
}

HRESULT CWorldTree::Ready_Object()
{
	CTree::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 10.f, 10.f, 10.f });
	m_pTransformCom->Set_Pos(_vec3{ 190.f, m_pTransformCom->Get_Scale().y - 1.f, 160.f });

	m_szName = L"WorldTree";

	return S_OK;
}

_int CWorldTree::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWorldTree::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWorldTree::Render_Object()
{
	__super::Render_Object();
}

void CWorldTree::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWorldTree::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWorldTree::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWorldTree::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_World_Tree", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWorldTree* CWorldTree::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWorldTree* pInstance = new CWorldTree(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WorldTree Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWorldTree::Free()
{
	__super::Free();
}
