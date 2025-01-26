#include "stdafx.h"
#include "TripleDeathTree.h"

#include "Export_Function.h"

CTripleDeathTree::CTripleDeathTree(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTree(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_TRIPLE_DEATH_TREE)
{
}

CTripleDeathTree::CTripleDeathTree(const CTree& rhs)
	: CTree(rhs)
{
}

CTripleDeathTree::~CTripleDeathTree()
{
}

HRESULT CTripleDeathTree::Ready_Object()
{
	CTree::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 6.f, 4.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 195.f, m_pTransformCom->Get_Scale().y - 1.f, 210.f });

	m_szName = L"TripleDeathTree";

	return S_OK;
}

_int CTripleDeathTree::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTripleDeathTree::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTripleDeathTree::Render_Object()
{
	__super::Render_Object();
}

void CTripleDeathTree::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTripleDeathTree::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTripleDeathTree::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTripleDeathTree::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Triple_DeathTree", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTripleDeathTree* CTripleDeathTree::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTripleDeathTree* pInstance = new CTripleDeathTree(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TripleDeathTree Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTripleDeathTree::Free()
{
	__super::Free();
}
