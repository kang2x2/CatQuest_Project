#include "InputDev.h"

USING(Engine)
IMPLEMENT_SINGLETON(CInputDev)

Engine::CInputDev::CInputDev(void)
{

}

Engine::CInputDev::~CInputDev(void)
{
	Free();
}

_bool CInputDev::Key_Pressing(_int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

_bool CInputDev::Key_Down(_int _iKey)
{
	if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

_bool CInputDev::Key_Up(_int _iKey)
{
	if (m_bKeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeyState[_iKey] = !m_bKeyState[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
			m_bKeyState[i] = !m_bKeyState[i];
	}

	return false;
}

HRESULT Engine::CInputDev::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{

	// DInput �İ�ü�� �����ϴ� �Լ�
	FAILED_CHECK_RETURN(DirectInput8Create(hInst,
											DIRECTINPUT_VERSION,
											IID_IDirectInput8,
											(void**)&m_pInputSDK,
											NULL), E_FAIL);

	// Ű���� ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pMouse->Acquire();


	return S_OK;
}

void Engine::CInputDev::Update_InputDev(void)
{
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	m_pMouse->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState);
}

void Engine::CInputDev::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}

/*

	���� 

	_long	dwMouse = 0;

	if (dwMouse = Engine::Get_DIMouseMove(DIMS_Z))
	{
		int a = 0;
	}

*/