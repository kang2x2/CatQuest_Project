#include "Key.h"
#include "Export_Function.h"
#include "EventMgr.h"

CKey::CKey(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItem_Object(pGraphicDev, OBJ_ID::ITEM_KEY)
{
}

CKey::CKey(const CItem& rhs)
	: CItem_Object(rhs)
{
}

CKey::~CKey()
{

}

HRESULT CKey::Ready_Object()
{
	__super::Ready_Object();
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


	// STATEINFO Setting
	//m_tStatInfo.fGold = 100.f;



	// 원래 이미지 크기
	m_vImageSize.x = 1.5;  // 100px = 1.f
	m_vImageSize.y = 0.6;
	m_vImageSize.z = 2.f;   // 고정 값


	// Transform Setting
	m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x , m_vImageSize.y, m_vImageSize.z});
	m_pTransformCom->Set_Pos(_vec3{ 165.f, m_pTransformCom->Get_Scale().y + 1.f, 379.f });

	m_fJumpingSpeed = 0.01;

	m_szName = L"Item_Key";

	return S_OK;
}

_int CKey::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CItem::Update_Object(fTimeDelta);   // 상위 먼저
	Engine::Add_RenderGroup(RENDER_ALPHA, this);	 //	렌더 그룹 추가


	// Jumping 

	_vec3		vOwnerPos	= m_pTransformCom->Get_Info(INFO_POS);
	float		Y			= m_pTransformCom->Get_Scale().y;



	if (vOwnerPos.y < Y || vOwnerPos.y > Y + 0.3f)
	{
		m_fJumpingSpeed *= -1;
	}
	m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);





	return iExit;
}

void CKey::LateUpdate_Object()
{
	__super::LateUpdate_Object();

}

void CKey::Render_Object()
{

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	__super::Render_Object(); // 콜라이더 출력

}

void CKey::OnCollision_Enter(CGameObject* _pColObj)
{
	switch (_pColObj->Get_Type())
	{
	case Engine::OBJ_TYPE::PLAYER:
	{
		m_bCol = true;
		CEventMgr::GetInstance()->Delete_Obj(this);  // 삭제
	}
	break;
	default:
		break;
	}
}

void CKey::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CKey::Add_Component()
{
	CComponent* pComponent = nullptr;

	
	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_Key", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);



	return S_OK;
}

CKey* CKey::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CKey* pInstance = new CKey(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Key Create Failed");
		return nullptr;
	}

	return pInstance;

	return nullptr;
}

void CKey::Free()
{
	__super::Free();
}
