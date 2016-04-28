#include <iostream>
#include "auxStructs.h"
#include "gameBoard.h"

bool engHistTest(int po, int p1)
{

	std::cout << "Poop" << po << p1 << std::endl;
	std::cout << uint64_t(122) << std::endl;

	engHistory eng;
	uint64_t b[9] = { 1,2,3,4,5,6,7,8,9 };
	uint64_t a[9] = { 6,4,4,4,5,4,7,8,9 };
	uint64_t c[9] = { 431,6,3,5,5,67,7,8,9 };
	uint64_t d[9] = { 431,6,3,5,5,67,7,8,3 };
	eng.add(a);
	eng.add(b);
	eng.add(c);

	for (int i = 0; i < HIST_MAX / 2; i++)
	{
		eng.add(a);
	}
	eng.add(b);
	eng.add(c);
	eng.add(c);
	eng.add(b);
	eng.add(c);
	eng.add(a);
	eng.add(a);
	std::cout << eng.checkForTriples() << std::endl;
	eng.add(b);
	std::cout << eng.checkForTriples() << std::endl;
	std::cout << eng.checkForTriples(2) << std::endl;
	eng.add(d);
	eng.add(d);

	std::cout << eng.checkForTriples() << std::endl;

	getchar();

	return 0;
}

typedef void* (*f_p)(void*, void*, void*, void*);
typedef void* (*f_p0)();

f_p0 funGen(f_p funct, void* arg0 = nullptr, void* arg1 = nullptr, void* arg2 = nullptr, void* arg3 = nullptr)
{
	return (f_p0)funct(arg0, arg1, arg2, arg3);
}

void bo(int &p, int* pp)
{
	p = 0x666;
	pp[1] = 0x666;
	pp[3] *= 20;
	std::cout << sizeof(pp) << "\n"
		<< sizeof(bool) << "\n"
		<< pp[3] << "\n";
	getchar();
}

class A
{
public:
	A()
	{

	}
	~A()
	{

	}

	template< typename T>
	void combine(T* const arr1, int size1, T* const arr2, int size2, T* dest)
	{
		T* tmp = (T*)malloc((size1 + size2)*sizeof(T));

		memcpy(tmp, arr1, size1*(sizeof(T)));
		memcpy(tmp + size1, arr2, size2*(sizeof(T)));

		//free(arr1);
		//free(arr2);

		//free(dest);
		memcpy(dest, tmp, sizeof(tmp));

	}


};

int main()
{
	//engHistTest(13,11);

	int a[] = { 1,2,3,4,5 };
	int b[] = { 9,6,9,6 };

	int w[10];
	int* y;

	A co;

	co.combine(a, 5, b, 4, w);
	for (int i = 0; i < 9; i++)
	{
		std::cout << *(w + i) << "\n";
	}

	//w = y;

	getchar();


	//80 -> 20, 20, 20, 20
	// 20v20
	//5v5
	//5
	int me = 99;
	auto lm = []()->int* {int i[] = { 1,2,3,4,5,6 }; return i;};
	int* p = lm();
	bo(me, p);

	int pt[6];
	p = pt;


	(me = 11) = me * 8;

	int* bob = new int[400];

	bo(me, bob);

	std::cout << sizeof(void*) << "\n"
		<< sizeof(uint64_t) << "\n"
		<< sizeof(bob) << "\n"
		<< (bob[1]) << "\n"
		<< sizeof(uint64_t*) << "\n";

	std::cout << me;

	getchar();

	auto blah{ &engHistTest };
	blah(11, 12);
	
	std::cout << sizeof(blah(99,13));

	f_p0 bloh = (f_p0)engHistTest;
	getchar();



	int c[] = { 10,11 };	
	std::cout << (typeid(engHistTest)).name();
	std::cout << (typeid(main)).raw_name() << "\n\n**";
	int res;
	int * re = &res;
	int ** r = &re;
	**r = 21;

	//genFunct((funct_ptr5)engHistTest(11, 12), (void***)resp, 0);

	std::cout << "\n\nRes: " << res << "\n";
//	int x = 0; 

	//std::string functInfo = typeid()
	//bool __cdecl(int,int)int __cdecl(void)
	void* rest = nullptr;
	(funGen((f_p)engHistTest, rest, (void*)11, (void*)19))();
	

	std::cout << "\n\nRes: " << res << "\n" << rest << "\n" << rest;

	getchar();
	return 0;
}