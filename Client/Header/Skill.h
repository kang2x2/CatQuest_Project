#pragma once

#include "Engine_Define.h"
#include "GameObject.h"
#include "SoundMgr.h"
#include "Effect_Range_Quater.h"
#include "SkillEffect.h"

/*

	* �ش� Ŭ������ ��� �޾� �� ��ų�� �����ϵ��� �Ѵ�.
	
	* CSkillEffect
	* CEffect_Range_Quater
	* CCollier
	* CTransform
	

	- �÷��̾� / ����
		- ��ų ����
			- ��ų 1
				- ��ų ����Ʈ
				- ���� ����Ʈ
				- �ݶ��̴�
			- ��ų 2
				- ��ų ����Ʈ
				- ���� ����Ʈ
				- �ݶ��̴�
	����

	1. �÷��̾� �Ǵ� ���ʹ� �ڽ��� ����� ��ų�� ��������� ���´�(�� Ŭ���� Ÿ��) -> ���� ��ų ���� �����̳� ���

	2. ��ų�� �� Ŭ������ ��ӹ޾� ���� ��ų Ŭ������ �����Ѵ�.

		- �ϳ��� ��ų�� CSkillEffect / CEffect_Range_Quater / CCollier / CTransform�� ������ ���´�(CEffect_Range_Quater�� ����)

		- ��ų ����, CSkillEffect�� CEffect_Range_Quater�� ��� �Լ��� ȣ���ϵ��� �Ѵ�.

*/

class CSkillEffect;
class CEffect_Range_Quater;
class CRangeObj;

class CSkill : public CGameObject
{
protected:
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, const OBJ_ID& _eID);
	explicit CSkill(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pOwnerObject, const OBJ_ID& _eID);
	explicit CSkill(const CSkill& rhs);
	virtual ~CSkill();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

public:
	virtual void			OnCollision_Enter(CGameObject* _pColObj) {};
	virtual void			OnCollision_Stay(CGameObject* _pColObj) {};
	virtual void			OnCollision_Exit(CGameObject* _pColObj) {};

private:
	HRESULT					Add_Component();

public:
	virtual HRESULT			Play();
	virtual HRESULT			End();

	void					Set_SkillPlay(const _float& bPlay)		{ m_bPlay = bPlay; }
	const _bool				Is_End() const { return m_bPlay; }; // ��ų ������ ��������

	CGameObject*			Get_SkillOwner() { return m_pOwnerObject; }

	void					Set_SkillDamage(const _float& pDamage)  { m_fSkillDamage = pDamage; }
	void					Set_SkillUsage(const _uint& pUsage)	{ m_iSkillUsage = pUsage; }

	const _float&			Get_SkillDamage() const { return m_fSkillDamage; }
	const _uint&			Get_SkillUsage()  const { return m_iSkillUsage; }

	// ���� �߰�
	const D3DCOLOR& Get_SkillFontColor() const { return m_fontColor; }
	const wstring&  Get_SkillContent()   const { return m_contentStr; }

	_int			Get_SkillLv() { return m_iLv; }
	void			Skill_LvUp(_int _PlusLv) { m_iLv += _PlusLv; }

protected:
	CGameObject*			m_pOwnerObject;
	_bool					m_bPlay;

	CSkillEffect*			m_pSKillEffect; // ���̳� �� ���� ��ų
	CEffect_Range_Quater*	m_pRangeEffect; // ��ų �Ʒ� �򸮴� ����
	
	CGameObject*			m_pRangeObj;

	_float					m_fSkillDamage;
	_uint					m_iSkillUsage;

	_bool					m_bAttackStart;

	// ���� �߰�
	D3DCOLOR				m_fontColor;
	wstring					m_contentStr;
	_int					m_iLv;


protected:
	virtual void			Free();
};

