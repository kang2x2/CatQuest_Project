#include "..\..\Header\CollisionMgr.h"

#include "Management.h"
#include "Layer.h"

#include "GameObject.h"
#include "LineObject.h"

#include "Collider.h"
#include "LineCollider.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "SphereCollider.h"

#include "Transform.h"

#include <iostream>

IMPLEMENT_SINGLETON(CCollisionMgr)

typedef		multimap<const _tchar*, CGameObject*>	_mapObj;
typedef		_mapObj::iterator					_iter;

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
	Free();
}

void CCollisionMgr::Check_Collision(const OBJ_TYPE& _eType1, const OBJ_TYPE& _eType2, const OBJ_TYPE& _eParentType, const COL_TYPE& _eColType1, const COL_TYPE& _eColType2)
{	
	CGameObject*	pObj1	=	nullptr;	 
	CGameObject*	pObj2	=	nullptr;
	CCollider*		pCol1	=	nullptr;
	CCollider*		pCol2	=	nullptr;

	map<_ulonglong, _bool>::iterator	iter;

	_mapObj& mapObj1 = CManagement::GetInstance()->Get_Layer(_eType1)->Get_ObjectMap();
	_mapObj& mapObj2 = CManagement::GetInstance()->Get_Layer(_eType2)->Get_ObjectMap();

	if (mapObj1.empty() || mapObj2.empty()) return;

	for (_iter iter1 = mapObj1.begin(); iter1 != mapObj1.end(); ++iter1)
	{
		for (_iter iter2 = mapObj2.begin(); iter2 != mapObj2.end(); ++iter2)
		{ 
			pObj1 = iter1->second;	pObj2 = iter2->second;

			if (pObj1 == pObj2 || nullptr == pObj1 || nullptr == pObj2) continue;

			if (COL_TYPE::RECT == _eColType1 && COL_TYPE::RECT == _eColType2) // 렉트 vs 렉트
			{
				pCol1 = pObj1->Get_Collider();
				pCol2 = pObj2->Get_Collider();

				if (nullptr == pCol1 || nullptr == pCol2 || !pCol1->Is_Active() || !pCol1->Is_Active()) continue;

				Set_Info(iter, pCol1, pCol2);

				if (Check_Rect(pObj1, pObj2)) // 충돌
				{
					if (iter->second) // 이전에도 충돌
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // 둘 중 하나 삭제 예정
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // 삭제 예정 없음
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // 이번에 충돌
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // 충돌 X
				{
					if (iter->second) // 이전에 충돌
					{
						pCol1->OnCollision_Exit(pObj2);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
				}
			}
			else if (COL_TYPE::RECT == _eColType1 && COL_TYPE::SPHERE == _eColType2) // 객체 포지션 vs 스피어
			{
				if (_eParentType != pObj2->Get_Parent()->Get_Type()) continue; 
				
				pCol1 = pObj1->Get_Collider(); // 렉트 콜라이더를 빌려 쓴다 (포지션정보만 필요하니까)
				pCol2 = pObj2->Get_Collider();

				if (nullptr == pCol1 || nullptr == pCol2) continue;
				Set_Info(iter, pCol1, pCol2);

				if (Check_Range(pObj1, pObj2)) // 충돌
				{
					if (iter->second) // 이전에도 충돌
					{
						if (!pObj1->Is_Active() || !pObj2->Is_Active()) // 둘 중 하나 삭제 예정
						{
							pCol1->OnCollision_Exit(pObj2);
							pCol2->OnCollision_Exit(pObj1);
							iter->second = false;
						}
						else // 삭제 예정 없음
						{
							pCol1->OnCollision_Stay(pObj2);
							pCol2->OnCollision_Stay(pObj1);
						}
					}
					else // 이번에 충돌
					{
						if (pObj1->Is_Active() && pObj2->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
						{
							pCol1->OnCollision_Enter(pObj2);
							pCol2->OnCollision_Enter(pObj1);
							iter->second = true;
						}
					}
				}
				else // 충돌 X
				{
					if (iter->second) // 이전에 충돌
					{
						pCol1->OnCollision_Exit(pObj2);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;
					}
				}
			}
		}
	}
}

void CCollisionMgr::Check_Line_Collision(const OBJ_TYPE& _eType)
{
	CGameObject* pObj1 = nullptr;

	CCollider* pCol1 = nullptr;
	CCollider* pCol2 = nullptr;

	map<_ulonglong, _bool>::iterator iter;

	_mapObj& mapObj1 = CManagement::GetInstance()->Get_Layer(_eType)->Get_ObjectMap();

	if (mapObj1.empty()) return;

	for (_iter iter1 = mapObj1.begin(); iter1 != mapObj1.end(); ++iter1)
	{
		for (auto& pLine : m_vecLine)
		{
			pObj1 = iter1->second;

			if (nullptr == pObj1 || nullptr == pLine ) continue;

			pCol1 = static_cast<CCollider*>(pObj1->Get_Component(COMPONENT_TYPE::COL_RECT, ID_STATIC));
			pCol2 = static_cast<CCollider*>(pLine->Get_Component(COMPONENT_TYPE::COL_LINE, ID_STATIC));

			if (nullptr == pCol1 || nullptr == pCol2) continue;

			Set_Info(iter, pCol1, pCol2);

			if (Check_Line_Rect(pObj1, pLine)) // 충돌
			{
				if (iter->second) // 이전에도 충돌
				{
					if (!pObj1->Is_Active() || !pLine->Is_Active()) // 둘 중 하나 삭제 예정
					{
						pCol1->OnCollision_Exit(pLine);
						pCol2->OnCollision_Exit(pObj1);
						iter->second = false;

						//cout << "Exit\n";
					}
					else // 삭제 예정 없음
					{
						pCol1->OnCollision_Stay(pLine);
						pCol2->OnCollision_Stay(pObj1);

						//cout << "Stay\n";
					}
				}
				else // 이번에 충돌
				{
					if (pObj1->Is_Active() && pLine->Is_Active()) // 둘다 삭제될 예정이 아닐 때만 충돌 처리
					{
						pCol1->OnCollision_Enter(pLine);
						pCol2->OnCollision_Enter(pObj1);
						iter->second = true;

						//cout << "Enter\n";
					}
				}
			}
			else // 충돌 X
			{
				if (iter->second) // 이전에 충돌
				{
					pCol1->OnCollision_Exit(pLine);
					pCol2->OnCollision_Exit(pObj1);
					iter->second = false;

					//cout << "Exit\n";

				}
			}

		}
	}
}

const _bool CCollisionMgr::Check_Rect(CGameObject* const _pObj1, CGameObject* const _pObj2)
{
	// 밀어내기는 밀어낼 값을 콜라이더나 라인에 저장하고, 밀어내기에 대한 구현은 각 오브젝트의 OnCollision에서 구현하도록 한다.

	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Collider());
	CRectCollider* pCol2 = static_cast<CRectCollider*>(_pObj2->Get_Collider());

	CTransform* pTrans1 = _pObj1->Get_Transform();
	CTransform* pTrans2 = _pObj2->Get_Transform();
	
	_float fX = fabs(pTrans1->Get_Info(INFO_POS).x - pTrans2->Get_Info(INFO_POS).x);
	_float fY = fabs(pTrans1->Get_Info(INFO_POS).y - pTrans2->Get_Info(INFO_POS).y); // Y 추가
	_float fZ = fabs(pTrans1->Get_Info(INFO_POS).z - pTrans2->Get_Info(INFO_POS).z);

	// 애니메이션에서 스케일을 -로 사용하는 경우에 대한 예외처리
	_float fRadiusX = (fabs(pTrans1->Get_Scale().x) + fabs(pTrans2->Get_Scale().x)) * 0.5f;
	_float fRadiusY = (fabs(pTrans1->Get_Scale().y) + fabs(pTrans2->Get_Scale().y)) * 0.5f; // Y 추가
	_float fRadiusZ = (fabs(pTrans1->Get_Scale().z) + fabs(pTrans2->Get_Scale().z)) * 0.5f;

	// Z 포지션 예외처리
	//if (pTrans1->Get_Info(INFO_POS).z < pTrans2->Get_Info(INFO_POS).z)
	//	fRadiusZ += fabs(pTrans2->Get_Scale().z);

	if ((fRadiusX >= fX) && (fRadiusZ >= fZ) && (fRadiusY >= fY))  // Y 추가
	{
		_float fOverX = fRadiusX - fX;
		_float fOverZ = fRadiusZ - fZ;

		pCol1->Set_OverLap_Rect(_vec3{ fOverX, 0.f, fOverZ });
		pCol2->Set_OverLap_Rect(_vec3{ fOverX, 0.f, fOverZ });

		return TRUE;
	}

	return FALSE;
}

const _bool CCollisionMgr::Check_Rect_Circle(CGameObject* const _pObj1, CGameObject* const _pObj2)
{

	return TRUE;
}

const _bool CCollisionMgr::Check_Line_Rect(CGameObject* const _pObj1, CLineObject* const _pObj2)
{
	CRectCollider* pCol1 = static_cast<CRectCollider*>(_pObj1->Get_Component(COMPONENT_TYPE::COL_RECT, ID_STATIC));
	CLineCollider* pCol2 = static_cast<CLineCollider*>(_pObj2->Get_Component(COMPONENT_TYPE::COL_LINE, ID_STATIC));

	_vec3 vPos = _pObj1->Get_Transform()->Get_Info(INFO_POS);
	_vec3 vScale = _pObj1->Get_Transform()->Get_Scale();

	if (0 > vScale.x) vScale.x *= -1.f;
	if (0 > vScale.z) vScale.z *= -1.f;

	_vec3 vRectPtList[4] =
	{
		_vec3{vPos.x - (vScale.x * 0.5f), 0.f, vPos.z + (vScale.z * 0.5f)},
		_vec3{vPos.x + (vScale.x * 0.5f), 0.f, vPos.z + (vScale.z * 0.5f)},
		_vec3{vPos.x + (vScale.x * 0.5f), 0.f, vPos.z - (vScale.z * 0.5f)},
		_vec3{vPos.x - (vScale.x * 0.5f), 0.f, vPos.z - (vScale.z * 0.5f)}
	};
	_vec3 vLinePtList[2] =
	{
		_vec3{ pCol2->m_vPointList[0].x, 0.f, pCol2->m_vPointList[0].z - vScale.z }, // z예외처리
		_vec3{ pCol2->m_vPointList[1].x, 0.f, pCol2->m_vPointList[1].z - vScale.z },
	};

	for (int i = 0; i < 3; ++i)
	{
		if ((Check_CCW(vRectPtList[i], vRectPtList[i + 1], vLinePtList[0])
			!= Check_CCW(vRectPtList[i], vRectPtList[i + 1], vLinePtList[1]))
			&&
			(Check_CCW(vLinePtList[0], vLinePtList[1], vRectPtList[i])
			!= Check_CCW(vLinePtList[0], vLinePtList[1], vRectPtList[i + 1])))
		{
			//if(지나갈 수 없는 라인이라면)

			pCol2->m_vOverlapLine = Get_LineCollision_Data(_pObj1->Get_Transform()->Get_Dir(), vRectPtList, vLinePtList);

			return TRUE;
		}
	}

	return FALSE;
}

const _int CCollisionMgr::Check_CCW(const _vec3& _vLineStart, const _vec3& _vLineEnd, const _vec3& _vPT)
{
	long long t1 = long long(_vLineStart.x * _vLineEnd.z + _vLineEnd.x * _vPT.z + _vPT.x * _vLineStart.z);
	long long t2 = long long(_vLineStart.z * _vLineEnd.x + _vLineEnd.z * _vPT.x + _vPT.z * _vLineStart.x);

	long long tres = t1 - t2;

	if (tres > 0)
		return 1;
	else if (tres == 0)
		return 0;
	else
		return -1;

	return 0;
}

const _vec3& CCollisionMgr::Get_LineCollision_Data(const _vec3& vDir, _vec3* _vRectPtList, _vec3* _vLinePtList)
{
	// 충돌 영역만큼 빼주기 위한 데이터 제공 -> 라인 콜라이더에 저장
	_vec3 vCross, v1, v2;
	_bool bPrevY[4]; // 외적된 y 값이 음수인지 양수인지
	_vec3 vOutPoint; // 렉트 4점 중 나간 점
	_vec3 vOverlap;  // 빼줘야할 영역
	ZeroMemory(&vOverlap, sizeof(_vec3));

	// 1. 외적으로 4점 중 어느 점이 라인밖으로 나갔는지 찾는다
	for (int i = 0; i < 4; ++i)
	{
		v1 = _vRectPtList[i] - _vLinePtList[0];
		v2 = _vLinePtList[1] - _vLinePtList[0];

		D3DXVec3Cross(&vCross, &v1, &v2);
		if (0 < vCross.y)
			bPrevY[i] = true;
		else
			bPrevY[i] = false;
	}

	if ((bPrevY[0] == bPrevY[1]) && (bPrevY[0] == bPrevY[2]) && (bPrevY[0] == bPrevY[3]))
		return vec3.zero;



	_bool bPrev; // 여기 조건을 다시 짜야할 듯
	for (int i = 0; i < 4; ++i)
	{
		if (0 == i)
		{
			bPrev = bPrevY[i]; 
			continue;
		}

		if (bPrev != bPrevY[i])
		{
			if (1 == i && bPrevY[0] == bPrevY[2])
			{
				vOutPoint = _vRectPtList[i];
				break;
			}
			else if (1 == i && bPrevY[0] != bPrevY[2])
			{
				vOutPoint = _vRectPtList[0];

				break;
			}
			vOutPoint = _vRectPtList[i];
			break;
		}
	}



	// 0 1 
	// 3 2

	if (0 == bPrevY[0] && 1 == bPrevY[1] && 1 == bPrevY[2] && 0 == bPrevY[3]) // 좌우 충돌 0 1 1 0
	{
		if (0 < vDir.x) // ->
			vOutPoint = _vRectPtList[1];
		else // <-
			vOutPoint = _vRectPtList[0];

		// 2. 직선의 방정식으로 라인에서 위치할 x, z 값을 구한다.

		_float fX = (vOutPoint.z - _vLinePtList[0].z)
			/ ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x))
			+ _vLinePtList[0].x;

		// 3. 밀어낸 최종 위치 
		vOverlap.x = fX - vOutPoint.x;
		vOverlap.z = 0.f;

		return vOverlap;
	}
	else if (1 == bPrevY[0] && 1 == bPrevY[1] && 0 == bPrevY[2] && 0 == bPrevY[3]) // 상하 충돌 1 1 0 0
	{
		if (0 < vDir.z) // 위로
			vOutPoint = _vRectPtList[0];
		else // 아래로
			vOutPoint = _vRectPtList[2];


		// 2. 직선의 방정식으로 라인에서 위치할 x, z 값을 구한다.
		_float fZ = ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x))
			* (vOutPoint.x - _vLinePtList[0].x)
			+ _vLinePtList[0].z;

		vOverlap.x = 0.f;
		vOverlap.z = fZ - vOutPoint.z;

		return vOverlap;
	}
	else
	{
		// 2. 직선의 방정식으로 라인에서 위치할 x, z 값을 구한다.
		_float fZ = ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x)) 
						* (vOutPoint.x - _vLinePtList[0].x) 
						+ _vLinePtList[0].z;

		_float fX = (vOutPoint.z - _vLinePtList[0].z) 
						/ ((_vLinePtList[1].z - _vLinePtList[0].z) / (_vLinePtList[1].x - _vLinePtList[0].x))	
						+ _vLinePtList[0].x;

		// 3. 밀어낸 최종 위치 
		vOverlap.x = fX - vOutPoint.x;
		vOverlap.z = fZ - vOutPoint.z;

		return vOverlap;
	}
}

