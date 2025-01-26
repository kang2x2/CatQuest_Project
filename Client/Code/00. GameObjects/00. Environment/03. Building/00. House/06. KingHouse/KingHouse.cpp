#include "stdafx.h"
#include "KingHouse.h"

#include "Export_Function.h"

#include "IndicatorUI.h"

CKingHouse::CKingHouse(LPDIRECT3DDEVICE9 pGraphicDev)
	: CHouse(pGraphicDev, OBJ_ID::ENVIRONMENT_BUILDING_KINGHOUSE)
{
}

CKingHouse::CKingHouse(const CHouse& rhs)
	: CHouse(rhs)
{
}

CKingHouse::~CKingHouse()
{
}

HRESULT CKingHouse::Ready_Object()
{
	CHouse::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;
	m_eInterType = INTERACTION_TYPE::INTERACTION_ALPHA;
	m_iTranslucent = 255;

	m_pTransformCom->Set_Scale(_vec3{ 4.f, 6.f, 6.f });
	m_pTransformCom->Set_Pos(_vec3{ 120.f, m_pTransformCom->Get_Scale().y, 60.f });

	m_szName = L"KingHouse";

	return S_OK;
}

_int CKingHouse::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	Alpha_Update();

	if (PLAY_MODE::GAME == CManagement::GetInstance()->Get_PlayMode())
	{
		//CIndicatorUI* pUI = static_cast<CIndicatorUI*>(CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::UI, L"UI_Indicator"));
		//pUI->Set_IndicTarget(this);
	}

	return iExit;
}

void CKingHouse::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CKingHouse::Render_Object()
{
	__super::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pTextureCom2->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom2->Render_Buffer();
	
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CKingHouse::Alpha_Update()
{
	// 알파값 조절
	if (m_bEnter) {
		if (m_iTranslucent > 10) {
			m_iTranslucent -= 10;
		}
	}
	else {
		if (m_iTranslucent < 255) {
			m_iTranslucent += 10;
		}
	}
}

HRESULT CKingHouse::Add_Component()
{
	CComponent* pComponent = nullptr;
	// Proto_Texture_KingHouse_In
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_KingHouse_In", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pTextureCom2 = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_KingHouse_Out", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom2 = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);
	
	return S_OK;
}

CKingHouse* CKingHouse::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CKingHouse* pInstance = new CKingHouse(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("KingHouse Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CKingHouse::Free()
{
	__super::Free();
}
