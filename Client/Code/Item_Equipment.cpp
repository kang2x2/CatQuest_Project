#include "Item_Equipment.h"
#include "Export_Function.h"
#include "EventMgr.h"


CItem_Equipment::CItem_Equipment(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID)
    : CItem(pGraphicDev, _eID)
{
}

CItem_Equipment::CItem_Equipment(const CItem& rhs)
    : CItem(rhs)
{
}

CItem_Equipment::~CItem_Equipment()
{
}

HRESULT CItem_Equipment::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    m_eItemType = ITEM_TYPE::EQUIPMENT;

    return S_OK;
}

_int CItem_Equipment::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);

    return iExit;
}

void CItem_Equipment::LateUpdate_Object()
{
    __super::LateUpdate_Object();

}

void CItem_Equipment::Render_Object()
{
    __super::Render_Object();
}

HRESULT CItem_Equipment::Add_Component()
{
    return S_OK;
}

void CItem_Equipment::Free()
{
    __super::Free();
}
