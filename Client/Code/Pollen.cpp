#include "stdafx.h"
#include "Pollen.h"

#include "Export_Function.h"

#include "Cloud1_Shadow.h"

CPollen::CPollen(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_POLLEN)
{
	m_InitPos = pPos;
}

CPollen::CPollen(const CPollen& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CPollen::~CPollen()
{
}

HRESULT CPollen::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_fSpeed = 10 + rand() % 5;

	_float fMin = 0.1;
	_float fMax = 0.25;
	_float	fScale = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	fScale = floor(fScale * 100) / 100;
	m_pTransformCom->Set_Scale(_vec3{ fScale, fScale, fScale });


	fMin = 0.3;
	fMax = 0.8;
	_float	fDirZ = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	m_fDirZ = floor(fDirZ * 10) / 10;


	m_InitPos.y += 2.f + rand() % 3;
	m_pTransformCom->Set_Pos(m_InitPos);

	m_fAccTime = 0.f;

	m_vWindVelo.x = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.y = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.z = (double)rand() / RAND_MAX - 0.5;

	m_bActive = true;

	return S_OK;
}

_int CPollen::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	m_vWindVelo.x += (double)rand() / RAND_MAX * WINDFORCE * 1;
	m_vWindVelo.y += (double)rand() / RAND_MAX * WINDFORCE - WINDFORCE / 2.0;
	m_vWindVelo.z += (double)rand() / RAND_MAX * WINDFORCE * m_fDirZ;

	m_pTransformCom->Set_Dir(m_vWindVelo);
	m_pTransformCom->Translate(fTimeDelta * m_fSpeed);


	m_fAccTime += fTimeDelta;
	if (m_fAccTime >= 12.f)
		CEventMgr::GetInstance()->Delete_Obj(this);

	return iExit;
}

void CPollen::LateUpdate_Object()
{
	_vec3 vPollenPos = m_pTransformCom->Get_Info(INFO::INFO_POS);

	CGameObject* pPlayer = CManagement::GetInstance()->Get_GameObject(OBJ_TYPE::PLAYER, L"Player");
	NULL_CHECK(pPlayer);
	_vec3 vPlayerPos = pPlayer->Get_Transform()->Get_Info(INFO::INFO_POS);

	_vec3 vDis = vPollenPos - vPlayerPos;
	_float fLength = D3DXVec3Length(&vDis);
	D3DXVec3Normalize(&vDis, &vDis);

	if(fLength > 50 && vDis.x > 0)
		CEventMgr::GetInstance()->Delete_Obj(this);

	__super::LateUpdate_Object();
}

void CPollen::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(200, 255, 255, 255));

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_WorldMat());

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetTexture(0, NULL);

	m_pGraphicDev->SetMaterial(&material.Get_Meretial(color.white));

	CEffect::Render_Object();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CPollen::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Pollen", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_RC_TEX, pComponent);

	return S_OK;
}

void CPollen::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

CPollen* CPollen::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
{
	CPollen* pInstance = new CPollen(pGraphicDev, pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_Pollen Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CPollen::Free()
{
	__super::Free();
}
