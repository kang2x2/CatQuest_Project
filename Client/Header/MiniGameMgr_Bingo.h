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
	_bool	Get_IsInit() { return m_bInit; } // ���� �ʱ�ȭ

	_bool	Get_Active()				  { return m_bActive; } // Ȱ�� ���� Ȯ��
	void	Set_Active(_bool _isActive)   { m_bActive = _isActive; } // Ȱ��ȭ 

	_bool	Get_FlagShow()				  { return m_bShowFlag; }
	void	Set_FlagShow(_bool _isShow)	  { m_bShowFlag = _isShow; }

	// ���� �� �� �������� �ٽ� ���Ѵ�
	_bool	Get_GameOver()				  { return m_bGameOver; }
public:
	HRESULT	Flag_Check(const OBJ_ID& _eID);

	_bool	Get_GameReady() { return m_bGameReady; }
	void	Set_GameReady() { m_bGameReady = true; }

private:
	LPDIRECT3DDEVICE9		m_pGraphicDev; // ����̽�
	CFlagOwner*				m_pFlagOwner;  // ���� ����
	CBingo_Launcher*		m_pLauncher;   // ���� ��ġ(�ָ� �ּ��ϴµ� �� �ȵ�?)
	vector<CFlag*>			m_FlagVector;  // ���� ����.
	vector<CFlag*>			m_BingoVector; // ���� ���� ����.
	CFlagStart*				m_pStartFlag;  // ��� �� ����

	_bool	m_bInit; // ���� �ʱ�ȭ
	_bool	m_bPushVec; // ���Ϳ� ���� ����.
	_bool	m_bStart; // ���� ����
	_bool	m_bShuffle; // �� �� ����
	_bool	m_bActive; // Ȱ��ȭ ����
	_bool	m_bShowFlag; // ���� ���� �����ִ� ����

	_int	m_iSetIndex; // �ϳ� �ϳ� ���� ���� ���� �ε���
	_int	m_iIndex; // ���� ���� �ε���
	_int	m_iShowIndex; // �����ֱ� �ε���
	_int	m_iLevel; // ����
	_int	m_iBingoCount; // �� ������ ����

	LERP_FLOAT_INFO	m_tShowAgainLerp; // �ٽ� �����ֱ� ����
	_bool			m_bShowAgain; // �ٽ� ���� ���� ���� ����
	_bool			m_bFirstSound; // ù ��° ����

	LERP_FLOAT_INFO	m_tFlagShowLerp; // ���� �߰� ��
	LERP_FLOAT_INFO m_tGameOverLerp; // ���� ���� �� ��
	_bool			m_bGameClear; // ���� ��
	_bool			m_bGameOver; // ���� ��

	LERP_FLOAT_INFO	m_tFistWaveLerp; // Ʈ�� ���� (��ü)
	LERP_FLOAT_INFO	m_tFistCreateLerp; // Ʈ�� ���� (����)
	_bool			m_bDropFist;	 // Ʈ�� Ȱ��ȭ

	_bool			m_bGameReady; // ����Ʈ ������ ���� ���� ���� ����
private:
	virtual void			Free();
};

END