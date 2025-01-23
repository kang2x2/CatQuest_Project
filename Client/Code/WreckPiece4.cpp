#include "stdafx.h"
#include "WreckPiece4.h"

#include "Export_Function.h"

CWreckPiece4::CWreckPiece4(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWreck(pGraphicDev, OBJ_ID::ENVIRONMENT_WRECK_PIECE4)
{
}

CWreckPiece4::CWreckPiece4(const CWreck& rhs)
	: CWreck(rhs)
{
}

CWreckPiece4::~CWreckPiece4()
{
}

HRESULT CWreckPiece4::Ready_Object()
{
	CWreck::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 2.f, 0.5f, 1.f });
	m_pTransformCom->Set_Pos(_vec3{ 330.f, m_pTransformCom->Get_Scale().y, 36.f });

	m_szName = L"WreckPiece4";

	return S_OK;
}

_int CWreckPiece4::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CWreckPiece4::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CWreckPiece4::Render_Object()
{
	__super::Render_Object();
}

void CWreckPiece4::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWreckPiece4::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CWreckPiece4::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CWreckPiece4::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Wreck_Piece4", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CWreckPiece4* CWreckPiece4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWreckPiece4* pInstance = new CWreckPiece4(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WreckPiece4 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CWreckPiece4::Free()
{
	__super::Free();
}
