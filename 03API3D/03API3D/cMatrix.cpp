#include "framework.h"
#include "cVector3.h"
#include "cMatrix.h"

cMatrix::cMatrix()
{
}

cMatrix::~cMatrix()
{
}

cMatrix::cRow::cRow()
{
}

//=====================================================================

cMatrix::cRow::cRow(int nDimension)
{
	Resize(nDimension);
}

cMatrix::cRow::~cRow()
{
}

void cMatrix::cRow::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}

float & cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

//=================================================================================

cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); ++ i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for (size_t i = 0; i < nDimension; ++i)
		m_vecData[i].Resize(nDimension);}

int cMatrix::Dimension()
{
	return (int)m_vecData.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);

	for (int i = 0; i < nDimension; ++i)
	{
		for (int j = 0; j < nDimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

bool cMatrix::operator==(cMatrix & mat)
{
	float fEpsilon = 0.0001f;
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if ((*this)[i][j] - fEpsilon > mat[i][j])
				return false;
			if ((*this)[i][j] + fEpsilon < mat[i][j])
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	return !((*this) == mat);
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0.0f;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += (*this)[i][k] * mat[k][j];
			}
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] *f;
		}
	}
	return matRet;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminant)
{
	cMatrix matRet = cMatrix::Identity(Dimension());

	fDeterminant = Determinant();
	if (-0.001f < fDeterminant&& fDeterminant < 0.001f)
	{
		//cout << "역행렬이 존재하지 않음" << endl;
		return matRet;
	}
	cMatrix matAdj = Adjoint();
	matRet = matAdj * (1 / fDeterminant);
	return matRet;
}

float cMatrix::Determinant()
{
	if (Dimension() == 1)
	{
		return (*this)[0][0];
	}

	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}

	float fDeterminent = 0.0f;
	for (int i = 0; i < Dimension(); ++i)
	{
		fDeterminent += ((*this)[i][0] * Cofactor(i, 0));
	}
	return fDeterminent;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}
	return matRet;
}

cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}
	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if ((nRow + nCol) % 2 != 0)
		nConst = -1;
	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension()-1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (nRow == i)
			continue;

		nMinorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}
	return matMinor.Determinant();
}

cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;
	return matRet;
}

cMatrix cMatrix::Translation(cVector3 & v)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[3][0] = v.x;
	matRet[3][1] = v.y;
	matRet[3][2] = v.z;
	return matRet;
}

cMatrix cMatrix::RotationX(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[1][1] = cosf(fAngle);
	matRet[1][2] = sinf(fAngle);
	matRet[2][1] = -sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationY(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][2] = -sinf(fAngle);
	matRet[2][0] = sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationZ(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][1] = sinf(fAngle);
	matRet[1][0] = -sinf(fAngle);
	matRet[1][1] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)	//뷰 스페이스
{
	cVector3 l = (vLookAt - vEye).Normalize();			//보고 있는 방향
	cVector3 r = cVector3::Cross(vUp,l).Normalize();	//오른쪽 방향 벡터 구함
	cVector3 u = cVector3::Cross(l, r).Normalize();		//윗방향 벡터 다시 계산

	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = r.x; matRet[0][1] = u.x; matRet[0][2] = l.x;
	matRet[1][0] = r.y; matRet[1][1] = u.y; matRet[1][2] = l.y;
	matRet[2][0] = r.z; matRet[2][1] = u.z; matRet[2][2] = l.z;

	matRet[3][0] = -cVector3::Dot(r, vEye);
	matRet[3][1] = -cVector3::Dot(u, vEye);
	matRet[3][2] = -cVector3::Dot(l, vEye);

	return matRet;
}

cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)	//투영
{
	cMatrix matRet = cMatrix::Identity(4);
	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;

	matRet[0][0] = fScaleX;
	matRet[1][1] = fScaleY;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = fFarZ * fNearZ / (fFarZ - fNearZ);
	matRet[3][3] = 0.0f;
	return matRet;
}

cMatrix cMatrix::Viewport(float x, float y, float w, float h, float minz, float maxz)	//뷰포트 변환
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = w / 2.0f;
	matRet[1][1] = -h / 2.0f;
	matRet[2][2] = maxz - minz;
	matRet[3][0] = x + w / 2.0f;
	matRet[3][1] = y + h / 2.0f;
	matRet[3][2] = minz;

	return matRet;
}

cMatrix cMatrix::Scale(float scale)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = matRet[0][0] * scale;
	matRet[1][1] = matRet[1][1] * scale;
	matRet[2][2] = matRet[2][2] * scale;

	return matRet;
}


//Matrix ----> S(Scaling) R(Rotation) T(Transform) => World Matrix   행렬 조합 순서 중요함 *엔진에 따라 바꿔주는 경우 있음	( T R S ) 
//
//	Wrold * View * Projection * Viewport
