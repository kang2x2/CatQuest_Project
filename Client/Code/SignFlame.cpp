#include "stdafx.h"
#include "SignFlame.h"

#include "Export_Function.h"

CSignFlame::CSignFlame(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_FALME)
{
}

CSignFlame::CSignFlame(const CSign& rhs)
	: CSign(rhs)
{
}

CSignFlame::~CSignFlame()
{
}

HRESULT CSignFlame::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 371.f, m_pTransformCom->Get_Scale().y, 123.f });

	m_szName = L"SignFlame";

	return S_OK;
}

_int CSignFlame::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignFlame::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignFlame::Render_Object()
{
	__super::Render_Object();
}

void CSignFlame::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignFlame::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignFlame::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignFlame::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Flame", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignFlame* CSignFlame::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignFlame* pInstance = new CSignFlame(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignFlame Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignFlame::Free()
{
	__super::Free();
}
