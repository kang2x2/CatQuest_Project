#pragma once
#include "UI.h"
#include "GameObject.h"

#define MAX_SPARKLE_SIZE 8

BEGIN(Engine)

class CTexture;

END

struct tagWeaponSparkle
{
	CTexture*		m_pSparkleTexCom;
	_matrix			m_matSparkle;
	_float			m_fTempSize; // 메트릭스에 바로 사이즈를 정하면 처음 1프레임 원상태로 시작한다.
	LERP_FLOAT_INFO m_tMoveLerpX;
	LERP_FLOAT_INFO m_tMoveLerpY;
	LERP_FLOAT_INFO m_tSizeUpLerp;
	LERP_FLOAT_INFO m_tSizeDownLerp;
};

class CWeaponGetEffect : public CUI     // 뷰포트 사용 | 화면에 고정된 표시를 위한 UI  프로토타입 입니다.
{

protected:
	explicit CWeaponGetEffect(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon);
	explicit CWeaponGetEffect(const CWeaponGetEffect& rhs);
	virtual ~CWeaponGetEffect();

public:
	virtual HRESULT			Ready_Object() override;
	virtual _int			Update_Object(const _float& fTimeDelta) override;
	virtual void			LateUpdate_Object() override;
	virtual void			Render_Object() override;

private:
	// 초기화
	void					Ready_WeaponGlow();
	void					Ready_WeaponShine();
	void					Ready_Sparkle();
	// 업데이트
	void					Random_Move();
	void					Smaller_Weapon();
	void					Sudden_Weapon();

private:
	virtual HRESULT			Add_Component() override;

private:
	// 사운드
	_bool			m_bReadySound;
	// 알파효과 주면서 생성
	_bool			m_ReadyEffect; // 알파 다 채워지면 시작
	LERP_FLOAT_INFO	m_tReadyEffectLerp; // 알파 시작 러프
	// 알파효과 주면서 지우기
	_bool			m_bResultStay;
	_int			m_iStayCount2;

	_int			m_iAllTranslucent;

#pragma region 스킬 및 글로우
	_float			 m_fCurWeaponSizeX; // 실시간 크기
	_float			 m_fCurWeaponSizeY; // 실시간 크기

	CGameObject*	 m_pWeapon;	 // 해당 스킬
	CTexture*		 m_pWeaponTexCom; // 무기 텍스쳐
	CTexture*		 m_pGlowTexCom; // 글로우 텍스쳐
	_matrix			 m_matGlow;     // 무기과 글로우의 월드
	LERP_FLOAT_INFO  m_tRandomMoveLerpX; // 랜덤하게 계속 쉐이킹 하기 위함
	LERP_FLOAT_INFO  m_tRandomMoveLerpY; // 랜덤하게 계속 쉐이킹 하기 위함
	LERP_FLOAT_INFO  m_tSmallerLerpX; // 점점 작아지는 러프
	LERP_FLOAT_INFO  m_tSmallerLerpY; // 점점 작아지는 러프
	LERP_FLOAT_INFO  m_tSuddenWeaponLerpX; // 갑자기 확 커지는 러프
	LERP_FLOAT_INFO  m_tSuddenWeaponLerpY; // 갑자기 확 커지는 러프
	LERP_FLOAT_INFO  m_tReturnWeaponSizeLerpX; // 원상태로 작아지는 러프
	LERP_FLOAT_INFO  m_tReturnWeaponSizeLerpY; // 원상태로 작아지는 러프


	_int			 m_iRandValue; // 무기 위치 랜덤 변수
	_int			 m_iWeaponAlpha; // 무기 알파 변수

	_int			 m_iStayCount; // 갑자기 커지기 전 대기
	_bool			 m_bTimeSet;   // 갑자기 커지기 전 대기 시간인지
	_bool			 m_bSizeUp;    // 갑자기 커지기 스위치
#pragma endregion

#pragma region 샤이닝
	_float			 m_fCurShineSize;
	CTexture*		 m_pShineTexCom; // 샤이닝 텍스쳐
	CTransform*		 m_pShineTransCom;	 // 샤이닝 월드
	_matrix			 m_matShine;

	LERP_FLOAT_INFO  m_tSuddenShineLerp; // 갑자기 확 커지는 러프
	LERP_FLOAT_INFO  m_tReturnShineSizeLerp; // 원상태로 작아지는 러프
#pragma endregion

#pragma region 스파클
	tagWeaponSparkle m_SparkleAry[MAX_SPARKLE_SIZE];
#pragma endregion

public:

	static CWeaponGetEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, CGameObject* _pWeapon);

protected:
	virtual void			Free() override;
};

