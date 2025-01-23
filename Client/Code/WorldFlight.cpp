#include "WorldFlight.h"
#include "Export_Function.h"
#include "EventMgr.h"
#include "SoundMgr.h"

#include "GetWorldEffect.h"
#include "Shadow_Item.h"

CWorldFlight::CWorldFlight(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem_Object(pGraphicDev, OBJ_ID::ITEM_WORLD_FLIGHT)
	, m_iLevel(0), m_bDelete(false), m_iOraMode(ORA_SIZE_UP)
{
}

CWorldFlight::CWorldFlight(const CItem& rhs)
	: CItem_Object(rhs)
{
}

CWorldFlight::~CWorldFlight()
{

}

HRESULT CWorldFlight::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// Transform Setting
	m_pTransformCom->Set_Scale(_vec3{ 1.4f , 1.4f, 0.5f });
	m_pTransformCom->Set_Pos(_vec3{
		137.f,
		m_pTransformCom->Get_Scale().y,
		383.f });
	// m_pTransformCom->Set_Pos(_vec3{
	// _float(START_POS_WORLD_X + 5.f),
	// m_pTransformCom->Get_Scale().y + 1.f,
	// _float(START_POS_WORLD_Z) });

	m_fJumpingSpeed = 0.01;

	m_szName = L"Item_WorldFlight";
	m_eEnter = ENTER_TYPE::ENTER_NO;
	m_eInterType = INTERACTION_TYPE::INTERACTION_QUESTION;

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
	{
		CEventMgr::GetInstance()->Add_Obj(L"WorldFlight_Shadow", CShadow_Item::Create(m_pGraphicDev, this));
	}

	Ready_Lerp();

	return S_OK;
}

void CWorldFlight::Ready_Lerp()
{
	// Ora
	m_tOraSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tOraSizeUpLerp.Set_Lerp(1.f, 1.4f, 1.96f);
	m_tOraSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
	m_tOraSizeDownLerp.Set_Lerp(1.f, 1.96f, 1.4f);

	for (_int i = 0; i < SPARKLE_AMOUNT; ++i)
	{
		m_tSparkle[i].m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
		m_tSparkle[i].m_tSizeUpLerp.Set_Lerp(0.1f, 0.f, 0.8f);
		m_tSparkle[i].m_tSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
		m_tSparkle[i].m_tSizeDownLerp.Set_Lerp(0.1f, 0.8f, 0.f);
	}

	// World Flight
	m_tUpPosY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tUpPosY.Set_Lerp(1.f, m_pTransformCom->Get_Scale().y + 1.f, m_pTransformCom->Get_Scale().y + 1.5f);
	
	m_tDownPosY.Init_Lerp(LERP_MODE::EASE_IN);
	m_tDownPosY.Set_Lerp(1.f, m_pTransformCom->Get_Scale().y + 1.5f, m_pTransformCom->Get_Scale().y + 1.f);
}

_int CWorldFlight::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CItem::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	// Fly
	// _vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
	// float		Y = m_pTransformCom->Get_Scale().y;
	// 
	// if (vOwnerPos.y < Y || vOwnerPos.y > Y + 1.5f)
	// {
	// 	m_fJumpingSpeed *= -1;
	// }
	// m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);

	// sparkle 위치
	m_tSparkle[0].m_pSparkleTransCom->Set_Pos({
	m_pTransformCom->Get_Info(INFO_POS).x - m_pTransformCom->Get_Scale().x * 0.5f,
	m_pTransformCom->Get_Info(INFO_POS).y - m_pTransformCom->Get_Scale().y * 0.7f,
	m_pTransformCom->Get_Info(INFO_POS).z });
	m_tSparkle[1].m_pSparkleTransCom->Set_Pos({
	m_pTransformCom->Get_Info(INFO_POS).x + m_pTransformCom->Get_Scale().x * 0.7f,
	m_pTransformCom->Get_Info(INFO_POS).y,
	m_pTransformCom->Get_Info(INFO_POS).z });
	m_tSparkle[2].m_pSparkleTransCom->Set_Pos({
	m_pTransformCom->Get_Info(INFO_POS).x - m_pTransformCom->Get_Scale().x * 0.7f,
	m_pTransformCom->Get_Info(INFO_POS).y + m_pTransformCom->Get_Scale().y * 1.f,
	m_pTransformCom->Get_Info(INFO_POS).z });
	// ora 위치
	m_pOraTransCom->Set_Pos(m_pTransformCom->Get_Info(INFO_POS));

	if (!m_bDelete) Update_Lerp(fTimeDelta);
	else            Play_Delete();

	return iExit;
}

