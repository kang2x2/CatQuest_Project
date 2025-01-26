#include "stdafx.h"
#include "SignLight.h"

#include "Export_Function.h"

CSignLight::CSignLight(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_LIGHT)
{
}

CSignLight::CSignLight(const CSign& rhs)
	: CSign(rhs)
{
}

CSignLight::~CSignLight()
{
}

HRESULT CSignLight::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 367.f, m_pTransformCom->Get_Scale().y, 118.f });

	m_szName = L"SignLight";

	return S_OK;
}

_int CSignLight::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignLight::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignLight::Render_Object()
{
	__super::Render_Object();
}

void CSignLight::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignLight::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignLight::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignLight::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Light", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignLight* CSignLight::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignLight* pInstance = new CSignLight(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignLight Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignLight::Free()
{
	__super::Free();
}
