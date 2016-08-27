#include <iostream>
#include <new>
#include <chrono>
#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
using namespace std;

int NUM_OF_ELEMENTS;
int NUM_OF_TRIALS;
char CONTAINER_TYPE;
char OPERATION;

template<size_t OBJECT_SIZE>
class NonPrimitiveType
{
public:
	int x[OBJECT_SIZE/4];
	NonPrimitiveType()
	{
    for(int i=0;i<OBJECT_SIZE/4;i++)
    {
      x[i] = i;
    }
	}
};

template <typename T, size_t OBJECT_SIZE>
void insertInToContainer()
{
  vector<NonPrimitiveType<OBJECT_SIZE>> containedElements;
  containedElements.reserve(NUM_OF_ELEMENTS);
  for(int i=0;i<NUM_OF_ELEMENTS;i++)
  {
    containedElements.push_back(*(new NonPrimitiveType<OBJECT_SIZE>));
  }
  
  auto begin = chrono::high_resolution_clock::now();
	for (int i=0;i<NUM_OF_TRIALS;i++)
	{
		T container;
		for (int j=0;j<NUM_OF_ELEMENTS;j++)
		{
			container.push_back(containedElements[j]);
		}
	}
  auto end = chrono::high_resolution_clock::now();
	long long totalTime = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / (NUM_OF_TRIALS* NUM_OF_ELEMENTS);
  printf("%c;%c;%d;%d;%lu\n",CONTAINER_TYPE, OPERATION, NUM_OF_ELEMENTS, (int)OBJECT_SIZE, totalTime);
}

template<size_t OBJECT_SIZE>
void insert()
{
  switch(CONTAINER_TYPE)
  {
    case 'v' :
    {
      insertInToContainer<vector<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
    case 'l' :
    {
      insertInToContainer<list<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
    case 'd' :
    {
      insertInToContainer<deque<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
  }
}

template <typename T, size_t OBJECT_SIZE>
void iterateOnContainer()
{
  vector<NonPrimitiveType<OBJECT_SIZE>> containedElements;
  containedElements.reserve(NUM_OF_ELEMENTS);
  for(int i=0;i<NUM_OF_ELEMENTS;i++)
  {
    containedElements.push_back(*(new NonPrimitiveType<OBJECT_SIZE>));
  }
  
  T container;
	for (int i=0;i<NUM_OF_ELEMENTS;i++)
	{
		container.push_back(containedElements[i]);
	}
  
  long long hash = 0;
  auto begin = chrono::high_resolution_clock::now();
	for (int i=0;i<NUM_OF_TRIALS;i++)
	{
    for (const NonPrimitiveType<OBJECT_SIZE>& item : container)
    {
      hash = hash + item.x[1];
    }
	}
  auto end = chrono::high_resolution_clock::now();
	long long totalTime = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / NUM_OF_TRIALS;
	printf("%c;%c;%d;%d;%lu;%llu\n",CONTAINER_TYPE, OPERATION, NUM_OF_ELEMENTS, (int)OBJECT_SIZE, totalTime, hash);
}

template<size_t OBJECT_SIZE>
void iterate()
{
  switch(CONTAINER_TYPE)
  {
    case 'v' :
    {
      iterateOnContainer<vector<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
    case 'l' :
    {
      iterateOnContainer<list<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
    case 'd' :
    {
      iterateOnContainer<deque<NonPrimitiveType<OBJECT_SIZE>>, OBJECT_SIZE>();
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  NUM_OF_ELEMENTS = atoi(argv[1]);
  CONTAINER_TYPE = *argv[2];
  OPERATION = *argv[3];
  NUM_OF_TRIALS = atoi(argv[4]);
  
  switch(OPERATION)
  {
    case 'a' :
    {
      insert<16>();
			insert<64>();
			insert<256>();
			insert<1024>();
			insert<4096>();
      break;
    }
    case 'i' :
    {
      iterate<16>();
			iterate<64>();
			iterate<256>();
			iterate<1024>();
			iterate<4096>();
      break;
    }
  }  

	return 0;
}
