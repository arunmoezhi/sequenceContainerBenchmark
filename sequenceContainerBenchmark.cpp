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

template <typename T>
void insertInToContainer()
{
  vector<NonPrimitiveType> containedElements;
  containedElements.reserve(NUM_OF_ELEMENTS);
  for(int i=0;i<NUM_OF_ELEMENTS;i++)
  {
    containedElements.push_back(*(new NonPrimitiveType));
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
  printf("%d;%d;%c;%c;%lu\n",NUM_OF_ELEMENTS, OBJECT_SIZE, CONTAINER_TYPE, OPERATION, totalTime);
}

void insert()
{
  switch(CONTAINER_TYPE)
  {
    case 'v' :
    {
      insertInToContainer<vector<NonPrimitiveType>>();
      break;
    }
    case 'l' :
    {
      insertInToContainer<list<NonPrimitiveType>>();
      break;
    }
    case 'd' :
    {
      insertInToContainer<deque<NonPrimitiveType>>();
      break;
    }
  }
}

template <typename T>
void iterateOnContainer()
{
  vector<NonPrimitiveType> containedElements;
  containedElements.reserve(NUM_OF_ELEMENTS);
  for(int i=0;i<NUM_OF_ELEMENTS;i++)
  {
    containedElements.push_back(*(new NonPrimitiveType));
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
    for (const NonPrimitiveType& item : container)
    {
      hash = hash + item.x[1];
    }
	}
  auto end = chrono::high_resolution_clock::now();
	long long totalTime = chrono::duration_cast<chrono::nanoseconds>(end - begin).count() / NUM_OF_TRIALS;
  printf("%d;%d;%c;%c;%lu;%llu\n",NUM_OF_ELEMENTS, OBJECT_SIZE, CONTAINER_TYPE, OPERATION, totalTime, hash);
}

void iterate()
{
  switch(CONTAINER_TYPE)
  {
    case 'v' :
    {
      iterateOnContainer<vector<NonPrimitiveType>>();
      break;
    }
    case 'l' :
    {
      iterateOnContainer<list<NonPrimitiveType>>();
      break;
    }
    case 'd' :
    {
      iterateOnContainer<deque<NonPrimitiveType>>();
      break;
    }
  }
}

int main(int argc, char *argv[])
{
  NUM_OF_ELEMENTS = atoi(argv[1]);
  //OBJECT_SIZE = atoi(argv[2]);
  CONTAINER_TYPE = *argv[2];
  OPERATION = *argv[3];
  NUM_OF_TRIALS = atoi(argv[4]);
  
  switch(OPERATION)
  {
    case 'a' :
    {
      insert();
      break;
    }
    case 'i' :
    {
      iterate();
      break;
    }
  }  

	return 0;
}
