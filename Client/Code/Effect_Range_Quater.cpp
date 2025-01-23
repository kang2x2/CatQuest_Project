#include "stdafx.h"
#include "Effect_Range_Quater.h"

#include "Export_Function.h"

_float MyLerp(const _float& _f1, const _float& _f2, const _float _fTime)
{
	return (1 - _fTime) * _f1 + (_fTime * _f2);
}

CEffect_Range_Quater::CEffect_Range_Quater(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const EFFECT_RANGE_QUATER_TYPE& _eType)
	: CSkillEffect(pGraphicDev, _pOwnerObject, OBJ_ID::EFFECT_RANGE)
	, m_eType(_eType)
{
	ZeroMemory(&m_eAlphaInfo, sizeof(LERP_FLOAT_INFO));
	ZeroMemory(&m_eScaleInfo, sizeof(LERP_FLOAT_INFO));
}

CEffect_Range_Quater::CEffect_Range_Quater(const CEffect& rhs)
	: CSkillEffect(rhs)
{
}

CEffect_Range_Quater::~CEffect_Range_Quater()
{
}

HRESULT CEffect_Range_Quater::Ready_Object()
{
	__super::Ready_Object();

	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	switch (m_eType)
	{
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_ATTACK:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE:  // New
	{
		m_pTransformCom->Set_Scale(_vec3{ 5.f, 5.f, 5.f * 0.7f }); 
		m_vSize = m_pTransformCom->Get_Scale();
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_RED:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_PURPLE:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_GOLD:
	{
		m_pTransformCom->Set_Scale(_vec3{ 5.f, 5.f, 5.f * 0.7f }); 
		m_vSize = m_pTransformCom->Get_Scale();
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_PURPLE: // New
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_RED:
	{
		m_pTransformCom->Set_Scale(_vec3{ 5.f, 5.f, 5.f * 0.7f }); 
		m_vSize = m_pTransformCom->Get_Scale();
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_BLUE:
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_GOLD:
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_RED:
	{
		m_pTransformCom->Set_Scale(_vec3{ 7.f, 7.f, 2.5f * 0.7f });
		m_vSize = m_pTransformCom->Get_Scale();
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_BLUE: // New
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_RED:
	{
		m_pTransformCom->Set_Scale(_vec3{ 2.f, 7.f, 5.f });
		m_vSize = m_pTransformCom->Get_Scale();
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SMALL_RED:
	{
		m_pTransformCom->Set_Scale(_vec3{ 2.f,2.f, 2.f * 0.7f });
	}

	default:
		break;
	}


	m_eScaleInfo.fCurValue = 1.f;
	m_eAlphaInfo.fCurValue = 255.f;
	m_vLerpSize = m_vSize;

	return S_OK;
}

_int CEffect_Range_Quater::Update_Object(const _float& fTimeDelta)
{
	//if (!m_eScaleInfo.bActive) // Test
	//{
	//	Scaling(1.f, 0.5f, 1.f);
	//	Alphaing(1.f, 0.f, 255.f);
	//}
	
	_int iExit = CGameObject::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_eScaleInfo.Update_Lerp(fTimeDelta);
	m_vLerpSize = m_vSize * m_eScaleInfo.fCurValue;
	m_eAlphaInfo.Update_Lerp(fTimeDelta);

	return iExit;
}

void CEffect_Range_Quater::LateUpdate_Object()
{
	__super::LateUpdate_Object();
}

void CEffect_Range_Quater::Render_Object()
{
	// 알파 값 설정	
	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(_int(m_eAlphaInfo.fCurValue), 255, 255, 255));

	// 텍스처 보간 설정 변경 
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	// 빌보드 해제
	_matrix matWorld = Get_Transform()->Get_WorldMat();
	matWorld._41 -= m_vLerpSize.x;
	matWorld._43 += m_vLerpSize.y;
	_matrix matBill;
	_vec3 vPos;

	memcpy(&vPos, &matWorld.m[3], sizeof(_vec3));
	vPos += m_vOffSet;
	vPos.y = 0.02f;

	matWorld *= *D3DXMatrixInverse(&matBill, NULL, &CCameraMgr::GetInstance()->Get_Billboard_X());
	memcpy(&matWorld.m[3], &vPos, sizeof(_vec3));

	matWorld._11 = m_vLerpSize.x;
	matWorld._22 = m_vLerpSize.y;
	matWorld._33 = m_vLerpSize.z;

	m_pTextureCom->Render_Texture(); // 텍스처 세팅 -> 버퍼 세팅 순서 꼭!

	switch (m_eType)
	{
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_ATTACK:
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE:
	{
		Render_Circle(matWorld);
	}
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_PURPLE:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_GOLD:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_RED:
	{	
		Render_Square(matWorld);
	}
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_PURPLE: // New
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_RED:
	{
	
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_BLUE:
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_GOLD:
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_RED:
	{
		Render_Arrow(matWorld);
	}
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_BLUE: // New
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_RED:
	{
		matWorld._43 += 5.f;
		Render_Arrow(matWorld);
	}
	break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SMALL_RED:
	{
		Render_CompleteShape(matWorld);
	}
		break;

	default:
		break;
	}


	//텍스처 보간 설정 되돌림
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pGraphicDev->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
}


void CEffect_Range_Quater::Play_Effect(const _vec3& _vPos, const _vec3& _vSize)
{
	m_pTransformCom->Set_Pos(_vec3{ _vPos.x, m_pTransformCom->Get_Info(INFO::INFO_POS).y, _vPos.z - 5.2f });
	m_bActive = true;
}

void CEffect_Range_Quater::Scaling(const _float& _fTime, const _float _fStartMag, const _float& _fTargetMag)
{
	m_eScaleInfo.Init_Lerp();
	m_eScaleInfo.Set_Lerp(_fTime, _fStartMag, _fTargetMag);
}

void CEffect_Range_Quater::Alphaing(const _float& _fTime, const _float _fStartValue, const _float& _fTargetValue)
{
	m_eAlphaInfo.Init_Lerp();
	m_eAlphaInfo.Set_Lerp(_fTime, _fStartValue, _fTargetValue);
}

void CEffect_Range_Quater::Render_Circle(_matrix& matWorld)
{
	// LT
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	// RT
	matWorld._41 += m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//RB 
	matWorld._43 -= m_vLerpSize.z * 2.f;
	matWorld._33 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//LB 
	matWorld._41 -= m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();
}

void CEffect_Range_Quater::Render_Arrow(_matrix& matWorld)
{
	// LT
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	// RT
	matWorld._41 += m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//RB 
	matWorld._43 -= m_vLerpSize.z * 2.f;
	matWorld._33 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//LB 
	matWorld._41 -= m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();
}

void CEffect_Range_Quater::Render_Square(_matrix& matWorld)
{
	// LT
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	// RT
	matWorld._41 += m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//RB 
	matWorld._43 -= m_vLerpSize.z * 2.f;
	matWorld._33 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	//LB 
	matWorld._41 -= m_vLerpSize.x * 2.f;
	matWorld._11 *= -1.f;
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();
}


void CEffect_Range_Quater::Render_Rotated_Square(_matrix& matWorld)
{
}

void CEffect_Range_Quater::Render_CompleteShape(_matrix& matWorld)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

}

HRESULT CEffect_Range_Quater::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CTerrainRcTex*>(Engine::Clone_Proto(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::BUFFER_TERRAIN_RC_TEX, pComponent);

	switch (m_eType)
	{
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_RED:
		//pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Red", this)); // 원래 이미지 크기
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_BigRangeSkill_Circle_Red", this));	// 확장한 이미지 크기
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SKILL_YELLOW:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Circle_Big_Yellow", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_ATTACK:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Attack_Circle_Red", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_PURPLE:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_PURPLE:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Purple", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_GOLD:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Gold", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_RED:
	case Engine::EFFECT_RANGE_QUATER_TYPE::SQUARE_ROTATED_RED:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Square_Red", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_BLUE:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Blue", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_GOLD:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Gold", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_BLUE:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Vertical_Arrow_Blue", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_RED:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Arrow_Red", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::ARROW_VERTICAL_RED:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Vertical_Arrow_Red", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_SMALL_RED:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_Range_Skill_Small_Red", this));
		break;
	case Engine::EFFECT_RANGE_QUATER_TYPE::CIRCLE_LARGE_PURPLE:
		pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Texture(L"Proto_Texture_Effect_range_Purple", this));
	default:
		break;
	}
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(COMPONENT_TYPE::TEXTURE, pComponent);


	return S_OK;
}

CEffect_Range_Quater* CEffect_Range_Quater::Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const EFFECT_RANGE_QUATER_TYPE& _eType)
{
	CEffect_Range_Quater* pInstance = new CEffect_Range_Quater(pGraphicDev, _pOwnerObject, _eType);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Effect Range Quater Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CEffect_Range_Quater::Free()
{
	__super::Free();
}