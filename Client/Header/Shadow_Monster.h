#pragma once
#include "Effect.h"

BEGIN(Engine)

class CTexture;

END

class CShadow_Monster : public CEffect
{
	explicit CShadow_Monster(LPDIRECT3DDEVICE9 pGraphicDev,
		CGameObject* _pOwnerObject, _float _fDistanceY, _float _fSize);
	explicit CShadow_Monster(const CShadow_Monster& rhs);
	virtual ~CShadow_Monster();

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

	_float    m_InitY;
	_float    m_fMonsterCurY; // ������ ���� ���� ( �׸��� ũ�⿡�� ���ش�.)
	_float    m_fDistanceY;   // �� ������ ����� �°� �Ű��� �޴´�. 
							  // �̿� ���� �׸����� ũ�Ⱑ ��������.)
	_float    m_fShadowSize;  // �׸����� ũ�� 

public:
	static CShadow_Monster* Create(LPDIRECT3DDEVICE9 pGraphicDev,
		CGameObject* _pOwnerObject, _float _fDistanceY, _float _fSize);

private:
	virtual void				Free() override;
};

