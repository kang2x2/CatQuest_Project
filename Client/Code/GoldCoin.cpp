#include "GoldCoin.h"
#include "Export_Function.h"
#include "EventMgr.h"

#include "Shadow_Item.h"
#include "ItemSparkle.h"


CGoldCoin::CGoldCoin(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem_Object(pGraphicDev, OBJ_ID::ITEM_GOLD)
{
}

CGoldCoin::CGoldCoin(const CItem& rhs)
	: CItem_Object(rhs)
{
}

CGoldCoin::~CGoldCoin()
{

}

HRESULT CGoldCoin::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_iItemValue = rand() % 11 + 20;

	// STATEINFO Setting
	m_tStatInfo.fGold = 100.f;

	ZeroMemory(&m_tLerpPos, sizeof(LERP_VEC3_INFO));

	// 원래 이미지 크기
	m_vImageSize.x = 0.69f;  // 100px = 1.f
	m_vImageSize.y = 0.66f;
	m_vImageSize.z = 2.f;   // 고정 값

	 
	// Transform Setting
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 1.5f, m_vImageSize.y * 1.5f, m_vImageSize.z });



	m_pTransformCom->Set_Pos(_vec3{ 80.f, m_pTransformCom->Get_Scale().y, 30.f });
	
	m_fJumpingSpeed = 0.01;

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
	{
		CEventMgr::GetInstance()->Add_Obj(L"Gold_Shadow", CShadow_Item::Create(m_pGraphicDev, this));
		CEventMgr::GetInstance()->Add_Obj(L"CoinSparkle", CItemSparkle::Create(m_pGraphicDev, this));
	}

	m_szName = L"Item_GoldCoin";



	m_tAlpha.Init_Lerp();
	m_tAlpha.Set_Lerp( 1.f, 0.f, 255.f);

	return S_OK;
}

_int CGoldCoin::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CItem::Update_Object(fTimeDelta);   // 상위 먼저
	Engine::Add_RenderGroup(RENDER_ALPHA, this);	 //	렌더 그룹 추가



	m_tAlpha.Update_Lerp(fTimeDelta);

	// Jumping 

	_vec3		vOwnerPos	= m_pTransformCom->Get_Info(INFO_POS);
	float		Y			= m_pTransformCom->Get_Scale().y;



	if (vOwnerPos.y < Y || vOwnerPos.y > Y + 0.3f)
	{
		m_fJumpingSpeed *= -1;
	}
	m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);


	// Player - Transform Com
	CTransform* pPlayerTransform = dynamic_cast<CTransform*>(Engine::Get_Component(OBJ_TYPE::PLAYER, L"Player", COMPONENT_TYPE::TRANSFORM, COMPONENTID::ID_DYNAMIC));
	NULL_CHECK_RETURN(pPlayerTransform, iExit);

	_vec3 vPlayerPos = pPlayerTransform->Get_Info(INFO_POS);



	_vec3	vDir = vOwnerPos - vPlayerPos;
	_float fDistance = D3DXVec3Length(&vDir);
	

	// Magnet
	if (m_tLerpPos.bActive)
	{
		m_tLerpPos.Update_Lerp(fTimeDelta);
		m_pTransformCom->Set_Pos(m_tLerpPos.vCurVec);
		m_tLerpPos.vEndVec = vPlayerPos;

	}

	if (fDistance <= 7.f && !m_tLerpPos.bActive)
	{
		//m_pAICom->Chase_TargetY(&vPlayerPos, fTimeDelta, 30.f);
		//m_pTransformCom->Translate(fTimeDelta * 30.f);
		m_tLerpPos.Init_Lerp(LERP_MODE::EASE_IN);
		m_tLerpPos.Set_Lerp(0.3f, m_pTransformCom->Get_Info(INFO_POS), vPlayerPos);
	}





	return iExit;
}

void CGoldCoin::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CGoldCoin::Render_Object()
{

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_tAlpha.fCurValue), 255, 255, 255));


	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));


	__super::Render_Object(); // 콜라이더 출력

}

HRESULT CGoldCoin::Add_Component()
{
	CComponent* pComponent = nullptr;

	
	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_Gold", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	// AI
	pComponent = m_pAICom = dynamic_cast<CAIComponent*>(Engine::Clone_Proto(COMPONENT_TYPE::AICOM, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(COMPONENT_TYPE::AICOM, pComponent);



	return S_OK;
}

CGoldCoin* CGoldCoin::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGoldCoin* pInstance = new CGoldCoin(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("GoldCoin Create Failed");
		return nullptr;
	}

	return pInstance;


}

void CGoldCoin::Free()
{

	__super::Free();
}
