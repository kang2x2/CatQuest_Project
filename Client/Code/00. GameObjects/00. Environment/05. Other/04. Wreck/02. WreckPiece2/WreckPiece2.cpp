#include "stdafx.h"
#include "WreckPiece2.h"

#include "Export_Function.h"

CWreckPiece2::CWreckPiece2(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWreck(pGraphicDev, OBJ_ID::ENVIRONMENT_WRECK_PIECE2)
{
}

CWreckPiece2::CWreckPiece2(const CWreck& rhs)
	: CWreck(rhs)
{
}

CWreckPiece2::~CWreckPiece2()
{
}

HRESULT CWreckPiece2::Ready_Object()
{
	CWreck::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 0.5f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 318.f, m_pTransformCom->Get_Scale().y, 50.f });

	m_szName = L"WreckPiece2";

	return S_OK;
}

_int CWreckPiece2::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWreckPiece2::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWreckPiece2::Render_Object()
{
	__super::Render_Object();
}

void CWreckPiece2::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWreckPiece2::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWreckPiece2::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWreckPiece2::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wreck_Piece2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWreckPiece2* CWreckPiece2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWreckPiece2* pInstance = new CWreckPiece2(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WreckPiece2 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWreckPiece2::Free()
{
	__super::Free();
}
