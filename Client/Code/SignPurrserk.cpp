#include "stdafx.h"
#include "SignPurrserk.h"

#include "Export_Function.h"

CSignPurrserk::CSignPurrserk(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_PURRSERK)
{
}

CSignPurrserk::CSignPurrserk(const CSign& rhs)
	: CSign(rhs)
{
}

CSignPurrserk::~CSignPurrserk()
{
}

HRESULT CSignPurrserk::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 371.f, m_pTransformCom->Get_Scale().y, 118.f });

	m_szName = L"SignPurrserk";

	return S_OK;
}

_int CSignPurrserk::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignPurrserk::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignPurrserk::Render_Object()
{
	__super::Render_Object();
}

void CSignPurrserk::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignPurrserk::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignPurrserk::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignPurrserk::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Purrserk", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignPurrserk* CSignPurrserk::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignPurrserk* pInstance = new CSignPurrserk(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignPurrserk Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignPurrserk::Free()
{
	__super::Free();
}
