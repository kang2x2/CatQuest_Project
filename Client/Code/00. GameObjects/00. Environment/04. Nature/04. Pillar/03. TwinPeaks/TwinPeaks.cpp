#include "stdafx.h"
#include "..\Header\TwinPeaks.h"

#include "Export_Function.h"

CTwinPeaks::CTwinPeaks(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPillar(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_TWINPEAKS)
{
}

CTwinPeaks::CTwinPeaks(const CPillar& rhs)
	: CPillar(rhs)
{
}

CTwinPeaks::~CTwinPeaks()
{
}

HRESULT CTwinPeaks::Ready_Object()
{
	CPillar::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 10.f, 13.f, 13.f });
	m_pTransformCom->Set_Pos(_vec3{ 240.f, m_pTransformCom->Get_Scale().y - 1.f, 200.f });

	m_szName = L"TwinPeaks";

	return S_OK;
}

_int CTwinPeaks::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CTwinPeaks::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CTwinPeaks::Render_Object()
{
	__super::Render_Object();
}

void CTwinPeaks::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CTwinPeaks::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CTwinPeaks::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CTwinPeaks::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Pillar_TwinPeaks", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CTwinPeaks* CTwinPeaks::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTwinPeaks* pInstance = new CTwinPeaks(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("TwinPeaks Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CTwinPeaks::Free()
{
	__super::Free();
}
