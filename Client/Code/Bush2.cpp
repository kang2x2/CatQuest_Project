#include "stdafx.h"
#include "Bush2.h"

#include "Export_Function.h"

CBush2::CBush2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_2)
{
}

CBush2::CBush2(const CBush& rhs)
	: CBush(rhs)
{
}

CBush2::~CBush2()
{
}

HRESULT CBush2::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 70.f });

	m_szName = L"Bush2";

	return S_OK;
}

_int CBush2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush2::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush2::Render_Object()
{
	CBush::Render_Object();
}

void CBush2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush2* CBush2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush2* pInstance = new CBush2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush2::Free()
{
	CBush::Free();
}
