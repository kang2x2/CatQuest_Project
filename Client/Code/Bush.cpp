#include "stdafx.h"
#include "..\Header\Bush.h"

#include "Export_Function.h"

#include "EventMgr.h"
#include "SoundMgr.h"

CBush::CBush(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
	: CEnvironment(pGraphicDev, _eID)
	, m_bReadySound(true)
{
}

CBush::CBush(const CBush& rhs)
	: CEnvironment(rhs)
{
}

CBush::~CBush()
{
}

HRESULT CBush::Ready_Object()
{
	CEnvironment::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_eEnter = ENTER_TYPE::ENTER;
	m_eInterType = INTERACTION_TYPE::INTERACTION_ALPHA;

	m_vecInitScale = { 4.0f, 3.5f, 3.5f };
	m_vecEndScale = {4.2f, 3.3f, 3.5f};

	m_bTransSwitch1 = false;
	m_bTransSwitch2 = false;
	m_iTranslucent = 255;
	m_iEndTranslucent = 150;

	m_pTransformCom->Set_Scale(m_vecInitScale);

	return S_OK;
}

_int CBush::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Play_ColLogic(fTimeDelta);
	Alpha_Update();

	return iExit;
}

void CBush::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CBush::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iTranslucent, 255, 255, 255));

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	CEnvironment::Render_Object(); 
}

void CBush::Play_ColLogic(const _float& fTimeDelta)
{

	if (m_bEventSwitch) {
		if (m_bReadySound)
		{
			CSoundMgr::GetInstance()->PlaySound(L"leaves_rustle.wav", CHANNEL_ID::ENVIRONMENT_3, ENVIRONMENT_BUSH);
			m_bReadySound = false;
		}
		// 줄어들었다
		if (!m_bTransSwitch1 && !m_bTransSwitch2) {
			m_pTransformCom->Set_Scale(_vec3{
			m_pTransformCom->Get_Scale().x + 1.f * fTimeDelta * 3.f,
			m_pTransformCom->Get_Scale().y - 1.f * fTimeDelta * 3.f,
			m_pTransformCom->Get_Scale().z });

			if (m_pTransformCom->Get_Scale().y <= m_vecEndScale.y) 
				m_bTransSwitch1 = true;
		}
		// 커졌다가 
		else if(m_bTransSwitch1){
			m_pTransformCom->Set_Scale(_vec3{
			m_pTransformCom->Get_Scale().x - 1.f * fTimeDelta * 2.f,
			m_pTransformCom->Get_Scale().y + 1.f * fTimeDelta * 2.f,
			m_pTransformCom->Get_Scale().z });

			if (m_pTransformCom->Get_Scale().y >= m_vecInitScale.y + 0.2f) {
				m_bTransSwitch1 = false;
				m_bTransSwitch2 = true;
			}
		}
		// 다시 원상태로
		else if (m_bTransSwitch2) {
			m_pTransformCom->Set_Scale(_vec3{
			m_pTransformCom->Get_Scale().x + 1.f * fTimeDelta * 3.f,
			m_pTransformCom->Get_Scale().y - 1.f * fTimeDelta * 3.f,
			m_pTransformCom->Get_Scale().z });

			if (m_pTransformCom->Get_Scale().y <= m_vecInitScale.y) {
				m_bTransSwitch2 = false;
				m_bEventSwitch = false;
				m_bReadySound = true;
			}
		}
	}
}

void CBush::Alpha_Update()
{
	// 알파값 조절
	if (m_bEnter) {
		if (m_iTranslucent > m_iEndTranslucent) {
			m_iTranslucent -= 5;
		}
	}
	else {
		if (m_iTranslucent < 255) {
			m_iTranslucent += 5;
		}
	}

}

HRESULT CBush::Add_Component()
{
	CComponent* pComponent = nullptr;

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

void CBush::Free()
{
	__super::Free();
}
