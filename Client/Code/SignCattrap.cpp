#include "stdafx.h"
#include "SignCattrap.h"

#include "Export_Function.h"

CSignCattrap::CSignCattrap(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_CATTRAP)
{
}

CSignCattrap::CSignCattrap(const CSign& rhs)
	: CSign(rhs)
{
}

CSignCattrap::~CSignCattrap()
{
}

HRESULT CSignCattrap::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 367.f, m_pTransformCom->Get_Scale().y, 123.f });

	m_szName = L"SignCattrap";

	return S_OK;
}

_int CSignCattrap::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignCattrap::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignCattrap::Render_Object()
{
	__super::Render_Object();
}

void CSignCattrap::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignCattrap::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignCattrap::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignCattrap::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Cattrap", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignCattrap* CSignCattrap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignCattrap* pInstance = new CSignCattrap(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignCattrap Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignCattrap::Free()
{
	__super::Free();
}
