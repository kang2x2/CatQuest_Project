#include "stdafx.h"
#include "..\Header\Calculator.h"

#include "Management.h"
#include "TerrainTex.h"
#include "Transform.h"
#include "CameraMgr.h"

IMPLEMENT_SINGLETON(CCalculator)

CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

bool CCalculator::Mouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt, _vec3* pVPos, CGameObject* pTerrainVertex)
{
    // 월드까지 가져갈 마우스 좌표
    D3DXVECTOR3     vMousePos;

    // 뷰포트 정보 얻어오기
    D3DVIEWPORT9 viewPort = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();
    //pGraphicDev->GetViewport(&viewPort);

    // 마우스 좌표 투영 좌표로 변환.
    vMousePos.x = pt.x / (viewPort.Width * 0.5f) - 1.f;
    vMousePos.y = pt.y / -(viewPort.Height * 0.5f) + 1.f;
    vMousePos.z = 0.f;

    // 투영 -> 뷰 스페이스
    D3DXMATRIX matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
    //pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
    D3DXMatrixInverse(&matProj, 0, &matProj);
    D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

    // 광선 위치, 방향 벡터
    D3DXVECTOR3 vRayPos = { 0.f, 0.f, 0.f };
    D3DXVECTOR3 vRayDir = vMousePos - vRayPos;

    // 뷰 스페이스 -> 월드 스페이스
    D3DXMATRIX matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
    //pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
    D3DXMatrixInverse(&matView, 0, &matView);
    D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
    D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

    // 월드 스페이스 -> 로컬 스페이스
    _matrix pTerrainWorld = pTerrainVertex->Get_Transform()->Get_WorldMat();
    
    D3DXMatrixInverse(&pTerrainWorld, 0, &pTerrainWorld);
    D3DXVec3TransformCoord(&vRayPos, &vRayPos, &pTerrainWorld);
    D3DXVec3TransformNormal(&vRayDir, &vRayDir, &pTerrainWorld);

    const _vec3* pTerrainVtxPos = 
    dynamic_cast<CTerrainTex*>(pTerrainVertex->Get_VIBuffer())->Get_VtxPos();

    // NULL_CHECK_RETURN(pTerrainVtxPos, _vec3());

    _ulong		dwVtxIdx[3]{};

    _float	fU = 0.f, fV = 0.f, fDist = 0.f;

    for (_ulong i = 0; i < VTXCNTZ - 1; ++i)
    {
        for (_ulong j = 0; j < VTXCNTX - 1; ++j)
        {
            _ulong	dwIndex = i * VTXCNTX + j;

            // 오른쪽 위
            dwVtxIdx[0] = dwIndex + VTXCNTX;
            dwVtxIdx[1] = dwIndex + VTXCNTX + 1;
            dwVtxIdx[2] = dwIndex + 1;

            if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
                &pTerrainVtxPos[dwVtxIdx[0]],
                &pTerrainVtxPos[dwVtxIdx[2]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                // V1 + U(V2 - V1) + V(V3 - V1)
                *pVPos = pTerrainVtxPos[dwIndex];
                return true;
                //return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + fU * (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x),
                //    0.f,
                //    pTerrainVtxPos[dwVtxIdx[1]].z + fV * (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z));
            }

            // 왼쪽 아래
            dwVtxIdx[0] = dwIndex + VTXCNTX;
            dwVtxIdx[1] = dwIndex + 1;
            dwVtxIdx[2] = dwIndex;

            if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
                &pTerrainVtxPos[dwVtxIdx[0]],
                &pTerrainVtxPos[dwVtxIdx[2]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                // V1 + U(V2 - V1) + V(V3 - V1)
                *pVPos = pTerrainVtxPos[dwIndex];
                return true;
                //return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + fU * (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x),
                //    0.f,
                //    pTerrainVtxPos[dwVtxIdx[1]].z + fV * (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z));
            }
        }
    }
    return false;
}

