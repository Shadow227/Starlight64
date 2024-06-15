#pragma once

#ifdef SLE_PLATEFORM_WINDOWS
	#ifdef SLE_BUILD_DLL
		#define SLE_API __declspec(dllexport)
	#else
		#define SLE_API __declspec(dllimport)
	#endif
#else
#error Starlight Game Engine only suports Window(64)
#endif