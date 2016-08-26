#include <iostream>
#include <new>
#include <chrono>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

int NUM_OF_ELEMENTS;
int NUM_OF_TRIALS;
char CONTAINER_TYPE;
char OPERATION;

class Type16
{
public:
	long x[4];
	Type16()
	{
		for (int i = 0; i < 4; i++)
		{
			x[i] = i;
		}
	}
};

class Type64
{
public:
	long x[16];
	Type64()
	{
		for (int i = 0; i < 16; i++)
		{
			x[i] = i;
		}
	}
};

class Type256
{
public:
	long x[64];
	Type256()
	{
		for (int i = 0; i < 64; i++)
		{
			x[i] = i;
		}
	}
};

class Type1K
{
public:
	long x[256];
	Type1K()
	{
		for (int i = 0; i < 256; i++)
		{
			x[i] = i;
		}
	}
};

class Type4K
{
public:
	long x[1024];
	Type4K()
	{
		for (int i = 0; i < 1024; i++)
		{
			x[i] = i;
		}
	}
};

template <typename T>
void insertFList(std::string typeName)
{
	long long totalTime = 0;
	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::forward_list<T> fList;
		for (int j = 0; j < NUM_OF_ELEMENTS; j++)
		{
			T* myT = new T;
			fList.push_front(*myT);
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NUM_OF_ELEMENTS;
		//std::cout << "iteration " << i << ": time for insert into flist in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg time for insert into  flist in ns: " << totalTime/NUM_OF_TRIALS << std::endl;
}

template <typename T>
void insertList(std::string typeName)
{
	long long totalTime = 0;
	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::list<T> list;
		for (int j = 0; j < NUM_OF_ELEMENTS; j++)
		{
			T* myT = new T;
			list.push_front(*myT);
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NUM_OF_ELEMENTS;
		//std::cout << "iteration " << i << ": time for insert into list in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg time for insert into   list in ns: " << totalTime / NUM_OF_TRIALS << std::endl;
}

template <typename T>
void insertVector(std::string typeName)
{
	long long totalTime = 0;
	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::vector<T> vec;
		for (int j = 0; j < NUM_OF_ELEMENTS; j++)
		{
			T* myT = new T;
			vec.push_back(*myT);
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NUM_OF_ELEMENTS;
		//std::cout << "iteration " << i << ": time for insert into list in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg time for insert into vector in ns: " << totalTime / NUM_OF_TRIALS << std::endl;
}

template <typename T>
void insertDeque(std::string typeName)
{
	long long totalTime = 0;
	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::deque<T> dq;
		for (int j = 0; j < NUM_OF_ELEMENTS; j++)
		{
			T* myT = new T;
			dq.push_back(*myT);
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / NUM_OF_ELEMENTS;
		//std::cout << "iteration " << i << ": time for insert into list in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg time for insert into  deque in ns: " << totalTime / NUM_OF_TRIALS << std::endl;
}

template <typename T>
void iterateFList(std::string typeName)
{
	long long totalTime = 0;
	long long hash = 0;
	std::forward_list<T> fList;
	for (int j = 0; j < NUM_OF_ELEMENTS; j++)
	{
		T* myT = new T;
		fList.push_front(*myT);
	}

	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (const T& item : fList)
		{
			hash = hash + item.x[1];
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		//std::cout << "iteration " << i << ": time for insert into flist in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg iteration time for    flist in ns: " << totalTime / NUM_OF_TRIALS  << "\t" << hash << std::endl;    
}

template <typename T>
void iterateList(std::string typeName)
{
	long long totalTime = 0;
	long long hash = 0;
	std::list<T> list;
	for (int j = 0; j < NUM_OF_ELEMENTS; j++)
	{
		T* myT = new T;
		list.push_front(*myT);
	}

	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (const T& item : list)
		{
			hash = hash + item.x[1];
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		//std::cout << "iteration " << i << ": time for insert into flist in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg iteration time for     list in ns: " << totalTime / NUM_OF_TRIALS << "\t" << hash << std::endl;
}

template <typename T>
void iterateVector(std::string typeName)
{
	long long totalTime = 0;
	long long hash = 0;
	std::vector<T> vec;
	for (int j = 0; j < NUM_OF_ELEMENTS; j++)
	{
		T* myT = new T;
		vec.push_back(*myT);
	}

	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (const T& item : vec)
		{
			hash = hash + item.x[1];
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		//std::cout << "iteration " << i << ": time for insert into flist in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg iteration time for   vector in ns: " << totalTime / NUM_OF_TRIALS << "\t" << hash << std::endl;
}

template <typename T>
void iterateDeque(std::string typeName)
{
	long long totalTime = 0;
	long long hash = 0;
	std::vector<T> dq;
	for (int j = 0; j < NUM_OF_ELEMENTS; j++)
	{
		T* myT = new T;
		dq.push_back(*myT);
	}

	for (int i = 0; i < NUM_OF_TRIALS; i++)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (const T& item : dq)
		{
			hash = hash + item.x[1];
		}
		auto end = std::chrono::high_resolution_clock::now();
		long long timeForThisIteration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
		//std::cout << "iteration " << i << ": time for insert into flist in ns: " << timeForThisIteration << std::endl;
		totalTime = totalTime + timeForThisIteration;
	}
	std::cout << typeName << "\t Avg iteration time for   deque in ns: " << totalTime / NUM_OF_TRIALS << "\t" << hash << std::endl;
}

int main(int argc, char *argv[])
{
  NUM_OF_ELEMENTS = atoi(argv[1]);
  NUM_OF_TRIALS = atoi(argv[2]);
  CONTAINER_TYPE = *argv[3];
  OPERATION = *argv[4];
  
	insertFList<Type16>("Type16");
	insertFList<Type64>("Type64");
	insertFList<Type256>("Type256");
	insertFList<Type1K>("Type1K");
	insertFList<Type4K>("Type4K");
	std::cout << "\n";

	insertList<Type16>("Type16");
	insertList<Type64>("Type64");
	insertList<Type256>("Type256");
	insertList<Type1K>("Type1K");
	insertList<Type4K>("Type4K");
	std::cout << "\n";

	insertVector<Type16>("Type16");
	insertVector<Type64>("Type64");
	insertVector<Type256>("Type256");
	insertVector<Type1K>("Type1K");
	insertVector<Type4K>("Type4K");
	std::cout << "\n";

	insertDeque<Type16>("Type16");
	insertDeque<Type64>("Type64");
	insertDeque<Type256>("Type256");
	insertDeque<Type1K>("Type1K");
	insertDeque<Type4K>("Type4K");
	std::cout << "\n";

	iterateFList<Type16>("Type16");
	iterateFList<Type64>("Type64");
	iterateFList<Type256>("Type256");
	iterateFList<Type1K>("Type1K");
	iterateFList<Type4K>("Type4K");
	std::cout << "\n";

	iterateList<Type16>("Type16");
	iterateList<Type64>("Type64");
	iterateList<Type256>("Type256");
	iterateList<Type1K>("Type1K");
	iterateList<Type4K>("Type4K");
	std::cout << "\n";

	iterateVector<Type16>("Type16");
	iterateVector<Type64>("Type64");
	iterateVector<Type256>("Type256");
	iterateVector<Type1K>("Type1K");
	iterateVector<Type4K>("Type4K");
	std::cout << "\n";

	iterateDeque<Type16>("Type16");
	iterateDeque<Type64>("Type64");
	iterateDeque<Type256>("Type256");
	iterateDeque<Type1K>("Type1K");
	iterateDeque<Type4K>("Type4K");
	std::cout << "\n";

	return 0;
}
