#include <iostream>

void fillUP(double** arr, int M, int N)
{
	std::cout << "\nFill up the array:" << std::endl;
	for(int i = 0; i < M; ++i)
		for(int j = 0; j < N; ++j)
		{
			std::cout << "array [" << i << ", " << j << "] = ";
			std::cin >> arr[i][j];
		}
}




void myMultiply(double** arr, int M, int N, double* multArray)
{
	std::cout << "\nCounting:" << std::endl;

	for(int i = 0; i < M; ++i)
	{
		multArray[i] = 1.0;

		for(int j = 0; j < N; ++j)
			multArray[i] *= arr[i][j];

		std::cout << "multiply [" << i << "] = " << multArray[i] << std::endl;
	}
}




int main()
{
	int M = 2;	// rows
	int N = 2;	// columns

	std::cout << "Define rows count: ";
	std::cin >> M;
	std::cout << "Define columns count: ";
	std::cin >> N;

	double** arr = new double* [M];
	for(int i = 0; i < M; ++i)
		arr[i] = new double[N];

	fillUP(arr, M, N);

	double* result = new double[M];
	myMultiply(arr, M, N, result);


	delete[] result;

	for(int i = 0; i < M; ++i)
		delete[] arr[i];
	delete[] arr;

	std::cout << std::endl;
	system("pause");
	return 0;
}