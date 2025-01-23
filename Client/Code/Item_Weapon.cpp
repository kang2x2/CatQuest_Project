#include "Item_Weapon.h"
#include "Export_Function.h"

CItem_Weapon::CItem_Weapon(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :CItem(pGraphicDev, _eID)
  
{
    ZeroMemory(&m_eItemInfo, sizeof(STATINFO));
}

CItem_Weapon::CItem_Weapon(const CItem& rhs)
    :CItem(rhs)
{
}

CItem_Weapon::~CItem_Weapon()
{
}

HRESULT CItem_Weapon::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_eItemType = ITEM_TYPE::WEAPON;
    m_eUILayer = UI_LAYER::LV2;

    return S_OK;
}

_int CItem_Weapon::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_VIEWUI, this);

    D3DXMatrixIdentity(&m_ItemMatWorld);

    return iExit;
}

void CItem_Weapon::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CItem_Weapon::Render_Object()
{
    m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_ItemMatWorld);

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    // m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

    m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    __super::Render_Object();
}

HRESULT CItem_Weapon::Add_Component()
{
    return S_OK;
}

void CItem_Weapon::Free()
{
    __super::Free();
}
