#include "stdafx.h"
#include "NoticeBoard.h"

#include "Export_Function.h"

CNoticeBoard::CNoticeBoard(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSign(pGraphicDev, OBJ_ID::ENVIRONMENT_SIGN_NOTICE)
{
}

CNoticeBoard::CNoticeBoard(const CSign& rhs)
	: CSign(rhs)
{
}

CNoticeBoard::~CNoticeBoard()
{
}

HRESULT CNoticeBoard::Ready_Object()
{
	CSign::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Scale(_vec3{ 3.f, 3.f, 3.f });
	m_pTransformCom->Set_Pos(_vec3{ 336.f, m_pTransformCom->Get_Scale().y, 126.f });

	m_szName = L"NoticeBoard";

	return S_OK;
}

_int CNoticeBoard::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CNoticeBoard::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CNoticeBoard::Render_Object()
{
	__super::Render_Object();
}

void CNoticeBoard::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNoticeBoard::OnCollision_Stay(CGameObject* _pColObj)
{
}

void CNoticeBoard::OnCollision_Exit(CGameObject* _pColObj)
{
}

HRESULT CNoticeBoard::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_NoticeBoard", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNoticeBoard* CNoticeBoard::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNoticeBoard* pInstance = new CNoticeBoard(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("NoticeBoard Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNoticeBoard::Free()
{
	__super::Free();
}
