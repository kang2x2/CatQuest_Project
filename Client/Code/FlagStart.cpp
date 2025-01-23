#include "FlagStart.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "RangeObj.h"

CFlagStart::CFlagStart(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
	: CFlag(pGraphicDev, OBJ_ID::FLAG_START)
	, m_fTranslucent(0.f), m_bShow(false)
{
	m_pFlagOwner = _owner;
}

CFlagStart::CFlagStart(const CFlag& rhs)
	: CFlag(rhs)
{
}

CFlagStart::~CFlagStart()
{

}

HRESULT CFlagStart::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransformCom->Set_Pos(_vec3{ 155.f, 1.02f, 140.f });

	CRangeObj* pRangeObj = CRangeObj::Create(m_pGraphicDev, this, 100.f);
	NULL_CHECK_RETURN(pRangeObj, E_FAIL);
	CEventMgr::GetInstance()->Add_Obj(L"FlagStart_RangeObj", pRangeObj);
	pRangeObj->Set_Radius(6.f);
	pRangeObj->Set_Pos(m_pTransformCom->Get_Info(INFO_POS));

	m_eFlagTag = FLAG_TAG::FLAG_START;

	m_szName = L"Flag_Start";

	m_bActive = false;

	m_tAlphaLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tAlphaLerp.Set_Lerp(0.5f, 0.f, 255.f);

	return S_OK;
}

_int CFlagStart::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CFlag::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	if (m_bShow)
	{
		m_tAlphaLerp.Update_Lerp(fTimeDelta);
		m_fTranslucent = m_tAlphaLerp.fCurValue;

		if (!m_bShow)
		{
			m_tDeAlphaLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tDeAlphaLerp.Set_Lerp(0.5f, 255.f, 0.f);
			m_fTranslucent = m_tDeAlphaLerp.fCurValue;
		}
	}
	if (!m_bShow)
	{
		m_tDeAlphaLerp.Update_Lerp(fTimeDelta);
		if (m_tDeAlphaLerp.bActive)
		{
			m_fTranslucent = m_tDeAlphaLerp.fCurValue;

			if (!m_tDeAlphaLerp.bActive)
			{
				m_bActive = false;
			}
		}
	}

	return iExit;
}

void CFlagStart::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CFlagStart::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB((_int)m_fTranslucent, 255, 255, 255));
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object();

	m_pFlagTexCom->Render_Texture(m_eFlagTag);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFlagStart::Set_Texture(const FLAG_TAG& _eID)
{
	m_eFlagTag = _eID;
}

HRESULT CFlagStart::Add_Component()
{
	CComponent* pComponent = nullptr;

	// Texture
	pComponent = m_pFlagTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Flag_List", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CFlagStart* CFlagStart::Create(LPDIRECT3DDEVICE9 pGraphicDev, CFlagOwner* _owner)
{
	CFlagStart* pInstance = new CFlagStart(pGraphicDev, _owner);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("FlagStart Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CFlagStart::Free()
{

	__super::Free();
}
