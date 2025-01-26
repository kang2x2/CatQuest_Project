#include "stdafx.h"
#include "Rock1.h"

#include "Export_Function.h"

CRock1::CRock1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CRock(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_ROCK_1)
{
}

CRock1::CRock1(const CRock& rhs)
	: CRock(rhs)
{
}

CRock1::~CRock1()
{
}

HRESULT CRock1::Ready_Object()
{
	CRock::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.9f, 1.3f, 3.2f });
	m_pTransformCom->Set_Pos(_vec3{ 340.f, m_pTransformCom->Get_Scale().y, 94.f });

	m_eEnter = ENTER_TYPE::ENTER_NO;

	m_szName = L"Rock1";

	return S_OK;
}

_int CRock1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CRock1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock1::Render_Object()
{
	__super::Render_Object();
}

HRESULT CRock1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Rock1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	return S_OK;
}

CRock1* CRock1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRock1* pInstance = new CRock1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Rock1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRock1::Free()
{
	__super::Free();
}
