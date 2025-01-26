#include "stdafx.h"
#include "Sweets1.h"

#include "Export_Function.h"

CSweets1::CSweets1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSweets(pGraphicDev, OBJ_ID::ENVIRONMENT_OTHER_SWEETS1)
{
}

CSweets1::CSweets1(const CSweets& rhs)
	: CSweets(rhs)
{
}

CSweets1::~CSweets1()
{
}

HRESULT CSweets1::Ready_Object()
{
	CSweets::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.f, 1.f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 220.f , m_pTransformCom->Get_Scale().y, 210.f });

	m_szName = L"Sweets1";

	return S_OK;
}

_int CSweets1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSweets1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSweets1::Render_Object()
{
	__super::Render_Object();
}

HRESULT CSweets1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sweets1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSweets1* CSweets1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSweets1* pInstance = new CSweets1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Sweets1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSweets1::Free()
{
	__super::Free();
}
