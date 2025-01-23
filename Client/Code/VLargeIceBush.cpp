#include "stdafx.h"
#include "VLargeIceBush.h"

#include "Export_Function.h"

CVLargeIceBush::CVLargeIceBush(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_VLARGE_ICE_BUSH)
{
}

CVLargeIceBush::CVLargeIceBush(const CBush& rhs)
	: CBush(rhs)
{
}

CVLargeIceBush::~CVLargeIceBush()
{
}

HRESULT CVLargeIceBush::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;
	m_eInterType = INTERACTION_TYPE::INTERACTION_ALPHA;

	m_bTransSwitch1 = false;
	m_bTransSwitch2 = false;
	m_iTranslucent = 255;

	m_pTransformCom->Set_Pos(_vec3{140.f,
		m_pTransformCom->Get_Scale().y + 2.5f,
		382.f });

	m_vecInitScale = { 7.32f, 5.15f, 1.f };
	m_vecEndScale = { 7.f, 4.7f, 1.f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"VLargeIceBush";

	m_iEndTranslucent = 100;

	return S_OK;
}

_int CVLargeIceBush::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CVLargeIceBush::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CVLargeIceBush::Render_Object()
{
	CBush::Render_Object();
}

void CVLargeIceBush::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CVLargeIceBush::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CVLargeIceBush::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CVLargeIceBush::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_VLarge_Ice_Bush", this));
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

CVLargeIceBush* CVLargeIceBush::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CVLargeIceBush* pInstance = new CVLargeIceBush(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("VLargeIceBush Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CVLargeIceBush::Free()
{
	CBush::Free();
}