void CWorldFlight::Update_Lerp(const _float& fTimeDelta)
{
	// Ora
	if (m_iOraMode == ORA_SIZE_UP)
	{
		m_tOraSizeUpLerp.Update_Lerp(fTimeDelta);
		m_tUpPosY.Update_Lerp(fTimeDelta);

		m_pOraTransCom->Set_Scale({
		m_tOraSizeUpLerp.fCurValue,
		m_tOraSizeUpLerp.fCurValue,
		m_tOraSizeUpLerp.fCurValue });

		m_pTransformCom->Set_Pos(_vec3{ 137.f, m_tUpPosY.fCurValue, 383.f });

		if (!m_tOraSizeUpLerp.bActive)
		{
			m_iOraMode = ORA_SIZE_DOWN;
			m_tOraSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tOraSizeDownLerp.Set_Lerp(1.f, 3.86f, 3.06f);
			m_tDownPosY.Init_Lerp(LERP_MODE::EASE_IN);
			m_tDownPosY.Set_Lerp(1.f, m_pTransformCom->Get_Scale().y + 1.5f, m_pTransformCom->Get_Scale().y + 1.f);

		}
	}
	else if(m_iOraMode == ORA_SIZE_DOWN)
	{
		m_tOraSizeDownLerp.Update_Lerp(fTimeDelta);
		m_tDownPosY.Update_Lerp(fTimeDelta);
		
		m_pOraTransCom->Set_Scale({
		m_tOraSizeDownLerp.fCurValue,
		m_tOraSizeDownLerp.fCurValue,
		m_tOraSizeDownLerp.fCurValue });

		m_pTransformCom->Set_Pos(_vec3{ 137.f, m_tDownPosY.fCurValue, 383.f });


		if (!m_tOraSizeDownLerp.bActive)
		{
			m_iOraMode = ORA_SIZE_UP;
			m_tOraSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tOraSizeUpLerp.Set_Lerp(1.f, 3.06f, 3.86f);
			m_tUpPosY.Init_Lerp(LERP_MODE::EASE_IN);
			m_tUpPosY.Set_Lerp(1.f, m_pTransformCom->Get_Scale().y + 1.f, m_pTransformCom->Get_Scale().y + 1.5f);
		}
	}

	
	// Sparkle
	switch (m_iLevel)
	{
	case 0:
		m_tSparkle[0].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[0].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[0].m_tSizeUpLerp.fCurValue,
		m_tSparkle[0].m_tSizeUpLerp.fCurValue,
		m_tSparkle[0].m_tSizeUpLerp.fCurValue });

		if (!m_tSparkle[0].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 1:
		m_tSparkle[1].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[1].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[1].m_tSizeUpLerp.fCurValue,
		m_tSparkle[1].m_tSizeUpLerp.fCurValue,
		m_tSparkle[1].m_tSizeUpLerp.fCurValue });

		if (!m_tSparkle[1].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 2:
		m_tSparkle[2].m_tSizeUpLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[2].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[2].m_tSizeUpLerp.fCurValue,
		m_tSparkle[2].m_tSizeUpLerp.fCurValue,
		m_tSparkle[2].m_tSizeUpLerp.fCurValue });

		if (!m_tSparkle[2].m_tSizeUpLerp.bActive) m_iLevel += 1;

		break;
	case 3:
		m_tSparkle[2].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[2].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[2].m_tSizeDownLerp.fCurValue,
		m_tSparkle[2].m_tSizeDownLerp.fCurValue,
		m_tSparkle[2].m_tSizeDownLerp.fCurValue });

		if (!m_tSparkle[2].m_tSizeDownLerp.bActive) m_iLevel += 1;

		break;
	case 4:
		m_tSparkle[1].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[1].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[1].m_tSizeDownLerp.fCurValue,
		m_tSparkle[1].m_tSizeDownLerp.fCurValue,
		m_tSparkle[1].m_tSizeDownLerp.fCurValue });

		if (!m_tSparkle[1].m_tSizeDownLerp.bActive) m_iLevel += 1;

		break;
	case 5:
		m_tSparkle[0].m_tSizeDownLerp.Update_Lerp(fTimeDelta);
		m_tSparkle[0].m_pSparkleTransCom->Set_Scale({
		m_tSparkle[0].m_tSizeDownLerp.fCurValue,
		m_tSparkle[0].m_tSizeDownLerp.fCurValue,
		m_tSparkle[0].m_tSizeDownLerp.fCurValue });

		if (!m_tSparkle[0].m_tSizeDownLerp.bActive) m_iLevel += 1;
		break;

	case 6:
		for (_int i = 0; i < SPARKLE_AMOUNT; ++i)
		{
			m_tSparkle[i].m_tSizeUpLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tSparkle[i].m_tSizeUpLerp.Set_Lerp(0.1f, 0.f, 0.8f);
			m_tSparkle[i].m_tSizeDownLerp.Init_Lerp(LERP_MODE::EASE_IN);
			m_tSparkle[i].m_tSizeDownLerp.Set_Lerp(0.1f, 0.8f, 0.f);
		}
		m_iLevel = 0;
		break;
	}
}

