#include "stdafx.h"
#include "Bush8.h"

#include "Export_Function.h"

CBush8::CBush8(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBush(pGraphicDev, OBJ_ID::ENVIRONMENT_NATURAL_BUSH_8)
{
}

CBush8::CBush8(const CBush& rhs)
	: CBush(rhs)
{
}

CBush8::~CBush8()
{
}

HRESULT CBush8::Ready_Object()
{
	CBush::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 100.f, m_pTransformCom->Get_Scale().y, 50.f });

	m_vecInitScale = { 4.6f, 3.5f, 3.5f };
	m_vecEndScale = { 4.8f, 3.3f, 3.5f };

	m_pTransformCom->Set_Scale(m_vecInitScale);

	m_szName = L"Bush8";

	return S_OK;
}

_int CBush8::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CBush::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CBush8::LateUpdate_Object()
{
	CBush::LateUpdate_Object();
}

void CBush8::Render_Object()
{
	CBush::Render_Object();
}

void CBush8::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CBush8::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CBush8::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CBush8::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Bush8", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CBush8* CBush8::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBush8* pInstance = new CBush8(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Bush8 Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBush8::Free()
{
	CBush::Free();
}
