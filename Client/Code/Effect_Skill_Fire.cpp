#include "Effect_Skill_Fire.h"

#include "Export_Function.h"

#include "EventMgr.h"

CEffect_Skill_Fire::CEffect_Skill_Fire(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
	: CEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_SKILL_FIRE), m_pTextureCom(nullptr)
{
}

CEffect_Skill_Fire::CEffect_Skill_Fire(const CEffect_Skill_Fire& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CEffect_Skill_Fire::~CEffect_Skill_Fire()
{
}

HRESULT CEffect_Skill_Fire::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CEffect_Skill_Fire::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CEffect_Skill_Fire::LateUpdate_Object()
{
	__super::LateUpdate_Object();


}

void CEffect_Skill_Fire::Render_Object()
{
	__super::Render_Object(); // 스킬 애니메이션 출력

	NULL_CHECK(m_pOwnerobject);

	// 장판 텍스처 출력
	// 빌보드 해제

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));
	
	_matrix matWorld = m_pOwnerobject->Get_Transform()->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos += m_vOffSet;
	vPos.y = 0.02f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = m_vSize.x;
	matWorld._22 = m_vSize.y;
	matWorld._33 = m_vSize.z;
	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);
}

HRESULT CEffect_Skill_Fire::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_skillrange_orange", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	return S_OK;
}

void CEffect_Skill_Fire::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_vOffSet = _vPos;
	m_vSize = _vSize;
	m_bActive = true;
}

CEffect_Skill_Fire* CEffect_Skill_Fire::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject)
{
	CEffect_Skill_Fire* pInstance = new CEffect_Skill_Fire(pGraphicDev, _pOwnerObject);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Skill Effect Fire Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Skill_Fire::Free()
{
	__super::Free();
}
