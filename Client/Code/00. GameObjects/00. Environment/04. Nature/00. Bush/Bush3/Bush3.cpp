#include "stdafx.h"
#include "Bush3.h"

#include "Export_Function.h"

CBush3::CBush3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_3)
{
}

CBush3::CBush3(const CBush& rhs)
	: CBush(rhs)
{
}

CBush3::~CBush3()
{
}

HRESULT CBush3::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y, 70.f });

	m_szName = L"Bush3";

	return S_OK;
}

_int CBush3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush3::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush3::Render_Object()
{
	CBush::Render_Object();
}

void CBush3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush3* CBush3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush3* pInstance = new CBush3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush3::Free()
{
	CBush::Free();
}
