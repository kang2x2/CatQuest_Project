#include "Item_Object.h"
#include "Export_Function.h"
#include "EventMgr.h"


CItem_Object::CItem_Object(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    :CItem(pGraphicDev, _eID)
{
 
}

CItem_Object::CItem_Object(const CItem& rhs)
    :CItem(rhs)
{
}

CItem_Object::~CItem_Object()
{
}

HRESULT CItem_Object::Ready_Object()
{

    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_eItemType = ITEM_TYPE::OBJECT;

    m_szName = L"";

    return S_OK;
}

_int CItem_Object::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    return iExit;
}

void CItem_Object::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CItem_Object::Render_Object()
{
    //m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

    //m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

    //m_pBufferCom->Render_Buffer();

    //m_pGraphicDev->SetTexture(0, NULL);

    //m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

    __super::Render_Object();

}

HRESULT CItem_Object::Add_Component()
{


    return S_OK;
}


void CItem_Object::Free()
{
    __super::Free();
}
