#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CBingoSucces : public CEffect
{
	explicit CBingoSucces(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer);
	explicit CBingoSucces(const CBingoSucces& rhs);
	virtual ~CBingoSucces();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

	void						Ready_Lerp();

private:
	HRESULT						Add_Component();

private:
	CTexture*		m_pTextureCom;
	CGameObject*	m_pPlayer;

	// 알파 및 위치 러프
	LERP_FLOAT_INFO m_tPosUpLerp; // 위치
	LERP_FLOAT_INFO m_tSizeUpLerp; // 사이즈
	LERP_FLOAT_INFO m_tDeleteLerp; // 머물 시간
	LERP_FLOAT_INFO m_tTranslucentLerp; // 투명도

	_int			m_iLerpLevel;

	_float			m_iTranslucent; 

public:
	static CBingoSucces* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer);

private:
	virtual void				Free() override;
};

