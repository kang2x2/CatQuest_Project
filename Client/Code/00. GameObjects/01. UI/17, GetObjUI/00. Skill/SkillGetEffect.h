#pragma once
#include "UI.h"
#include "Skill.h"

#define MAX_SPARKLE_SIZE 8

BEGIN(Engine)

class CTexture;

END


struct tagSparkle
{
	CTexture*		m_pSparkleTexCom;
	_matrix			m_matSparkle;
	_float			m_fTempSize; // ��Ʈ������ �ٷ� ����� ���ϸ� ó�� 1������ �����·� �����Ѵ�.
	LERP_FLOAT_INFO m_tMoveLerpX;
	LERP_FLOAT_INFO m_tMoveLerpY;
	LERP_FLOAT_INFO m_tSizeUpLerp;
	LERP_FLOAT_INFO m_tSizeDownLerp;
};

class CSkillGetEffect : public CUI     // ����Ʈ ��� | ȭ�鿡 ������ ǥ�ø� ���� UI  ������Ÿ�� �Դϴ�.
{

protected:
	explicit CSkillGetEffect(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill);
	explicit CSkillGetEffect(const CSkillGetEffect& rhs);
	virtual ~CSkillGetEffect();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	// �ʱ�ȭ
	void					Ready_SkillGlow();
	void					Ready_SkillShine();
	void					Ready_Sparkle();
	// ������Ʈ
	void					Random_Move();
	void					Smaller_Skill();
	void					Sudden_Skill();

private:
	virtual HRESULT			Add_Component() override;

private:
	_bool			m_bReadySound;
	// ����ȿ�� �ָ鼭 ����
	_bool			m_ReadyEffect; // ���� �� ä������ ����
	LERP_FLOAT_INFO	m_tReadyEffectLerp; // ���� ���� ����
	// ����ȿ�� �ָ鼭 �����
	// _bool	  m_bDelete;
	_bool			m_bResultStay;
	_int			m_iStayCount2;
	_int			m_iAllTranslucent;
	
#pragma region ��ų �� �۷ο�
	_float			 m_fCurSkillSize; // �ǽð� ũ��

	CSkill*			 m_pSkill;	 // �ش� ��ų
	CTexture*		 m_pSkillTexCom; // ��ų �ؽ���
	CTexture*		 m_pGlowTexCom; // �۷ο� �ؽ���
	_matrix			 m_matGlow;     // ��ų�� �۷ο��� ����
	LERP_FLOAT_INFO  m_tRandomMoveLerpX; // �����ϰ� ��� ����ŷ �ϱ� ����
	LERP_FLOAT_INFO  m_tRandomMoveLerpY; // �����ϰ� ��� ����ŷ �ϱ� ����
	LERP_FLOAT_INFO  m_tSmallerLerp; // ���� �۾����� ����
	LERP_FLOAT_INFO  m_tSuddenSkillLerp; // ���ڱ� Ȯ Ŀ���� ����
	LERP_FLOAT_INFO  m_tReturnSkillSizeLerp; // �����·� �۾����� ����


	_int			 m_iRandValue; // ��ų ��ġ ���� ����
	_int			 m_iSkillAlpha; // ��ų ���� ����

	_int			 m_iStayCount; // ���ڱ� Ŀ���� �� ���
	_bool			 m_bTimeSet;   // ���ڱ� Ŀ���� �� ��� �ð�����
	_bool			 m_bSizeUp;    // ���ڱ� Ŀ���� ����ġ
#pragma endregion

#pragma region ���̴�
	_float			 m_fCurShineSize;
	CTexture*		 m_pShineTexCom; // ���̴� �ؽ���
	CTransform*	     m_pShineTransCom;	 // ���̴� ����
	_matrix			 m_matShine;

	LERP_FLOAT_INFO  m_tSuddenShineLerp; // ���ڱ� Ȯ Ŀ���� ����
	LERP_FLOAT_INFO  m_tReturnShineSizeLerp; // �����·� �۾����� ����
#pragma endregion

#pragma region ����Ŭ
	tagSparkle m_SparkleAry[MAX_SPARKLE_SIZE];
#pragma endregion

public:

	static CSkillGetEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill);

protected:
	virtual void			Free() override;
};

