#include "stdafx.h"
#include "Rock_Pillar3.h"

#include "Export_Function.h"

CRock_Pillar3::CRock_Pillar3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPillar(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_PILLAR_ROCK_3)
{
}

CRock_Pillar3::CRock_Pillar3(const CPillar& rhs)
	: CPillar(rhs)
{
}

CRock_Pillar3::~CRock_Pillar3()
{
}

HRESULT CRock_Pillar3::Ready_Object()
{
	CPillar::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 5.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 30.f, m_pTransformCom->Get_Scale().y - 1.f, 80.f });
	
	m_szName = L"Rock_Pillar3";
	
	return S_OK;
}

_int CRock_Pillar3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CRock_Pillar3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock_Pillar3::Render_Object()
{
	__super::Render_Object();
}

void CRock_Pillar3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CRock_Pillar3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CRock_Pillar3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CRock_Pillar3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Rock_Pillar3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CRock_Pillar3* CRock_Pillar3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRock_Pillar3* pInstance = new CRock_Pillar3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Rock_Pillar3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRock_Pillar3::Free()
{
	__super::Free();
}
