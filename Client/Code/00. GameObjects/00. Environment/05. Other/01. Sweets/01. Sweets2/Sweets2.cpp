#include "stdafx.h"
#include "Sweets2.h"

#include "Export_Function.h"

CSweets2::CSweets2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSweets(pGraphicDev, OBJ_ID::ENVIRONMENT_OTHER_SWEETS1)
{
}

CSweets2::CSweets2(const CSweets& rhs)
	: CSweets(rhs)
{
}

CSweets2::~CSweets2()
{
}

HRESULT CSweets2::Ready_Object()
{
	CSweets::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 215.f , m_pTransformCom->Get_Scale().y, 210.f });

	m_szName = L"Sweets2";

	return S_OK;
}

_int CSweets2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSweets2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSweets2::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSweets2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sweets2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSweets2* CSweets2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSweets2* pInstance = new CSweets2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Sweets2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSweets2::Free()
{
	__super::Free();
}
