#pragma once

#include "Base.h"
#include "Engine_Define.h"


class CSkyBox;

BEGIN(Engine)

class CGameObject;

END

class CFogMgr : public CBase
{
	DECLARE_SINGLETON(CFogMgr)

private:
	explicit CFogMgr();
	virtual ~CFogMgr();

public:
	HRESULT					Ready_FogMgr(LPDIRECT3DDEVICE9 _pGraphicDev);
	void					Update_FogMgr(const _float& fTimeDelta);

public:
	const _bool&			Is_Ready_FogMgr() const { return m_bReady; }

public:
	void					Start_Lerp_Near(const _float& _fTime, const _float& _fStart, const _float& _fEnd, const LERP_MODE& _eMode);
	void					Start_Lerp_Far(const _float& _fTime, const _float& _fStart, const _float& _fEnd, const LERP_MODE& _eMode);

	const _bool				Is_Lerp_Near() const { return m_tLerpNear.bActive; }
	const _bool				Is_Lerp_Far() const { return m_tLerpFar.bActive; }

	const _float& Get_Lerp_Near() const { return m_tLerpNear.fCurValue; }
	const _float& Get_Lerp_Far() const { return m_tLerpFar.fCurValue; }
private:
	void					Set_Fog();


private:
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	_bool					m_bReady;

	LERP_VEC3_INFO			m_tLerpColor;

	LERP_FLOAT_INFO			m_tLerpNear;
	LERP_FLOAT_INFO			m_tLerpFar;
private:
	virtual void			Free();
};