_vec3& CCalculator::RealMouse_Picking(LPDIRECT3DDEVICE9 pGraphicDev, POINT pt, CGameObject* pTerrainVertex)
{
    // 월드까지 가져갈 마우스 좌표
    D3DXVECTOR3     vMousePos;

    // 뷰포트 정보 얻어오기
    D3DVIEWPORT9 viewPort = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_ViewPort();
    //pGraphicDev->GetViewport(&viewPort);

    // 마우스 좌표 투영 좌표로 변환.
    vMousePos.x = pt.x / (viewPort.Width * 0.5f) - 1.f;
    vMousePos.y = pt.y / -(viewPort.Height * 0.5f) + 1.f;
    vMousePos.z = 0.f;

    // 투영 -> 뷰 스페이스
    D3DXMATRIX matProj = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatProj();
    //pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
    D3DXMatrixInverse(&matProj, 0, &matProj);
    D3DXVec3TransformCoord(&vMousePos, &vMousePos, &matProj);

    // 광선 위치, 방향 벡터
    D3DXVECTOR3 vRayPos = { 0.f, 0.f, 0.f };
    D3DXVECTOR3 vRayDir = vMousePos - vRayPos;

    // 뷰 스페이스 -> 월드 스페이스
    D3DXMATRIX matView = CCameraMgr::GetInstance()->Get_CurCamera()->Get_CameraCom()->Get_MatView();
    //pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
    D3DXMatrixInverse(&matView, 0, &matView);
    D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
    D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

    // 월드 스페이스 -> 로컬 스페이스
    _matrix pTerrainWorld = pTerrainVertex->Get_Transform()->Get_WorldMat();

    D3DXMatrixInverse(&pTerrainWorld, 0, &pTerrainWorld);
    D3DXVec3TransformCoord(&vRayPos, &vRayPos, &pTerrainWorld);
    D3DXVec3TransformNormal(&vRayDir, &vRayDir, &pTerrainWorld);

    const _vec3* pTerrainVtxPos =
        dynamic_cast<CTerrainTex*>(pTerrainVertex->Get_VIBuffer())->Get_VtxPos();

    // NULL_CHECK_RETURN(pTerrainVtxPos, _vec3());

    _ulong		dwVtxIdx[3]{};

    _float	fU = 0.f, fV = 0.f, fDist = 0.f;

    for (_ulong i = 0; i < VTXCNTZ - 1; ++i)
    {
        for (_ulong j = 0; j < VTXCNTX - 1; ++j)
        {
            _ulong	dwIndex = i * VTXCNTX + j;

            // 오른쪽 위
            dwVtxIdx[0] = dwIndex + VTXCNTX;
            dwVtxIdx[1] = dwIndex + VTXCNTX + 1;
            dwVtxIdx[2] = dwIndex + 1;

            if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
                &pTerrainVtxPos[dwVtxIdx[0]],
                &pTerrainVtxPos[dwVtxIdx[2]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + fU * (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x),
                    0.f,
                    pTerrainVtxPos[dwVtxIdx[1]].z + fV * (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z));
            }

            // 왼쪽 아래
            dwVtxIdx[0] = dwIndex + VTXCNTX;
            dwVtxIdx[1] = dwIndex + 1;
            dwVtxIdx[2] = dwIndex;

            if (D3DXIntersectTri(&pTerrainVtxPos[dwVtxIdx[1]],
                &pTerrainVtxPos[dwVtxIdx[0]],
                &pTerrainVtxPos[dwVtxIdx[2]],
                &vRayPos, &vRayDir, &fU, &fV, &fDist))
            {
                // V1 + U(V2 - V1) + V(V3 - V1)
                return _vec3(pTerrainVtxPos[dwVtxIdx[1]].x + fU * (pTerrainVtxPos[dwVtxIdx[0]].x - pTerrainVtxPos[dwVtxIdx[1]].x),
                    0.f,
                    pTerrainVtxPos[dwVtxIdx[1]].z + fV * (pTerrainVtxPos[dwVtxIdx[2]].z - pTerrainVtxPos[dwVtxIdx[1]].z));
            }
        }
    }

    return _vec3{ vec3.zero };
}

void CCalculator::Free()
{
}