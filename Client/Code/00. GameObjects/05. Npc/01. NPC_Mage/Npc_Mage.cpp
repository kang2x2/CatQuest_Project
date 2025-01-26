#include "stdafx.h"
#include "Npc_Mage.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"
#include "TalkMgr.h"
#include "QuestMgr.h"

CNpc_Mage::CNpc_Mage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_MAGE)
{
}

CNpc_Mage::CNpc_Mage(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_Mage::~CNpc_Mage()
{
}

HRESULT CNpc_Mage::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ 200.f, m_pTransformCom->Get_Scale().y + 1.f, 290.f });
	m_pTransformCom->Set_Scale(_vec3{ 2.5f, 2.5f, 2.5f });

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Npc_Mage_Shadow", CShadow_Npc::Create(m_pGraphicDev, this));
	
	m_szName = L"Npc_Mage";

	return S_OK;
}

_int CNpc_Mage::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_Mage::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_Mage::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_Mage::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_Mage::OnCollision_Stay(CGameObject* _pColObj)
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

void CNpc_Mage::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CNpc_Mage::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_Mage", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_Mage* CNpc_Mage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_Mage* pInstance = new CNpc_Mage(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_Mage Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_Mage::Free()
{
	CNpc::Free();
}
