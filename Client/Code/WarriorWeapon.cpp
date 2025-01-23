#include "WarriorWeapon.h"
#include "Export_Function.h"
#include "EventMgr.h"

// Shadow
#include  "Shadow_Item.h"
CWarriorWeapon::CWarriorWeapon(LPDIRECT3DDEVICE9 pGraphicDev)
    : CItem_Weapon(pGraphicDev, OBJ_ID::ITEM_WARRIOR)
{
}

CWarriorWeapon::CWarriorWeapon(const CItem& rhs)
    : CItem_Weapon(rhs)
{

}

CWarriorWeapon::~CWarriorWeapon()
{
}

HRESULT CWarriorWeapon::Ready_Object()
{
    __super::Ready_Object();
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);


    // STATEINFO Setting
    m_tStatInfo.fGold = 100.f;
    m_tStatInfo.fAD = 5.f;
    m_tStatInfo.fMaxHP = 20.f;

    m_eClass = CLASS_TYPE::THORN;


    // ���� �̹��� ũ��
    //m_vImageSize.x = 1.04f;  // 100px = 1.f
    //m_vImageSize.y = 1.25f;
    //m_vImageSize.z = 2.f;   // ���� ��
    //
    //
    //// Transform Setting
    //m_pTransformCom->Set_Scale(_vec3{ m_vImageSize.x * 1.5f, m_vImageSize.y * 1.5f, m_vImageSize.z });



    //m_pTransformCom->Set_Pos(_vec3{
    //    _float(START_POS_WORLD_X) + 30.f,
    //    m_pTransformCom->Get_Scale().y,
    //     _float(START_POS_WORLD_Z) - 10.f });
    //
    //m_fJumpingSpeed = 0.01;
    //
    //CEventMgr::GetInstance()->Add_Obj(L"Warrior_Weapon_Shadow", CShadow_Item::Create(m_pGraphicDev, this));

    m_szName = L"Item_WarriorWeapon";

    m_eItemType = ITEM_TYPE::WEAPON;

    return S_OK;
}

_int CWarriorWeapon::Update_Object(const _float& fTimeDelta)
{
    _int iExit = __super::Update_Object(fTimeDelta);
    //Engine::Add_RenderGroup(RENDER_ALPHA, this);	 //	���� �׷� �߰�
    //
    //
    //// Jumping 
    //_vec3		vOwnerPos = m_pTransformCom->Get_Info(INFO_POS);
    //float		Y = m_pTransformCom->Get_Scale().y;
    //
    //
    //
    //if (vOwnerPos.y < Y || vOwnerPos.y > Y + 0.3f)
    //{
    //    m_fJumpingSpeed *= -1;
    //}
    //m_pTransformCom->Translate(DIR_UP, m_fJumpingSpeed, WORLD);



    return iExit;
}

void CWarriorWeapon::LateUpdate_Object()
{
    __super::LateUpdate_Object();
}

void CWarriorWeapon::Render_Object()
{

    //m_pTextureCom->Render_Texture(); // �ؽ�ó ���� -> ���� ���� ���� ��!
    //
    //m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());
    //
    //m_pBufferCom->Render_Buffer();
    //
    //m_pGraphicDev->SetTexture(0, NULL);
    //
    //m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));


    __super::Render_Object();
}

HRESULT CWarriorWeapon::Add_Component()
{
    CComponent* pComponent = nullptr;

    // Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Item_WarriorWeapon", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);





    return S_OK;
}

CWarriorWeapon* CWarriorWeapon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CWarriorWeapon* pInstance = new CWarriorWeapon(pGraphicDev);

    if (FAILED(pInstance->Ready_Object()))
    {

        Safe_Release(pInstance);

        MSG_BOX("Warrior Weapon Create Failed");
        return nullptr;
    }
    return pInstance;

}

void CWarriorWeapon::Free()
{
    __super::Free();
}
