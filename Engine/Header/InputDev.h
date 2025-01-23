#ifndef InputDev_h__
#define InputDev_h__

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CInputDev : public CBase
{
	DECLARE_SINGLETON(CInputDev)

private:
	explicit CInputDev(void);
	virtual ~CInputDev(void);
	
public:
	// API �� ����ϴ� Ű ��ǲ �Լ�
	_bool			Key_Pressing(_int _iKey);
	_bool			Key_Down(_int _iKey);
	_bool			Key_Up(_int _iKey);

	_byte			Get_DIKeyState(_ubyte byKeyID)				{ return m_byKeyState[byKeyID]; }
	_byte			Get_DIMouseState(MOUSEKEYSTATE eMouse) 		{ return m_tMouseState.rgbButtons[eMouse]; 	}
	_long			Get_DIMouseMove(MOUSEMOVESTATE eMouseState)	{ return *(((_long*)&m_tMouseState) + eMouseState); } // ���콺 ���� ��ǲ ����
																																/*
							
							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Y))
							{
								// ��ũ�� ��ǥ�踦 �������� ���� �����ӿ��� ������������ ���콺 y������ ���̸� ��ȯ�Ѵ�.
								// ���콺�� �ø��� -��, ������ +��
							}

							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_X))
							{
								// ��ũ�� ��ǥ�踦 �������� ���� �����ӿ��� ������������ ���콺 x������ ���̸� ��ȯ�Ѵ�.
								// ���콺�� ���������� �ϸ� +��, �������� �ϸ� -��
							}

							if (dwMouse = CInputDev::GetInstance()->Get_DIMouseMove(DIMS_Z))
							{
								// ���� ��ũ�� �ϸ� 120 ��ȯ
								// �Ʒ��� ��ũ�� �ϸ� -120 ��ȯ
							}

							*/

public:
	HRESULT					Ready_InputDev(HINSTANCE hInst, HWND hWnd);
	void					Update_InputDev(void);	// �� ������Ʈ ���� ��ǲ ���¸� �����Ѵ� (Main App���� ȣ��)

private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;	// ��ǲ ��ġ SKD

private:
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;	// ��ǲ �İ�ü
	LPDIRECTINPUTDEVICE8	m_pMouse	= nullptr;	// ��ǲ �İ�ü

private:
	_byte					m_byKeyState[256];		// Ű���忡 �ִ� ��� Ű���� �����ϱ� ���� ����
	DIMOUSESTATE			m_tMouseState;	

	bool					m_bKeyState[VK_MAX];

public:
	virtual void			Free(void);

};
END
#endif // InputDev_h__
