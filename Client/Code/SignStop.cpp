#include "stdafx.h"
#include "SignStop.h"

#include "Export_Function.h"

CSignStop::CSignStop(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_STOP)
{
}

CSignStop::CSignStop(const CSign& rhs)
	: CSign(rhs)
{
}

CSignStop::~CSignStop()
{
}

HRESULT CSignStop::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 1.5f, 1.5f, 1.5f });
	m_pTransformCom->Set_Pos(_vec3{ 375.f, m_pTransformCom->Get_Scale().y, 118.f });

	m_szName = L"SignStop";

	return S_OK;
}

_int CSignStop::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CSignStop::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CSignStop::Render_Object()
{
	__super::Render_Object();
}

void CSignStop::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CSignStop::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CSignStop::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CSignStop::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Sign_Stop", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CSignStop* CSignStop::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSignStop* pInstance = new CSignStop(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("SignStop Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CSignStop::Free()
{
	__super::Free();
}
