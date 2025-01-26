#include "stdafx.h"
#include "Wall2.h"

#include "Export_Function.h"

CWall2::CWall2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWall(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_WALL2)
{
}

CWall2::CWall2(const CWall& rhs)
	: CWall(rhs)
{
}

CWall2::~CWall2()
{
}

HRESULT CWall2::Ready_Object()
{
	CWall::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });
	m_pTransformCom->Set_Pos(_vec3{ 310.f, m_pTransformCom->Get_Scale().y, 140.f });

	m_szName = L"Wall2";

	return S_OK;
}

_int CWall2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWall2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWall2::Render_Object()
{
	__super::Render_Object();
}

void CWall2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWall2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWall2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWall2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wall2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWall2* CWall2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWall2* pInstance = new CWall2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Wall2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWall2::Free()
{
	__super::Free();
}