void CWorldFlight::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CWorldFlight::Render_Object()
{
	// Ora
	m_pOraTexCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pOraTransCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	// World Flight
	m_pTextureCom->Render_Texture();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
	m_pBufferCom->Render_Buffer();

	// Sparkle
	for (_int i = 0; i < 3; ++i)
	{
		m_tSparkle[i].m_pSparkleTextureCom->Render_Texture();
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_tSparkle[i].m_pSparkleTransCom->Get_WorldMat());
		m_pBufferCom->Render_Buffer();
	}

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // 콜라이더 출력

}

void CWorldFlight::Play_Delete()
{
	CGetWorldEffect* m_pEffect = CGetWorldEffect::Create(m_pGraphicDev, 
		m_pTransformCom->Get_Info(INFO_POS));
	CEventMgr::GetInstance()->Add_Obj(L"GetWorldEffect", m_pEffect);
	CSoundMgr::GetInstance()->PlaySound(L"catnap.wav", CHANNEL_ID::EFFECT_3, 1.f);
	CEventMgr::GetInstance()->Delete_Obj(this);  // 삭제
}

void CWorldFlight::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CWorldFlight::OnCollision_Stay(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
	}
	break;
	default:
		break;
	}
}

void CWorldFlight::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CWorldFlight::Add_Component()
{
	CComponent* pComponent = nullptr;

	// WorldFlight
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WorldFlight", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	// Ora
	pComponent = m_pOraTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

	pComponent = m_pOraTexCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WorldFlight_Ora", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	for (_int i = 0; i < 3; ++i)
	{
		pComponent = m_tSparkle[i].m_pSparkleTransCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Proto(COMPONENT_TYPE::TRANSFORM, this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::TRANSFORM, pComponent);

		pComponent = m_tSparkle[i].m_pSparkleTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_ItemSparkle", this));
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);
	}


	return S_OK;
}

CWorldFlight* CWorldFlight::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CWorldFlight* pInstance = new CWorldFlight(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("WorldFlight Create Failed");
		return nullptr;
	}

	return pInstance;

	return nullptr;
}

void CWorldFlight::Free()
{
	__super::Free();
}
