#include "stdafx.h"
#include "Wall1.h"

#include "Export_Function.h"

CWall1::CWall1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWall(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_WALL1)
{
}

CWall1::CWall1(const CWall& rhs)
	: CWall(rhs)
{
}

CWall1::~CWall1()
{
}

HRESULT CWall1::Ready_Object()
{
	CWall::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 320.f, m_pTransformCom->Get_Scale().y, 140.f });

	m_szName = L"Wall1";

	return S_OK;
}

_int CWall1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWall1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWall1::Render_Object()
{
	__super::Render_Object();
}

void CWall1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWall1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWall1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWall1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wall1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWall1* CWall1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWall1* pInstance = new CWall1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Wall1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWall1::Free()
{
	__super::Free();
}
