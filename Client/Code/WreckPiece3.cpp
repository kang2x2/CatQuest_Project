#include "stdafx.h"
#include "WreckPiece3.h"

#include "Export_Function.h"

CWreckPiece3::CWreckPiece3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWreck(pGraphicDev, OBJ_ID::ENVIRONMENT_WRECK_PIECE3)
{
}

CWreckPiece3::CWreckPiece3(const CWreck& rhs)
	: CWreck(rhs)
{
}

CWreckPiece3::~CWreckPiece3()
{
}

HRESULT CWreckPiece3::Ready_Object()
{
	CWreck::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 325.f, m_pTransformCom->Get_Scale().y, 36.f });

	m_szName = L"WreckPiece3";

	return S_OK;
}

_int CWreckPiece3::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWreckPiece3::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWreckPiece3::Render_Object()
{
	__super::Render_Object();
}

void CWreckPiece3::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWreckPiece3::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWreckPiece3::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWreckPiece3::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wreck_Piece3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWreckPiece3* CWreckPiece3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWreckPiece3* pInstance = new CWreckPiece3(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WreckPiece3 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWreckPiece3::Free()
{
	__super::Free();
}
