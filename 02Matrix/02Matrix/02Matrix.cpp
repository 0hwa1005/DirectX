#include <iostream>

#include "Global.h"
#include "cMatrix.h"

int main()
{
	int nMatDimension;
	//���� �Է¹���
	cout << endl << "��� ������ �Է��Ͻÿ� : ";
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

	cout << "[ �ʱ� ��� ] " << endl;
	mat.Print();

	cout << "[ Determinant ] " << endl;
	cout << mat.Determinant() << endl;

	if (mat.Determinant() == 0)
	{
		cout << "������� �������� ����" << endl;
		return 0;
	}

	cout << "[ Adjoint ] " << endl;
	mat.Adjoint().Print();

	float fDet = 0.0f;
	cMatrix matInv = mat.Inverse(fDet);
	cout << "[ ����� ] " << endl;
	matInv.Print();

	cout << "[ ����� Ȯ�� ] " << endl;
	(matInv*mat).Print();


}
