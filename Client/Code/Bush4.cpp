#include "stdafx.h"
#include "Bush4.h"

#include "Export_Function.h"

CBush4::CBush4(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_4)
{
}

CBush4::CBush4(const CBush& rhs)
	: CBush(rhs)
{
}

CBush4::~CBush4()
{
}

HRESULT CBush4::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 60.f, m_pTransformCom->Get_Scale().y, 60.f });

	m_vecInitScale = { 1.7f, 2.3f, 1.5f };
	m_vecEndScale = { 1.9f, 2.0f, 1.5f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"Bush4";

	return S_OK;
}

_int CBush4::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush4::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush4::Render_Object()
{
	CBush::Render_Object();
}

void CBush4::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush4::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush4::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush4::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush4", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush4* CBush4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush4* pInstance = new CBush4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush4 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush4::Free()
{
	CBush::Free();
}