const _bool CCollisionMgr::Check_Range(CGameObject* const _pObj, CGameObject* const _pRange)
{
	_vec3 vObjPos = _pObj->Get_Transform()->Get_Info(INFO_POS);
	vObjPos.y = 0.f;

	CSphereCollider* pCol = dynamic_cast<CSphereCollider*>(_pRange->Get_Collider());

	NULL_CHECK_RETURN(pCol, FALSE);

	_float fRadius = pCol->Get_Radius();

	_float fDis = D3DXVec3Length(&(vObjPos - _pRange->Get_Transform()->Get_Info(INFO_POS)));

	if (fDis < fRadius)
		return TRUE;
	else
		return FALSE;
}

void CCollisionMgr::Set_Info(map<_ulonglong, _bool>::iterator & _iter, CCollider * _pCol1, CCollider * _pCol2)
{
	COLLIDER_ID ID;

	ID.iLeft_id = _pCol1->Get_ID();
	ID.iRight_id = _pCol2->Get_ID();

	// 이전에 충돌 검사 여부 조사
	_iter = m_mapColInfo.find(ID.ID);

	// 없다면 새로 추가
	if (m_mapColInfo.end() == _iter)
	{
		m_mapColInfo.insert({ ID.ID, false });
		_iter = m_mapColInfo.find(ID.ID);
	}
}

void CCollisionMgr::Free()
{
}
