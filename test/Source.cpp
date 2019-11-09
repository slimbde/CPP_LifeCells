#include <iostream>
#include <chrono>


void swap(int* arr, int idx1, int idx2)
{
	auto temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}


void mySort(int* arr, int startIdx, int endIdx)
{
	if(endIdx - startIdx < 1)
		return;

	auto idLeft = startIdx;
	auto idRight = endIdx;

	while(idLeft < idRight)
	{
		while(arr[idLeft] <= arr[endIdx])
		{
			++idLeft;
			if(idLeft == endIdx)
				break;
		}

		while(arr[idRight] > arr[endIdx])
		{
			--idRight;
			if(idRight == startIdx)
				break;
		}

		if(idLeft < idRight)
			swap(arr, idLeft++, idRight);
	}

	while(arr[idLeft] < arr[endIdx])
	{
		++idLeft;
		if(idLeft == endIdx)
			break;
	}
	swap(arr, idLeft, endIdx);

	mySort(arr, startIdx, startIdx + idLeft - 1);
	mySort(arr, startIdx + idLeft, endIdx);
}



void fillRandom(int* arr, int size)
{
	while(size + 1)
		arr[size--] = rand() % 100;
}



/*------------------+
		MAIN		|
+------------------*/
int main()
{
	srand((unsigned int)time(NULL));
	// there is a difference to run whether under x86 or x64 architecture

	#define size 13
	int* arr = new int[size];

	auto print = [](int* arr) {
		for(int i = 0; i < size; ++i)
			std::cout << arr[i] << std::endl;
		std::cout << std::endl;
	};


	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	int it = 0;
	for(; it < 10'000'000; ++it)
	{
		fillRandom(arr, size);
		mySort(arr, 0, size - 1);
	}
	end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	print(arr);
	std::cout << duration << " ms for " << it << " iterations" << std::endl;



	//delete[] arr;
	std::cout << std::endl;
	system("pause");
	return 0;
}