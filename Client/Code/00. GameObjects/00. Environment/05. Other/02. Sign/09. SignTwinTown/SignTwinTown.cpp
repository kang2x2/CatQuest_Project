#include "stdafx.h"
#include "SignTwinTown.h"

#include "Export_Function.h"

CSignTwinTown::CSignTwinTown(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_TWINTOWN)
{
}

CSignTwinTown::CSignTwinTown(const CSign& rhs)
	: CSign(rhs)
{
}

CSignTwinTown::~CSignTwinTown()
{
}

HRESULT CSignTwinTown::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 363.f, m_pTransformCom->Get_Scale().y, 113.f });

	m_szName = L"SignTwinTown";

	return S_OK;
}

_int CSignTwinTown::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignTwinTown::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignTwinTown::Render_Object()
{
	__super::Render_Object();
}

void CSignTwinTown::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignTwinTown::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignTwinTown::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignTwinTown::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_TwinTown", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignTwinTown* CSignTwinTown::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignTwinTown* pInstance = new CSignTwinTown(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignTwinTown Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignTwinTown::Free()
{
	__super::Free();
}
