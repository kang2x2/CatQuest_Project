#include "FlagRussia.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "RangeObj.h"

CFlagRussia::CFlagRussia(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
	: CFlag(pGraphicDev, OBJ_ID::FLAG_RUSSIA)
{
	m_pFlagOwner = _owner;
}

CFlagRussia::CFlagRussia(const CFlag& rhs)
	: CFlag(rhs)
{
}

CFlagRussia::~CFlagRussia()
{

}

HRESULT CFlagRussia::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 155.f, 1.02f, 160.f });

	CRangeObj* pRangeObj = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pRangeObj, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"FlagRussia_RangeObj", pRangeObj);
	pRangeObj->Set_Radius(6.f);
	pRangeObj->Set_Pos(m_pTransformCom->Get_Info(INFO_POS));

	m_eFlagTag = FLAG_TAG::FLAG_RUSSIA;

	m_szName = L"Flag_Russia";

	return S_OK;
}

_int CFlagRussia::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CFlag::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CFlagRussia::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CFlagRussia::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fTranslucent, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object();

	m_pFlagTexCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CFlagRussia::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Texture
	pComponent = m_pFlagTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Flag_Russia", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CFlagRussia* CFlagRussia::Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
{
	CFlagRussia* pInstance = new CFlagRussia(pGraphicDev, _owner);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlagRussia Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CFlagRussia::Free()
{

	__super::Free();
}
