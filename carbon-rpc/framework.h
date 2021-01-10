#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <cstdio>
#include <windows.h>
#include "detours.h"
#include <vector>

const HMODULE MODULE_HANDLE = GetModuleHandle(NULL);
#define BASE_ADDRESS (int)GetModuleHandle(NULL)

#define ASLR(address) \
	((unsigned int)MODULE_HANDLE + (unsigned int)address - 0x400000)

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#define PROC_ADDRESS(libraryName, procName) \
	GetProcAddress(LoadLibrary(TEXT(libraryName)), procName)

#define HOOK(returnType, callingConvention, functionName, location, ...) \
    typedef returnType callingConvention functionName(__VA_ARGS__); \
    functionName* original##functionName = (functionName*)(location); \
    returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INSTALL_HOOK(functionName) \
	{ \
		DetourTransactionBegin(); \
		DetourUpdateThread(GetCurrentThread()); \
		DetourAttach((void**)&original##functionName, implOf##functionName); \
		DetourTransactionCommit(); \
	}

#define VTABLE_HOOK(returnType, callingConvention, className, functionName, ...) \
	typedef returnType callingConvention functionName(className* This, __VA_ARGS__); \
	functionName* original##functionName; \
	returnType callingConvention implOf##functionName(className* This, __VA_ARGS__)

#define INSTALL_VTABLE_HOOK(object, functionName, functionIndex) \
	{ \
		void** addr = &(*(void***)object)[functionIndex]; \
		if (*addr != implOf##functionName) \
		{ \
			original##functionName = (functionName*)*addr; \
			DWORD oldProtect; \
			VirtualProtect(addr, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect); \
			*addr = implOf##functionName; \
			VirtualProtect(addr, sizeof(void*), oldProtect, NULL); \
		} \
	}

#define WRITE_MEMORY(location, ...) \
	{ \
		const char data[] = { __VA_ARGS__ }; \
		DWORD oldProtect; \
		VirtualProtect((void*)location, sizeof(data), PAGE_EXECUTE_READWRITE, &oldProtect); \
		memcpy((void*)location, data, sizeof(data)); \
		VirtualProtect((void*)location, sizeof(data), oldProtect, NULL); \
	}

#define WRITE_FUNCTION(location, func)\
	{ \
		DWORD oldProtect; \
		void* address = (void*)func; \
		VirtualProtect((void*)location, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect); \
		memcpy((void*)location, &address, sizeof(void*)); \
		VirtualProtect((void*)location, sizeof(void*), oldProtect, NULL); \
	}

#define OBJECT_FUNCTION(returnType, function, location, ...) \
	inline returnType function(__VA_ARGS__) \
	{ \
		FUNCTION_PTR(returnType, __thiscall, Base##function, location, void* This, __VA_ARGS__);\
		return Base##function((void*)this, __VA_ARGS__);\
	} \