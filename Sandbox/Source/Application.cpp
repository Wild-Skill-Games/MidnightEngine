// MidnightEngine.cpp : Defines the entry point for the application.
//

#include "Application.h"

using namespace std;

namespace MidnightEngine
{
	__declspec(dllimport) void Print();
}

int main()
{
	cout << "Hello CMake." << endl;
	MidnightEngine::Print();
	return 0;
}
