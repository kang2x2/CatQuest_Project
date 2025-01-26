#include "stdafx.h"
#include "Bush7.h"

#include "Export_Function.h"

CBush7::CBush7(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_7)
{
}

CBush7::CBush7(const CBush& rhs)
	: CBush(rhs)
{
}

CBush7::~CBush7()
{
}

HRESULT CBush7::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 90.f, m_pTransformCom->Get_Scale().y, 60.f });

	m_vecInitScale = { 2.7f, 2.0f, 1.5f };
	m_vecEndScale = { 2.9f, 1.8f, 1.5f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"Bush7";

	return S_OK;
}

_int CBush7::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush7::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush7::Render_Object()
{
	CBush::Render_Object();
}

void CBush7::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush7::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush7::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush7::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush7", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush7* CBush7::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush7* pInstance = new CBush7(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush7 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush7::Free()
{
	CBush::Free();
}
