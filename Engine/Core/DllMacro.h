#pragma once
#ifdef ENGINE_DLL
	#define ENGINEAPI __declspec(dllexport) 
#else
	#define ENGINEAPI __declspec(dllimport)
#endif