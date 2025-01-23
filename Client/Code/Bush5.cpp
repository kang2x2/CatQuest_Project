#include "stdafx.h"
#include "Bush5.h"

#include "Export_Function.h"

CBush5::CBush5(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_5)
{
}

CBush5::CBush5(const CBush& rhs)
	: CBush(rhs)
{
}

CBush5::~CBush5()
{
}

HRESULT CBush5::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 60.f });

	m_szName = L"Bush5";

	return S_OK;
}

_int CBush5::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush5::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush5::Render_Object()
{
	CBush::Render_Object();
}

void CBush5::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush5::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush5::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush5::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush5", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush5* CBush5::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush5* pInstance = new CBush5(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush5 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush5::Free()
{
	CBush::Free();
}
