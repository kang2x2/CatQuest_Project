#include "stdafx.h"
#include "Rock2.h"

#include "Export_Function.h"

CRock2::CRock2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CRock(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_ROCK_2)
{
}

CRock2::CRock2(const CRock& rhs)
	: CRock(rhs)
{
}

CRock2::~CRock2()
{
}

HRESULT CRock2::Ready_Object()
{
	CRock::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 0.86f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 360.f, m_pTransformCom->Get_Scale().y, 94.f });

	m_szName = L"Rock2";

	return S_OK;
}

_int CRock2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CRock2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock2::Render_Object()
{
	__super::Render_Object();
}

HRESULT CRock2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Rock2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	m_eEnter = ENTER_TYPE::ENTER;

	return S_OK;
}

CRock2* CRock2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRock2* pInstance = new CRock2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Rock2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRock2::Free()
{
	__super::Free();
}
