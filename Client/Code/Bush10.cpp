#include "stdafx.h"
#include "Bush10.h"

#include "Export_Function.h"

CBush10::CBush10(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_10)
{
}

CBush10::CBush10(const CBush& rhs)
	: CBush(rhs)
{
}

CBush10::~CBush10()
{
}

HRESULT CBush10::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y, 50.f });

	m_vecInitScale = { 1.7f, 2.3f, 1.5f };
	m_vecEndScale = { 1.9f, 2.0f, 1.5f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"Bush10";

	return S_OK;
}

_int CBush10::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush10::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush10::Render_Object()
{
	CBush::Render_Object();
}

void CBush10::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush10::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush10::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush10::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush10", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush10* CBush10::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush10* pInstance = new CBush10(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush10 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush10::Free()
{
	CBush::Free();
}
