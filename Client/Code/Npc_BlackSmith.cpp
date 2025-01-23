#include "stdafx.h"
#include "Npc_BlackSmith.h"

#include "Export_Function.h"

#include "Shadow_Npc.h"
#include "TalkMgr.h"
#include "QuestMgr.h"

CNpc_BlackSmith::CNpc_BlackSmith(LPDIRECT3DDEVICE9 pGraphicDev)
	: CNpc(pGraphicDev, OBJ_ID::NPC_BLACKSMITH)
{
}

CNpc_BlackSmith::CNpc_BlackSmith(const CNpc& rhs)
	: CNpc(rhs)
{
}


CNpc_BlackSmith::~CNpc_BlackSmith()
{
}

HRESULT CNpc_BlackSmith::Ready_Object()
{
	CNpc::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pAnimation = CAnimation::Create(m_pGraphicDev, m_pTextureCom, STATE_TYPE::FRONT_IDLE, 0.1f, true);

	m_pTransformCom->Set_Pos(_vec3{ 85.f, m_pTransformCom->Get_Scale().y + 1.f, 110.f });
	m_pTransformCom->Set_Scale(_vec3{ 2.f, 2.f, 2.f });

	if (CManagement::GetInstance()->Get_PlayMode() == PLAY_MODE::GAME)
		CEventMgr::GetInstance()->Add_Obj(L"Npc_BlackSmith_Shadow", CShadow_Npc::Create(m_pGraphicDev, this));

	m_szName = L"Npc_BlackSmith";

	return S_OK;
}

_int CNpc_BlackSmith::Update_Object(const _float& fTimeDelta)
{
	_int iExit = CNpc::Update_Object(fTimeDelta);

	return iExit;
}

void CNpc_BlackSmith::LateUpdate_Object()
{
	CNpc::LateUpdate_Object();
}

void CNpc_BlackSmith::Render_Object()
{
	CNpc::Render_Object();
}

void CNpc_BlackSmith::OnCollision_Enter(CGameObject* _pColObj)
{
}

void CNpc_BlackSmith::OnCollision_Stay(CGameObject* _pColObj)
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

void CNpc_BlackSmith::OnCollision_Exit(CGameObject* _pColObj)
{
	m_bCol = false;
}

HRESULT CNpc_BlackSmith::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Npc_BlackSmith", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

CNpc_BlackSmith* CNpc_BlackSmith::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNpc_BlackSmith* pInstance = new CNpc_BlackSmith(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Npc_BlackSmith Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CNpc_BlackSmith::Free()
{
	CNpc::Free();
}
