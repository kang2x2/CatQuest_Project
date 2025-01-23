#include "stdafx.h"
#include "Bush6.h"

#include "Export_Function.h"

CBush6::CBush6(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_6)
{
}

CBush6::CBush6(const CBush& rhs)
	: CBush(rhs)
{
}

CBush6::~CBush6()
{
}

HRESULT CBush6::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y, 60.f });

	m_szName = L"Bush6";

	return S_OK;
}

_int CBush6::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush6::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush6::Render_Object()
{
	CBush::Render_Object();
}

void CBush6::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush6::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush6::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush6::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush6", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush6* CBush6::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush6* pInstance = new CBush6(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush6 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush6::Free()
{
	CBush::Free();
}
