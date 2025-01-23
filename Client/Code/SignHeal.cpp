#include "stdafx.h"
#include "SignHeal.h"

#include "Export_Function.h"

CSignHeal::CSignHeal(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_HEAL)
{
}

CSignHeal::CSignHeal(const CSign& rhs)
	: CSign(rhs)
{
}

CSignHeal::~CSignHeal()
{
}

HRESULT CSignHeal::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 363.f, m_pTransformCom->Get_Scale().y, 118.f });

	m_szName = L"SignHeal";

	return S_OK;
}

_int CSignHeal::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignHeal::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignHeal::Render_Object()
{
	__super::Render_Object();
}

void CSignHeal::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignHeal::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignHeal::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignHeal::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Heal", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignHeal* CSignHeal::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignHeal* pInstance = new CSignHeal(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignHeal Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignHeal::Free()
{
	__super::Free();
}
