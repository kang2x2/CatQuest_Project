#define _CRT_SECURE_NO_WARNINGS
#include "..\..\Header\Texture.h"

#include "GameObject.h"

#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
#include <string.h>

#include <mbstring.h>

#include "Management.h"

CTexture::CTexture()
{
}

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev, COMPONENT_TYPE::TEXTURE)
{
}

CTexture::CTexture(const CTexture & rhs, CGameObject* _pOwnerObject)
	: CComponent(rhs, _pOwnerObject)
{
	_uint		iContainer = rhs.m_vecTexture.size();
	m_vecTexture.reserve(iContainer);

	m_vecTexture = rhs.m_vecTexture;
	m_vecPathForImGui = rhs.m_vecPathForImGui; // ���� �߰�
	m_iTexCnt = rhs.m_iTexCnt;

	for (_uint i = 0; i < iContainer; ++i) 
		m_vecTexture[i]->AddRef(); // 1�ؽ�ó�� 1�İ�ü�̴�. ���� ���۷��� ī��Ʈ�� �÷��ش�.
}


CTexture::~CTexture()
{
}

HRESULT CTexture::Ready_Texture(TEXTUREID eType, const _tchar * pPath, const _uint & iCnt)
{
	m_vecTexture.reserve(iCnt); 
	m_iTexCnt = iCnt;

	IDirect3DBaseTexture9*		pTexture = nullptr;

	for (_uint i = 0; i < iCnt; ++i)
	{
		TCHAR		szFileName[128] = L"";

		wsprintf(szFileName, pPath, i);

		// �ؽ�ó Ÿ���� �Ϲ� �ؽ�ó���� ť�� �ؽ�ó������ ���� ����ϴ� �Լ��� �ٸ���.
		switch (eType)
		{
		case TEX_NORMAL:
			FAILED_CHECK_RETURN(D3DXCreateTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DTEXTURE9*)&pTexture), E_FAIL);
			break;

		case TEX_CUBE:
			FAILED_CHECK_RETURN(D3DXCreateCubeTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DCUBETEXTURE9*)&pTexture), E_FAIL);
			break;
		}
		
		// << : IMGUI
		wstring wstrPath(pPath);
		string strPath(wstrPath.begin(), wstrPath.end());
		string strFind = "%";
		
		if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())
		{
			if (strPath.find(strFind) != string::npos) // �ش� ���ڿ� ����
			{
				/*int find = strPath.rfind("/") + 1;
				string filePath = strPath.substr(0, find);
				filePath += "0.png";
			
				wstrPath.assign(filePath.begin(), filePath.end());*/

				TCHAR*		szNewFileName = new TCHAR[sizeof(TCHAR) * 128];

				wcscpy(szNewFileName, szFileName);

				if(m_vecPathForImGui.empty())
					m_vecPathForImGui.push_back(szNewFileName); // �̰� �츮��
				int k = 0;
			}
			else
			{
				if (m_vecPathForImGui.empty())
					m_vecPathForImGui.push_back(pPath); // �̰� �츮��
				int k = 0;
			}
		}
		m_vecTexture.push_back(pTexture);
		//m_vecPathForImGui.push_back(pPath); // �̰� �����

	}

	
	return S_OK;
}

void CTexture::Render_Texture(const _uint & iIndex)
{
	if (m_vecTexture.size() < iIndex)
		return;

	m_pGraphicDev->SetTexture(0, m_vecTexture[iIndex]); 
	
	// ����̽��� �ؽ�ó ������ ���� ���õ� ��, ���۰� ��µǾ�� �Ѵ�
	// (���� ������Ʈ Render_Object()�Լ� ������ �Ʒ� ����)
	//		1. m_pTextureCom->Render_Texture(0); 
	//		2. m_pBufferCom->Render_Buffer();
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTUREID eType, _tchar * pPath, const _uint & iCnt)
{
	CTexture*			pInstance = new CTexture(pGraphicDev);

	if (FAILED(pInstance->Ready_Texture(eType, pPath, iCnt)))
	{
		MSG_BOX("Texture Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CTexture::Clone(CGameObject* _pOwnerObject)
{
	return new CTexture(*this, _pOwnerObject);
}

void CTexture::Free()
{
	if (PLAY_MODE::TOOL == CManagement::GetInstance()->Get_PlayMode())
	{
		for (auto& iter : m_vecPathForImGui)
		{
			//delete [] iter;
		}
	}
	for_each(m_vecTexture.begin(), m_vecTexture.end(), CDeleteObj());
	m_vecTexture.clear();

	CComponent::Free();
}
