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

	// ���� �� ��ġ ����
	LERP_FLOAT_INFO m_tPosUpLerp; // ��ġ
	LERP_FLOAT_INFO m_tSizeUpLerp; // ������
	LERP_FLOAT_INFO m_tDeleteLerp; // �ӹ� �ð�
	LERP_FLOAT_INFO m_tTranslucentLerp; // ����

	_int			m_iLerpLevel;

	_float			m_iTranslucent; 

public:
	static CBingoSucces* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pPlayer);

private:
	virtual void				Free() override;
};

