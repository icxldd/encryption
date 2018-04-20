#include "windows.h"

#define C extern "C" 
#define nakedStdCall(v) _declspec(naked) v _stdcall 
#define stdCall _stdcall
