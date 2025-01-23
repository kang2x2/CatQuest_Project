#include "stdafx.h"
#include "SignAstropaw.h"

#include "Export_Function.h"

CSignAstropaw::CSignAstropaw(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_ASTROPAW)
{
}

CSignAstropaw::CSignAstropaw(const CSign& rhs)
	: CSign(rhs)
{
}

CSignAstropaw::~CSignAstropaw()
{
}

HRESULT CSignAstropaw::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 363.f, m_pTransformCom->Get_Scale().y, 123.f });

	m_szName = L"SignAstropaw";

	return S_OK;
}

_int CSignAstropaw::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignAstropaw::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignAstropaw::Render_Object()
{
	__super::Render_Object();
}

void CSignAstropaw::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignAstropaw::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignAstropaw::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignAstropaw::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Astropaw", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignAstropaw* CSignAstropaw::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignAstropaw* pInstance = new CSignAstropaw(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignAstropaw Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignAstropaw::Free()
{
	__super::Free();
}
