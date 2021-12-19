#include <iostream>

#include "Global.h"
#include "cMatrix.h"

int main()
{
	int nMatDimension;
	//차수 입력받음
	cout << endl << "행렬 차수를 입력하시오 : ";
	cin >> nMatDimension;

	cMatrix mat(nMatDimension);
	mat = cMatrix::Identity(nMatDimension);

	for (int row = 0; row < nMatDimension; row++)
	{
		for (int col = 0; col < nMatDimension; col++)
		{
			printf("[ %d, %d ] : ", row + 1, col + 1);
			cin >> mat[row][col];
		}
	}

	cout << "[ 초기 행렬 ] " << endl;
	mat.Print();

	cout << "[ Determinant ] " << endl;
	cout << mat.Determinant() << endl;

	if (mat.Determinant() == 0)
	{
		cout << "역행렬이 존재하지 않음" << endl;
		return 0;
	}

	cout << "[ Adjoint ] " << endl;
	mat.Adjoint().Print();

	float fDet = 0.0f;
	cMatrix matInv = mat.Inverse(fDet);
	cout << "[ 역행렬 ] " << endl;
	matInv.Print();

	cout << "[ 역행렬 확인 ] " << endl;
	(matInv*mat).Print();


}
