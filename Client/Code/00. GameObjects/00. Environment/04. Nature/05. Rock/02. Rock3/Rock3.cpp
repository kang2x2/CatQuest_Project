#include "stdafx.h"
#include "Rock3.h"

#include "Export_Function.h"

CRock3::CRock3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CRock(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_ROCK_3)
{
}

CRock3::CRock3(const CRock& rhs)
	: CRock(rhs)
{
}

CRock3::~CRock3()
{
}

HRESULT CRock3::Ready_Object()
{
	CRock::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 0.5f, 0.27f, 0.5f });
	m_pTransformCom->Set_Pos(_vec3{ 360.f, m_pTransformCom->Get_Scale().y, 88.f });

	m_eEnter = ENTER_TYPE::ENTER;

	m_szName = L"Rock3";

	return S_OK;
}

_int CRock3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CRock3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CRock3::Render_Object()
{
	__super::Render_Object();
}

HRESULT CRock3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Rock3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CRock3* CRock3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRock3* pInstance = new CRock3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Rock3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CRock3::Free()
{
	__super::Free();
}
