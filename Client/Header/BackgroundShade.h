#pragma once
#include "UI.h"


BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CBackgroundShade : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:

	explicit CBackgroundShade(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBackgroundShade(const CBackgroundShade& rhs);
	virtual ~CBackgroundShade();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	virtual HRESULT			Add_Component() override;

private:
	_matrix					m_matWorld;

public:

	static CBackgroundShade* Create(LPDIRECT3DDEVICE9 pGraphicDev);

protected:
	virtual void			Free() override;
};

