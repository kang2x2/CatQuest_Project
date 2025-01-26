#include "stdafx.h"
#include "SignFreeze.h"

#include "Export_Function.h"

CSignFreeze::CSignFreeze(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_FREEZE)
{
}

CSignFreeze::CSignFreeze(const CSign& rhs)
	: CSign(rhs)
{
}

CSignFreeze::~CSignFreeze()
{
}

HRESULT CSignFreeze::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 375.f, m_pTransformCom->Get_Scale().y, 123.f });

	m_szName = L"SignFreeze";

	return S_OK;
}

_int CSignFreeze::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignFreeze::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignFreeze::Render_Object()
{
	__super::Render_Object();
}

void CSignFreeze::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignFreeze::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignFreeze::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignFreeze::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Freeze", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignFreeze* CSignFreeze::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignFreeze* pInstance = new CSignFreeze(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignFreeze Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignFreeze::Free()
{
	__super::Free();
}
