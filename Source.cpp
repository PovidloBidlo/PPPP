#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание новой матрицы/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

int** NewMatrix(int countCol, int countRows) {
	int** matrix = new int* [countCol];
	for (int i = 0; i < countCol; i++) {
		matrix[i] = new int[countRows];
	}
	return matrix;
}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Ввод размера матрицы //////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

// MatrixN - порядковый номер матрицы,
void GetMatrixRazm(int MatrixN, int* countCol, int* countRows) {

	int N = 0, M = 0;
	while (N <= 0 || M <= 0) {
		cout << "Введите размеры " << MatrixN << " первой матрицы" << endl;
		cin >> N >> M;
	}
	*countCol = N;
	*countRows = M;
}


	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения матрицы //////////////////////////////
	///////////////////////////////////////////////////////////////////////////////


int GetChoiceUser() {
	int choice = 0;

	while (choice < 1 || choice > 2) {
		cout << "Выберите способ заполнения матрицы\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> choice;
	}
	return choice;
}


// вывод матрицы
void OutMatrix(int MatrixN, int** matrix, int countCol, int countRows) {
	cout << "\nМатрица " << MatrixN << endl;
	for (int i = 0; i < countCol; i++) {
		for (int j = 0; j < countRows; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}


	///////////////////////////////////////////////////////////////////////////////
	/////////////Заполнение матрицы с учетом выбора способа заполнения ////////////
	///////////////////////////////////////////////////////////////////////////////

// UserChoice - выбор пользователя, полученное в результате выполнения функции GetChoiceUser

int** FullMatrix(int MatrixN, int UserChoice, int** matrix, int countCol, int countRows) {
	switch (UserChoice)
	{
	case 1:
		for (int i = 0; i < countCol; i++)
			for (int j = 0; j < countRows; j++)
				cin >> matrix[i][j];
		break;
	case 2:
		for (int i = 0; i < countCol; i++)
			for (int j = 0; j < countRows; j++)
				matrix[i][j] = rand() % 10;
	}

	return matrix;
}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Приведение матрицы к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

int** DecreaseMatrix(int length, int** matrix, int countCol, int countRows) {
	int** RasMatrix = new int* [length];
	for (int i = 0; i < length; i++)
	{
		RasMatrix[i] = new int[length];
		for (int j = 0; j < length; j++)
			RasMatrix[i][j] = 0;
	}

	for (int i = 0; i < countCol; i++)
		for (int j = 0; j < countRows; j++)
			RasMatrix[i][j] = matrix[i][j];
	return RasMatrix;

}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Разбиение матриц на подматрицы и их заполнение/////////////////
	///////////////////////////////////////////////////////////////////////////////

int*** CreateAndFullSubMatrix(int length, int** RasMatrix) {
	//int** mat1 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat1[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat1[i][j] = RasMatrix[i][j];
	//}
	//int** mat2 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat2[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat2[i][j] = RasMatrix[i][j + length / 2];
	//}
	//int** mat3 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat3[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat3[i][j] = RasMatrix[i + length / 2][j];
	//}
	//int** mat4 = new int* [length / 2];
	//for (int i = 0; i < length / 2; i++)
	//{
	//	mat4[i] = new int[length / 2];
	//	for (int j = 0; j < length / 2; j++)
	//		mat4[i][j] = RasMatrix[i + length / 2][j + length / 2];
	//}

	int*** SubMatrix = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		SubMatrix[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			SubMatrix[i][j] = new int[length / 2];
	}

	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++) {
			SubMatrix[0][i][j] = RasMatrix[i][j];
			SubMatrix[1][i][j] = RasMatrix[i][j + length / 2];
			SubMatrix[2][i][j] = RasMatrix[i + length / 2][j];
			SubMatrix[3][i][j] = RasMatrix[i + length / 2][j + length / 2];
		}
	return SubMatrix;
}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Создание массива промежуточных матриц /////////////////////////
	///////////////////////////////////////////////////////////////////////////////

int*** CreatePromejMatrixs(int length) {
	int*** p = new int** [7];
	for (int i = 0; i < 7; i++)
	{
		p[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			p[i][j] = new int[length / 2];
	}
	return p;
}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Вычисление значений промежуточных матриц //////////////////////
	///////////////////////////////////////////////////////////////////////////////

int*** CalculatePromejMatrix(int length, int*** p, int*** SubMatrixFirst, int*** SubMatrixSecond) {
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < length / 2; j++)
			for (int k = 0; k < length / 2; k++)
				p[i][j][k] = 0;

	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
			for (int z = 0; z < length / 2; z++) {
				p[0][i][j] += (SubMatrixFirst[0][i][z] + SubMatrixFirst[3][i][z]) * (SubMatrixSecond[0][z][j] + SubMatrixSecond[3][z][j]);
				p[1][i][j] += (SubMatrixFirst[2][i][z] + SubMatrixFirst[3][i][z]) * SubMatrixSecond[0][z][j];
				p[2][i][j] += SubMatrixFirst[0][i][z] * (SubMatrixSecond[1][z][j] - SubMatrixSecond[3][z][j]);
				p[3][i][j] += SubMatrixFirst[3][i][z] * (SubMatrixSecond[2][z][j] - SubMatrixSecond[0][z][j]);
				p[4][i][j] += (SubMatrixFirst[0][i][z] + SubMatrixFirst[1][i][z]) * SubMatrixSecond[3][z][j];
				p[5][i][j] += (SubMatrixFirst[2][i][z] - SubMatrixFirst[0][i][z]) * (SubMatrixSecond[0][z][j] + SubMatrixSecond[1][z][j]);
				p[6][i][j] += (SubMatrixFirst[1][i][z] - SubMatrixFirst[3][i][z]) * (SubMatrixSecond[2][z][j] + SubMatrixSecond[3][z][j]);
			}
	return p;
}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Создание вспомогательных матриц ///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

int*** SupportMatrixes(int length, int*** p) {
	int*** SupportMatrix = new int** [4];
	for (int i = 0; i < 4; i++)
	{
		SupportMatrix[i] = new int* [length / 2];
		for (int j = 0; j < length / 2; j++)
			SupportMatrix[i][j] = new int[length / 2];
	}


	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
		{
			SupportMatrix[0][i][j] = p[0][i][j] + p[3][i][j] - p[4][i][j] + p[6][i][j];
			SupportMatrix[1][i][j] = p[2][i][j] + p[4][i][j];
			SupportMatrix[2][i][j] = p[1][i][j] + p[3][i][j];
			SupportMatrix[3][i][j] = p[0][i][j] - p[1][i][j] + p[2][i][j] + p[5][i][j];
		}
	return SupportMatrix;
}
	///////////////////////////////////////////////////////////////////////////////
	////////////////Создание результирующей матрицы ///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
int** CreateResultingMatrix(int length, int*** SupportMatrix) {
	int** resultingMatrix = new int* [length];
	for (int i = 0; i < length; i++)
		resultingMatrix[i] = new int[length];


	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < length / 2; i++)
		for (int j = 0; j < length / 2; j++)
		{
			resultingMatrix[i][j] = SupportMatrix[0][i][j];
			resultingMatrix[i][j + length / 2] = SupportMatrix[1][i][j];
			resultingMatrix[i + length / 2][j] = SupportMatrix[2][i][j];
			resultingMatrix[i + length / 2][j + length / 2] = SupportMatrix[3][i][j];
		}


	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < length; i++)
	{
		x = 0;
		for (int j = 0; j < length; j++)
			if (resultingMatrix[i][j] != 0)
			{
				x++;
				f = 100;
			}

		if (x == 0 && i < f)
			f = i;
	}

	for (int i = 0; i < length; i++)
	{
		x = 0;
		for (int j = 0; j < length; j++)
			if (resultingMatrix[j][i] != 0)
			{
				x++;
				s = 100;
			}

		if (x == 0 && i < s)
			s = i;
	}

	int** resultMatrix = new int* [f];
	for (int i = 0; i < f; i++)
	{
		resultMatrix[i] = new int[s];
		for (int j = 0; j < s; j++)
			resultMatrix[i][j] = resultingMatrix[i][j];
	}
	cout << "\nРезультирующая матрица\n\n";
	OutMatrix(0, resultMatrix, f, s);

	for (int i = 0; i < length; i++)
	{
		delete[] resultingMatrix[i];
	}
	return resultMatrix;

	for (int i = 0; i < f; i++)
		delete[] resultMatrix[i];
}





