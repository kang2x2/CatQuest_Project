#pragma once

/*

    �ݰ� �� �浹�� �����ϴ� ������Ʈ
    
    �浹�� �� ��ü�� ������ �ִ� ���ο��� �ݸ��� �޽����� �߻���Ų��.
    
    �÷��̾ ������ ��ų ���� �ݰ�, ������ �߰� �ݰ������ ����ϸ�ȴ�.
    
    �÷��̾ ���ʹ� �� ��ü�� ��������� ������, �ڽŵ��� Ready���� ���� �������ְ� �Ŵ�����Ʈ���� �����ָ� �ȴ�.
    
    ����� ���� ���� �ʴٸ� ��� ������ Set_Active()�Լ��� ���ְ�, ������ �� ���ִ� �͵� ���� ����̴�.

*/

#include "GameObject.h"

BEGIN(Engine)

END

class CRangeObj : public Engine::CGameObject
{
private:
    explicit CRangeObj(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius);
    explicit CRangeObj(const CRangeObj& rhs);
    virtual ~CRangeObj();


public:
    virtual HRESULT		Ready_Object() override;
    virtual _int		Update_Object(const _float& fTimeDelta) override;
    virtual void		LateUpdate_Object() override;
    virtual void		Render_Object() override;


public:
    virtual void		OnCollision_Enter(CGameObject* _pColObj);
    virtual void		OnCollision_Stay(CGameObject* _pColObj);
    virtual void		OnCollision_Exit(CGameObject* _pColObj);

    CGameObject*        Get_OwnerObj() const { return m_pOwnerObject; }

public:
    void                Set_Radius(const _float& _fRadius);
    const _float&       Get_Radius() const { return m_fRadius; }
    void                Set_Pos(const _vec3 _vPos) { m_vPos = _vPos; m_bSetPos = true; }

private:
    HRESULT				Add_Component();

private:
    CGameObject*        m_pOwnerObject;
    _float              m_fRadius;

    _vec3               m_vPos; // ���� �ֱ⵵ ���� 
    _bool               m_bSetPos;

public:
    static              CRangeObj* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const _float& _fRadius);

private:
    virtual void		Free() override;
};

