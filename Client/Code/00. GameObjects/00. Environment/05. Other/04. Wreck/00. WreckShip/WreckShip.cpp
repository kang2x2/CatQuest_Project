#include "stdafx.h"
#include "WreckShip.h"

#include "Export_Function.h"

CWreckShip::CWreckShip(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWreck(pGraphicDev, OBJ_ID::ENVIRONMENT_WRECK_SHIP)
{
}

CWreckShip::CWreckShip(const CWreck& rhs)
	: CWreck(rhs)
{
}

CWreckShip::~CWreckShip()
{
}

HRESULT CWreckShip::Ready_Object()
{
	CWreck::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 4.5f, 4.5f, 4.5f });
	m_pTransformCom->Set_Pos(_vec3{ 320.f, m_pTransformCom->Get_Scale().y, 36.f });

	m_szName = L"WreckShip";

	return S_OK;
}

_int CWreckShip::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWreckShip::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWreckShip::Render_Object()
{
	__super::Render_Object();
}

void CWreckShip::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWreckShip::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWreckShip::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWreckShip::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wreck_Ship", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWreckShip* CWreckShip::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWreckShip* pInstance = new CWreckShip(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WreckShip Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWreckShip::Free()
{
	__super::Free();
}
