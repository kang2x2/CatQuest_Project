#include "stdafx.h"
#include "LargeIceBush.h"

#include "Export_Function.h"

CLargeIceBush::CLargeIceBush(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_LARGE_ICE_BUSH)
{
}

CLargeIceBush::CLargeIceBush(const CBush& rhs)
	: CBush(rhs)
{
}

CLargeIceBush::~CLargeIceBush()
{
}

HRESULT CLargeIceBush::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;
	m_eInterType = INTERACTION_TYPE::INTERACTION_ALPHA;

	m_bTransSwitch1 = false;
	m_bTransSwitch2 = false;
	m_iTranslucent = 255;

	m_pTransformCom->Set_Pos(_vec3{ 151.f,
		m_pTransformCom->Get_Scale().y + 2.5f,
		386.f});

	m_vecInitScale = { 5.f, 3.84f, 1.f };
	m_vecEndScale = { 4.7f, 3.54f, 1.f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"LargeIceBush";

	return S_OK;
}

_int CLargeIceBush::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CLargeIceBush::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CLargeIceBush::Render_Object()
{
	CBush::Render_Object();
}

void CLargeIceBush::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CLargeIceBush::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CLargeIceBush::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CLargeIceBush::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Large_Ice_Bush", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Rc Texture
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	// Rect Collider
	pComponent = m_pColliderCom = dynamic_cast<CRectCollider*>(Engine::Clone_Proto(COMPONENT_TYPE::COL_RECT, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::COL_RECT, pComponent);


	return S_OK;
}

CLargeIceBush* CLargeIceBush::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLargeIceBush* pInstance = new CLargeIceBush(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("LargeIceBush Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLargeIceBush::Free()
{
	CBush::Free();
}
