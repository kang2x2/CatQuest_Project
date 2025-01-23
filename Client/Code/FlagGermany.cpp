#include "FlagGermany.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "RangeObj.h"

CFlagGermany::CFlagGermany(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
	: CFlag(pGraphicDev, OBJ_ID::FLAG_GERMANY)
{
	m_pFlagOwner = _owner;
}

CFlagGermany::CFlagGermany(const CFlag& rhs)
	: CFlag(rhs)
{
}

CFlagGermany::~CFlagGermany()
{

}

HRESULT CFlagGermany::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 185.f, 1.02f, 140.f });

	CRangeObj* pRangeObj = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pRangeObj, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"FlagGermany_RangeObj", pRangeObj);
	pRangeObj->Set_Radius(6.f);
	pRangeObj->Set_Pos(m_pTransformCom->Get_Info(INFO_POS));

	m_eFlagTag = FLAG_TAG::FLAG_GERMANY;

	m_szName = L"Flag_Germany";

	return S_OK;
}

_int CFlagGermany::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CFlag::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CFlagGermany::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CFlagGermany::Render_Object()
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

HRESULT CFlagGermany::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Texture
	pComponent = m_pFlagTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Flag_Germany", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CFlagGermany* CFlagGermany::Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
{
	CFlagGermany* pInstance = new CFlagGermany(pGraphicDev, _owner);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlagGermany Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CFlagGermany::Free()
{

	__super::Free();
}