int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int countCol_firstMatrix, countRows_firstMatrix;
	int countCol_secondMatrix, countRows_secondMatrix;
	int k, length = 2;

	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	GetMatrixRazm(1, &countCol_firstMatrix, &countRows_firstMatrix);
	GetMatrixRazm(2, &countCol_secondMatrix, &countRows_secondMatrix);
	int** matrixFirst = NewMatrix(countCol_firstMatrix, countRows_firstMatrix);
	int** matrixSecond = NewMatrix(countCol_secondMatrix, countRows_secondMatrix);

	int UserChoice = GetChoiceUser();
	matrixFirst = FullMatrix(1, UserChoice, matrixFirst, countCol_firstMatrix, countRows_firstMatrix);
	matrixSecond = FullMatrix(2, UserChoice, matrixSecond, countCol_secondMatrix, countRows_secondMatrix);

	OutMatrix(1, matrixFirst, countCol_firstMatrix, countRows_firstMatrix);
	OutMatrix(2, matrixSecond, countCol_secondMatrix, countRows_secondMatrix);

	while (length < countCol_firstMatrix || length < countCol_secondMatrix
		|| length < countRows_firstMatrix || length < countRows_secondMatrix)
		length *= 2;
	int** redactionMatrixFirst = DecreaseMatrix(length, matrixFirst, countCol_firstMatrix, countRows_firstMatrix);
	int** redactionMatrixSecond = DecreaseMatrix(length, matrixSecond, countCol_secondMatrix, countRows_secondMatrix);

	cout << "Приведенные матрицы\n";
	cout << "\nМатрица 1\n\n";
	OutMatrix(1, redactionMatrixFirst, length, length);
	cout << "\nМатрица 2\n\n";
	OutMatrix(2, redactionMatrixSecond, length, length);

	int*** SubMatrixFirst = CreateAndFullSubMatrix(length, redactionMatrixFirst);
	int*** SubMatrixSecond = CreateAndFullSubMatrix(length, redactionMatrixSecond);

	//Создание промежуточных матриц
	int*** p = CreatePromejMatrixs(length);
	//Вычисление значений промежуточных матриц 
	int*** PromejMatrixNew = CalculatePromejMatrix(length, p, SubMatrixFirst, SubMatrixSecond);
	//Работа со вспомогательными матрицами
	int*** SupportMatrix = SupportMatrixes(length, p);

	int** resultMatrix = CreateResultingMatrix(length, SupportMatrix);

	system("pause");


	//Освобождение памяти
	//for (int i = 0; i < countCol_firstMatrix; i++)
	//	delete[] matrixFirst[i];
	//for (int i = 0; i < countCol_secondMatrix; i++)
	//	delete[] matrixSecond[i];

	//for (int i = 0; i < length; i++)
	//{
	//	delete[] redactionMatrixFirst[i];
	//	delete[] redactionMatrixSecond[i];
	//	delete[] resultMatrix[i];
	//}

	delete[] matrixFirst, matrixSecond, redactionMatrixFirst, redactionMatrixSecond, resultMatrix;
	delete[] p, SubMatrixFirst, SubMatrixSecond;
	return 0;
}

