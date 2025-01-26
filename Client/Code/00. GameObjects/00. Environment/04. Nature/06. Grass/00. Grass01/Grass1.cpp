#include "stdafx.h"
#include "Grass1.h"

#include "Export_Function.h"

CGrass1::CGrass1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGrass(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURE_GRASS)
{
}

CGrass1::CGrass1(const CGrass& rhs)
	: CGrass(rhs)
{
}

CGrass1::~CGrass1()
{
}

HRESULT CGrass1::Ready_Object()
{
	CGrass::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 200.f, m_pTransformCom->Get_Scale().y - 1.f , 195.f });

	m_szName = L"Grass1";

	return S_OK;
}

_int CGrass1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CGrass1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CGrass1::Render_Object()
{
	__super::Render_Object();
}

HRESULT CGrass1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Grass1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CGrass1* CGrass1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGrass1* pInstance = new CGrass1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Grass1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CGrass1::Free()
{
	__super::Free();
}
