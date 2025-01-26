#include "stdafx.h"
#include "WreckPiece1.h"

#include "Export_Function.h"

CWreckPiece1::CWreckPiece1(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWreck(pGraphicDev, OBJ_ID::ENVIRONMENT_WRECK_PIECE1)
{
}

CWreckPiece1::CWreckPiece1(const CWreck& rhs)
	: CWreck(rhs)
{
}

CWreckPiece1::~CWreckPiece1()
{
}

HRESULT CWreckPiece1::Ready_Object()
{
	CWreck::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 312.f, m_pTransformCom->Get_Scale().y, 50.f });

	m_szName = L"WreckPiece1";

	return S_OK;
}

_int CWreckPiece1::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWreckPiece1::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWreckPiece1::Render_Object()
{
	__super::Render_Object();
}

void CWreckPiece1::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWreckPiece1::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWreckPiece1::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWreckPiece1::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wreck_Piece1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWreckPiece1* CWreckPiece1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWreckPiece1* pInstance = new CWreckPiece1(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WreckPiece1 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWreckPiece1::Free()
{
	__super::Free();
}
