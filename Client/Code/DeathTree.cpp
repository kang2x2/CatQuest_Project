#include "stdafx.h"
#include "DeathTree.h"

#include "Export_Function.h"

CDeathTree::CDeathTree(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTree(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_DEATH_TREE)
{
}

CDeathTree::CDeathTree(const CTree& rhs)
	: CTree(rhs)
{
}

CDeathTree::~CDeathTree()
{
}

HRESULT CDeathTree::Ready_Object()
{
	CTree::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 4.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 190.f, m_pTransformCom->Get_Scale().y - 1.f, 200.f });
	
	m_szName = L"DeathTree";

	return S_OK;
}

_int CDeathTree::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CDeathTree::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CDeathTree::Render_Object()
{
	__super::Render_Object();
}

void CDeathTree::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CDeathTree::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CDeathTree::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CDeathTree::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_DeathTree", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CDeathTree* CDeathTree::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDeathTree* pInstance = new CDeathTree(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("DeathTree Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CDeathTree::Free()
{
	__super::Free();
}
