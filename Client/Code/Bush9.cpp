#include "stdafx.h"
#include "Bush9.h"

#include "Export_Function.h"

CBush9::CBush9(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_9)
{
}

CBush9::CBush9(const CBush& rhs)
	: CBush(rhs)
{
}

CBush9::~CBush9()
{
}

HRESULT CBush9::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 70.f, m_pTransformCom->Get_Scale().y, 50.f });

	m_szName = L"Bush9";

	return S_OK;
}

_int CBush9::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush9::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush9::Render_Object()
{
	CBush::Render_Object();
}

void CBush9::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush9::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush9::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush9::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush9", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush9* CBush9::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush9* pInstance = new CBush9(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush9 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush9::Free()
{
	CBush::Free();
}
