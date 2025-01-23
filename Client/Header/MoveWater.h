#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;
class CAnimation;

END

class CMoveWater : public CEffect
{
	// 상태에 따라 처리해야하기에 주인보다는 위치 자체를 넘겨주는게 나아보인다.
	explicit CMoveWater(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject);
	explicit CMoveWater(const CMoveWater& rhs);
	virtual ~CMoveWater();

public:
	virtual HRESULT				Ready_Object() override;
	virtual _int				Update_Object(const _float& fTimeDelta) override;
	virtual void				LateUpdate_Object() override;
	virtual void				Render_Object() override;

private:
	HRESULT						Add_Component();
	virtual void				Play_Effect(const _vec3& _vPos, const _vec3& _vSize = vec3.one) override;

private:
	CTexture* m_pTextureCom;
	CAnimation* m_pAnimation;
	_int		m_iTranslucent;
public:
	static CMoveWater* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject); // 구름이 생성되는 위치를 위해서라도 주인이 필요할 듯

private:
	virtual void				Free() override;
};

