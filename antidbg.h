#include <windows.h>
#include <iostream>
#include <thread>
#include <tlhelp32.h>
#include "..\misc\xorstr.hpp"


void IfDebugActiveProcess(const char*);
typedef NTSTATUS(__stdcall* _NtSetInformationThread)(_In_ HANDLE, _In_ THREAD_INFORMATION_CLASS, _In_ PVOID, _In_ ULONG);

void IfDebugString()
{
	SetLastError(0);
	OutputDebugStringA(xorstr_("Protection"));
	if (GetLastError() != 0)
	{
		(exit)(0);
	}
}

void IfIsDebuggerPresent()
{
	BOOL found = false;
	found = IsDebuggerPresent();
	if (found)
	{
		(exit)(0);
	}
}

void IfCheckRemoteDebuggerPresent()
{
	HANDLE process = INVALID_HANDLE_VALUE;
	BOOL found = false;
	process = GetCurrentProcess();
	CheckRemoteDebuggerPresent(process, &found);
	if (found)
	{
		(exit)(0);
	}
}

void IfCheckWindowClassName()
{
	BOOL found = false;
	HANDLE window = NULL;
	const wchar_t* x64dbg = xorstr_(L"Qt5QWindowIcon");
	const wchar_t* processhacker1 = xorstr_(L"ProcessHacker");
	const wchar_t* processhacker2 = xorstr_(L"MainWindowClassName");
	const wchar_t* processhacker3 = xorstr_(L"discord");
	const wchar_t* filegrab = xorstr_(L"WindowsForms10.Window.8.app.0.33c0d9d");
	const wchar_t* ida = xorstr_(L"Qt5153QTQWindowIcon");
	const wchar_t* cheatengine = L"Window";
	window = FindWindowW(x64dbg, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(processhacker1, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(processhacker2, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(processhacker3, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(filegrab, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(ida, NULL);
	if (window)
	{
		found = true;
	}
	window = FindWindowW(cheatengine, NULL);
	if (window)
	{
		found = true;
	}
	if (found)
	{
		(exit)(0);
	}
}

void IfDebugActiveProcess(const char* cpid)
{
	BOOL found = false;
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	TCHAR szPath[MAX_PATH];
	DWORD exitCode = 0;
	if (GetLastError() != ERROR_SUCCESS)
	{
		if (DebugActiveProcess((DWORD)atoi(cpid)))
		{
			return;
		}
		else
		{
			(exit)(555);
		}
	}
	DWORD pid = GetCurrentProcessId();
	GetModuleFileName(NULL, szPath, MAX_PATH);
	char cmdline[MAX_PATH + 1 + sizeof(int)];
	snprintf(cmdline, sizeof(cmdline), xorstr_("%ws %d"), szPath, pid);
	BOOL success = CreateProcessA(
		NULL,
		cmdline,
		NULL,
		NULL,
		false,
		0,
		NULL,
		NULL,
		&si,
		&pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(pi.hProcess, &exitCode);
	if (exitCode == 555)
	{
		found = true;
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	if (found)
	{
		(exit)(0);
	}
}

DWORD WINAPI Dummy(LPVOID lpParam)
{
	while (true)
	{
		Sleep(0);
	}
}

void IfResumeDummy()
{
	HANDLE dummy = CreateThread(NULL, NULL, Dummy, NULL, NULL, NULL);
	while (true)
	{
		if (ResumeThread(dummy) >= 1)
		{
			(exit)(0);
			for (long long int i = 0; ++i; (&i)[i] = i);
			*((char*)NULL) = 0;
		}
		Sleep(1);
	}
}

void IfCloseHandleException()
{
	HANDLE Invalid = (HANDLE)0xBEEF;
	DWORD found = false;
	__try
	{
		CloseHandle(Invalid);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		found = true;
	}
	if (found)
	{
		(exit)(0);
	}
}

void IfHardwareDebugRegisters2()
{
	BOOL found = false;
	CONTEXT ctx = { 0 };
	HANDLE hThread = GetCurrentThread();

	ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	if (GetThreadContext(hThread, &ctx))
	{
		if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
		{
			found = true;
		}
	}
	if (found)
	{
		(exit)(0);
	}
}

void IfNtSetInformationThread()
{
	THREAD_INFORMATION_CLASS ThreadHideFromDebugger = (THREAD_INFORMATION_CLASS)0x11;
	HMODULE hNtdll = LoadLibraryW(xorstr_(L"ntdll.dll"));
	if (hNtdll == INVALID_HANDLE_VALUE || hNtdll == NULL)
	{
		return;
	}
	_NtSetInformationThread NtSetInformationThread = NULL;
	NtSetInformationThread = (_NtSetInformationThread)GetProcAddress(hNtdll, xorstr_("NtSetInformationThread"));
	if (NtSetInformationThread == NULL)
	{
		return;
	}
	NtSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, 0, 0);
}

void IfDebugBreak2()
{
	__try
	{
		DebugBreak();
	}
	__except (GetExceptionCode() == EXCEPTION_BREAKPOINT ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
	}
}

bool IsThreadSuspended(DWORD threadId) {
	HANDLE hThread = OpenThread(THREAD_GET_CONTEXT, FALSE, threadId);
	if (hThread != nullptr) {
		CONTEXT context;
		context.ContextFlags = CONTEXT_CONTROL;

		if (GetThreadContext(hThread, &context)) {
			CloseHandle(hThread);
			return false;
		}

		CloseHandle(hThread);
		return true;
	}

	return false;
}
void IfUnpacked2()
{
	HMODULE hModule = GetModuleHandle(NULL);
	if (hModule != NULL)
	{
		PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)hModule + dosHeader->e_lfanew);
		PIMAGE_SECTION_HEADER sectionHeader = IMAGE_FIRST_SECTION(ntHeaders);
		for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++, sectionHeader++)
		{
			if (strcmp((char*)sectionHeader->Name, xorstr_(".SCY")) == 0)
			{
				(exit)(0);
			}
		}
	}
}

void CreateThread()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(30000));
	}
}

void Thread()
{
	while (true)
	{
		IsThreadSuspended(7448);
		IsThreadSuspended(14684);
		IsThreadSuspended(20476);
		IsThreadSuspended(21200);
		IfDebugString();
		IfIsDebuggerPresent();
		IfCheckRemoteDebuggerPresent();
		IfCheckWindowClassName();
		IfCloseHandleException();
		IfHardwareDebugRegisters2();
		IfNtSetInformationThread();
		IfDebugBreak2();
		IfUnpacked2();
	}
}
