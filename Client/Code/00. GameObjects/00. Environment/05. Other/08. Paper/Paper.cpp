#include "stdafx.h"
#include "Paper.h"

#include "Export_Function.h"

CPaper::CPaper(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEnvironment(pGraphicDev, OBJ_ID::ENVIRONMENT_OTHER_PAPER)
{
}

CPaper::CPaper(const CPaper& rhs)
	: CEnvironment(rhs)
{
}

CPaper::~CPaper()
{
}

HRESULT CPaper::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;

	m_pTransformCom->Set_Scale(_vec3{ 0.8f, 0.8f, 0.8f });
	m_pTransformCom->Set_Pos(_vec3{ 317.f, m_pTransformCom->Get_Scale().y, 105.f });

	m_szName = L"Paper";

	return S_OK;
}

_int CPaper::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CPaper::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CPaper::Render_Object()
{
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEnvironment::Render_Object();
}

void CPaper::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CPaper::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CPaper::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CPaper::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Other_Paper", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CPaper* CPaper::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPaper* pInstance = new CPaper(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Paper Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPaper::Free()
{
	__super::Free();
}
