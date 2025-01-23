#pragma
#include "GameObject.h"
#include "FlagOwner.h"
#include "FlagStart.h"
#include "Bingo_Launcher.h"
#include "Flag.h"

BEGIN(Engine)

class CMiniGameMgr_Bingo : public CBase
{
	DECLARE_SINGLETON(CMiniGameMgr_Bingo)
private:
	explicit CMiniGameMgr_Bingo();
	virtual ~CMiniGameMgr_Bingo();
	
public:
	HRESULT	Init(LPDIRECT3DDEVICE9 _pGraphicDev);
	void	Update(const _float& _fDelta);
	
	void	ShowFlag();

public:
	_bool	Get_IsInit() { return m_bInit; } // 최초 초기화

	_bool	Get_Active()				  { return m_bActive; } // 활성 상태 확인
	void	Set_Active(_bool _isActive)   { m_bActive = _isActive; } // 활성화 

	_bool	Get_FlagShow()				  { return m_bShowFlag; }
	void	Set_FlagShow(_bool _isShow)	  { m_bShowFlag = _isShow; }

	// 게임 한 번 끝냈으면 다시 못한다
	_bool	Get_GameOver()				  { return m_bGameOver; }
public:
	HRESULT	Flag_Check(const OBJ_ID& _eID);

	_bool	Get_GameReady() { return m_bGameReady; }
	void	Set_GameReady() { m_bGameReady = true; }

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev; // 디바이스
	CFlagOwner*				m_pFlagOwner;  // 오너 정보
	CBingo_Launcher*		m_pLauncher;   // 빙고 장치(애를 주석하는데 왜 안됨?)
	vector<CFlag*>			m_FlagVector;  // 국기 저장.
	vector<CFlag*>			m_BingoVector; // 정답 국기 저장.
	CFlagStart*				m_pStartFlag;  // 가운데 빈 국기

	_bool	m_bInit; // 최초 초기화
	_bool	m_bPushVec; // 벡터에 최초 삽입.
	_bool	m_bStart; // 게임 세팅
	_bool	m_bShuffle; // 한 번 섞기
	_bool	m_bActive; // 활성화 상태
	_bool	m_bShowFlag; // 정답 국기 보여주는 상태

	_int	m_iSetIndex; // 하나 하나 알파 보간 위한 인덱스
	_int	m_iIndex; // 게임 진행 인덱스
	_int	m_iShowIndex; // 보여주기 인덱스
	_int	m_iLevel; // 레벨
	_int	m_iBingoCount; // 총 저장할 개수

	LERP_FLOAT_INFO	m_tShowAgainLerp; // 다시 보여주기 러프
	_bool			m_bShowAgain; // 다시 보기 러프 실행 여부
	_bool			m_bFirstSound; // 첫 번째 사운드

	LERP_FLOAT_INFO	m_tFlagShowLerp; // 국기 중간 텀
	LERP_FLOAT_INFO m_tGameOverLerp; // 국기 제거 전 텀
	_bool			m_bGameClear; // 게임 끝
	_bool			m_bGameOver; // 게임 끝

	LERP_FLOAT_INFO	m_tFistWaveLerp; // 트랩 생성 (전체)
	LERP_FLOAT_INFO	m_tFistCreateLerp; // 트랩 생성 (개별)
	_bool			m_bDropFist;	 // 트랩 활성화

	_bool			m_bGameReady; // 퀘스트 진행을 위한 게임 레디 변수
private:
	virtual void			Free();
};

END