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
	_float			m_fTempSize; // 메트릭스에 바로 사이즈를 정하면 처음 1프레임 원상태로 시작한다.
	LERP_FLOAT_INFO m_tMoveLerpX;
	LERP_FLOAT_INFO m_tMoveLerpY;
	LERP_FLOAT_INFO m_tSizeUpLerp;
	LERP_FLOAT_INFO m_tSizeDownLerp;
};

class CSkillGetEffect : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
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
	// 초기화
	void					Ready_SkillGlow();
	void					Ready_SkillShine();
	void					Ready_Sparkle();
	// 업데이트
	void					Random_Move();
	void					Smaller_Skill();
	void					Sudden_Skill();

private:
	virtual HRESULT			Add_Component() override;

private:
	_bool			m_bReadySound;
	// 알파효과 주면서 생성
	_bool			m_ReadyEffect; // 알파 다 채워지면 시작
	LERP_FLOAT_INFO	m_tReadyEffectLerp; // 알파 시작 러프
	// 알파효과 주면서 지우기
	// _bool	  m_bDelete;
	_bool			m_bResultStay;
	_int			m_iStayCount2;
	_int			m_iAllTranslucent;
	
#pragma region 스킬 및 글로우
	_float			 m_fCurSkillSize; // 실시간 크기

	CSkill*			 m_pSkill;	 // 해당 스킬
	CTexture*		 m_pSkillTexCom; // 스킬 텍스쳐
	CTexture*		 m_pGlowTexCom; // 글로우 텍스쳐
	_matrix			 m_matGlow;     // 스킬과 글로우의 월드
	LERP_FLOAT_INFO  m_tRandomMoveLerpX; // 랜덤하게 계속 쉐이킹 하기 위함
	LERP_FLOAT_INFO  m_tRandomMoveLerpY; // 랜덤하게 계속 쉐이킹 하기 위함
	LERP_FLOAT_INFO  m_tSmallerLerp; // 점점 작아지는 러프
	LERP_FLOAT_INFO  m_tSuddenSkillLerp; // 갑자기 확 커지는 러프
	LERP_FLOAT_INFO  m_tReturnSkillSizeLerp; // 원상태로 작아지는 러프


	_int			 m_iRandValue; // 스킬 위치 랜덤 변수
	_int			 m_iSkillAlpha; // 스킬 알파 변수

	_int			 m_iStayCount; // 갑자기 커지기 전 대기
	_bool			 m_bTimeSet;   // 갑자기 커지기 전 대기 시간인지
	_bool			 m_bSizeUp;    // 갑자기 커지기 스위치
#pragma endregion

#pragma region 샤이닝
	_float			 m_fCurShineSize;
	CTexture*		 m_pShineTexCom; // 샤이닝 텍스쳐
	CTransform*	     m_pShineTransCom;	 // 샤이닝 월드
	_matrix			 m_matShine;

	LERP_FLOAT_INFO  m_tSuddenShineLerp; // 갑자기 확 커지는 러프
	LERP_FLOAT_INFO  m_tReturnShineSizeLerp; // 원상태로 작아지는 러프
#pragma endregion

#pragma region 스파클
	tagSparkle m_SparkleAry[MAX_SPARKLE_SIZE];
#pragma endregion

public:

	static CSkillGetEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, CSkill* _pSkill);

protected:
	virtual void			Free() override;
};

