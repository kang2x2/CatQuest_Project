#include "stdafx.h"
#include "SignWoodFish.h"

#include "Export_Function.h"

CSignWoodFish::CSignWoodFish(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_WOODFISH)
{
}

CSignWoodFish::CSignWoodFish(const CSign& rhs)
	: CSign(rhs)
{
}

CSignWoodFish::~CSignWoodFish()
{
}

HRESULT CSignWoodFish::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 371.f, m_pTransformCom->Get_Scale().y, 113.f });

	m_szName = L"SignWoodFish";

	return S_OK;
}

_int CSignWoodFish::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignWoodFish::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignWoodFish::Render_Object()
{
	__super::Render_Object();
}

void CSignWoodFish::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignWoodFish::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignWoodFish::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignWoodFish::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_WoodFish", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignWoodFish* CSignWoodFish::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignWoodFish* pInstance = new CSignWoodFish(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignWoodFish Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignWoodFish::Free()
{
	__super::Free();
}
