#include "stdafx.h"

#include "Effect_RainRipple.h"

#include "Export_Function.h"


CEffect_RainRipple::CEffect_RainRipple(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
	: CEffect(pGraphicDev, OBJ_ID::EFFECT_RAIN_RIPPLE)
{
	m_InitPos = pPos;
}

CEffect_RainRipple::CEffect_RainRipple(const CEffect_RainRipple& rhs)
	: CEffect(rhs), m_pTextureCom(rhs.m_pTextureCom)
{
}

CEffect_RainRipple::~CEffect_RainRipple()
{
}

HRESULT CEffect_RainRipple::Ready_Object()
{
	CGameObject::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	//m_fSpeed = 5 + rand() % 5;

	_float fMin = 1.f;
	_float fMax = 2.f;
	_float	fScale = fMin + (float)(rand()) / ((float)(RAND_MAX / (fMax - fMin)));
	fScale = floor(fScale * 100) / 100;
	m_pTransformCom->Set_Scale(_vec3{ fScale, fScale, fScale });


	m_pTransformCom->Set_Pos(m_InitPos);

	m_fAccTime = 0.f;

	/*m_vWindVelo.x = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.y = (double)rand() / RAND_MAX - 0.5;
	m_vWindVelo.z = (double)rand() / RAND_MAX - 0.5;*/

	std::mt19937 gen(m_Random());
	_int iMin = 0;
	_int iMax = 4;
	std::uniform_int_distribution<int> xDistX(iMin, iMax);
	m_iTexChoice = xDistX(gen);
	
	m_iAlpha = 150;
	m_tAlpha.Init_Lerp(LERP_MODE::SMOOTHSTEP);
	m_tAlpha.Set_Lerp(1.f, m_iAlpha, 0);
	m_tAlpha.fCurValue = m_tAlpha.fStartValue;

	m_bActive = true;

	return S_OK;
}

_int CEffect_RainRipple::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);


	//m_vWindVelo.x += (double)rand() / RAND_MAX * WINDFORCE - WINDFORCE / 2.0;
	//m_vWindVelo.y -= (double)rand() / RAND_MAX * WINDFORCE * 1;
	////m_vWindVelo.z += (double)rand() / RAND_MAX * WINDFORCE - WINDFORCE / 2.0;

	//m_pTransformCom->Set_Dir(m_vWindVelo);
	//m_pTransformCom->Translate(fTimeDelta * m_fSpeed);

	//_vec3 vRainPos = m_pTransformCom->Get_Info(INFO::INFO_POS);

	m_tAlpha.Update_Lerp(fTimeDelta);
	

	if(m_iAlpha <= 0)
		CEventMgr::GetInstance()->Delete_Obj(this);

	return iExit;
}

void CEffect_RainRipple::LateUpdate_Object()
{

	m_iAlpha = m_tAlpha.fCurValue;

	__super::LateUpdate_Object();
}

void CEffect_RainRipple::Render_Object()
{
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));

	_matrix matWorld = m_pTransformCom->Get_WorldMat();
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos.y = 0.02f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	m_pTextureCom->Render_Texture(m_iTexChoice);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

	__super::Render_Object();
}

HRESULT CEffect_RainRipple::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_RainRipple", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);

	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	return S_OK;
}

void CEffect_RainRipple::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
}

CEffect_RainRipple* CEffect_RainRipple::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 pPos)
{
	CEffect_RainRipple* pInstance = new CEffect_RainRipple(pGraphicDev, pPos);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect_RainRipple Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_RainRipple::Free()
{
	__super::Free();
}