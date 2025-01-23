#include "UsePotion.h"
#include "Export_Function.h"
#include "EventMgr.h"

// Shadow
#include  "Shadow_Item.h"
CUsePotion::CUsePotion(LPDIRECT3DDEVICE9 pGraphicDev)
    : CItem(pGraphicDev, OBJ_ID::ITEM_POTION)
    , m_iAmount(0)
{
}

CUsePotion::CUsePotion(const CItem& rhs)
    : CItem(rhs)
{

}

CUsePotion::~CUsePotion()
{
}

HRESULT CUsePotion::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_szName = L"Item_UsePotion";

    m_eItemType = ITEM_TYPE::USE;
    m_eUILayer = UI_LAYER::LV2;

    return S_OK;
}

_int CUsePotion::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_VIEWUI, this);

    D3DXMatrixIdentity(&m_ItemMatWorld);

    return iExit;
}

void CUsePotion::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CUsePotion::Render_Object()
{

    m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_ItemMatWorld);

    m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    m_pBufferCom->Render_Buffer();

    m_pGraphicDev->SetTexture(0, NULL);

    m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

    m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    __super::Render_Object();
}

HRESULT CUsePotion::Add_Component()
{
    CComponent* pComponent = nullptr;

    // Texture
    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_Potion", this));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);





    return S_OK;
}

CUsePotion* CUsePotion::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CUsePotion* pInstance = new CUsePotion(pGraphicDev);

    if (FAILED(pInstance->Ready_Object()))
    {

        Safe_Release(pInstance);

        MSG_BOX("Use Potion Create Failed");
        return nullptr;
    }
    return pInstance;

}

void CUsePotion::Free()
{
    __super::Free();
}
