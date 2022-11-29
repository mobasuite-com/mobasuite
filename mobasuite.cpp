#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>
#include <urlmon.h>
#include <ShlObj_core.h>
#include <tlhelp32.h>
#include <shellapi.h>
#include "Resource.h"

constexpr auto MAX_LOADSTRING = 100;
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

const wchar_t* dxx86_cab[] = {
	L"Apr2005_d3dx9_25_x86.cab",
	L"Apr2006_d3dx9_30_x86.cab",
	L"Apr2006_MDX1_x86.cab",
	L"Apr2006_MDX1_x86_Archive.cab",
	L"Apr2006_XACT_x86.cab",
	L"Apr2006_xinput_x86.cab",
	L"APR2007_d3dx9_33_x86.cab",
	L"APR2007_d3dx10_33_x86.cab",
	L"APR2007_XACT_x86.cab",
	L"APR2007_xinput_x86.cab",
	L"Aug2005_d3dx9_27_x86.cab",
	L"AUG2006_XACT_x86.cab",
	L"AUG2006_xinput_x86.cab",
	L"AUG2007_d3dx9_35_x86.cab",
	L"AUG2007_d3dx10_35_x86.cab",
	L"AUG2007_XACT_x86.cab",
	L"Aug2008_d3dx9_39_x86.cab",
	L"Aug2008_d3dx10_39_x86.cab",
	L"Aug2008_XACT_x86.cab",
	L"Aug2008_XAudio_x86.cab",
	L"Aug2009_D3DCompiler_42_x86.cab",
	L"Aug2009_d3dcsx_42_x86.cab",
	L"Aug2009_d3dx9_42_x86.cab",
	L"Aug2009_d3dx10_42_x86.cab",
	L"Aug2009_d3dx11_42_x86.cab",
	L"Aug2009_XACT_x86.cab",
	L"Aug2009_XAudio_x86.cab",
	L"Dec2005_d3dx9_28_x86.cab",
	L"DEC2006_d3dx9_32_x86.cab",
	L"DEC2006_d3dx10_00_x86.cab",
	L"DEC2006_XACT_x86.cab",
	L"Feb2005_d3dx9_24_x86.cab",
	L"Feb2006_d3dx9_29_x86.cab",
	L"Feb2006_XACT_x86.cab",
	L"FEB2007_XACT_x86.cab",
	L"Feb2010_X3DAudio_x86.cab",
	L"Feb2010_XACT_x86.cab",
	L"Feb2010_XAudio_x86.cab",
	L"Jun2005_d3dx9_26_x86.cab",
	L"JUN2006_XACT_x86.cab",
	L"JUN2007_d3dx9_34_x86.cab",
	L"JUN2007_d3dx10_34_x86.cab",
	L"JUN2007_XACT_x86.cab",
	L"JUN2008_d3dx9_38_x86.cab",
	L"JUN2008_d3dx10_38_x86.cab",
	L"JUN2008_X3DAudio_x86.cab",
	L"JUN2008_XACT_x86.cab",
	L"JUN2008_XAudio_x86.cab",
	L"Jun2010_D3DCompiler_43_x86.cab",
	L"Jun2010_d3dcsx_43_x86.cab",
	L"Jun2010_d3dx9_43_x86.cab",
	L"Jun2010_d3dx10_43_x86.cab",
	L"Jun2010_d3dx11_43_x86.cab",
	L"Jun2010_XACT_x86.cab",
	L"Jun2010_XAudio_x86.cab",
	L"Mar2008_d3dx9_37_x86.cab",
	L"Mar2008_d3dx10_37_x86.cab",
	L"Mar2008_X3DAudio_x86.cab",
	L"Mar2008_XACT_x86.cab",
	L"Mar2008_XAudio_x86.cab",
	L"Mar2009_d3dx9_41_x86.cab",
	L"Mar2009_d3dx10_41_x86.cab",
	L"Mar2009_X3DAudio_x86.cab",
	L"Mar2009_XACT_x86.cab",
	L"Mar2009_XAudio_x86.cab",
	L"Nov2007_d3dx9_36_x86.cab",
	L"Nov2007_d3dx10_36_x86.cab",
	L"NOV2007_X3DAudio_x86.cab",
	L"NOV2007_XACT_x86.cab",
	L"Nov2008_d3dx9_40_x86.cab",
	L"Nov2008_d3dx10_40_x86.cab",
	L"Nov2008_X3DAudio_x86.cab",
	L"Nov2008_XACT_x86.cab",
	L"Nov2008_XAudio_x86.cab",
	L"Oct2005_xinput_x86.cab",
	L"OCT2006_d3dx9_31_x86.cab",
	L"OCT2006_XACT_x86.cab"
};

const wchar_t* dxx64_cab[] = {
	L"Apr2005_d3dx9_25_x64.cab",
	L"Apr2006_d3dx9_30_x64.cab",
	L"Apr2006_XACT_x64.cab",
	L"Apr2006_xinput_x64.cab",
	L"APR2007_d3dx9_33_x64.cab",
	L"APR2007_d3dx10_33_x64.cab",
	L"APR2007_XACT_x64.cab",
	L"APR2007_xinput_x64.cab",
	L"Aug2005_d3dx9_27_x64.cab",
	L"AUG2006_XACT_x64.cab",
	L"AUG2006_xinput_x64.cab",
	L"AUG2007_d3dx9_35_x64.cab",
	L"AUG2007_d3dx10_35_x64.cab",
	L"AUG2007_XACT_x64.cab",
	L"Aug2008_d3dx9_39_x64.cab",
	L"Aug2008_d3dx10_39_x64.cab",
	L"Aug2008_XACT_x64.cab",
	L"Aug2008_XAudio_x64.cab",
	L"Aug2009_D3DCompiler_42_x64.cab",
	L"Aug2009_d3dcsx_42_x64.cab",
	L"Aug2009_d3dx9_42_x64.cab",
	L"Aug2009_d3dx10_42_x64.cab",
	L"Aug2009_d3dx11_42_x64.cab",
	L"Aug2009_XACT_x64.cab",
	L"Aug2009_XAudio_x64.cab",
	L"Dec2005_d3dx9_28_x64.cab",
	L"DEC2006_d3dx9_32_x64.cab",
	L"DEC2006_d3dx10_00_x64.cab",
	L"DEC2006_XACT_x64.cab",
	L"Feb2005_d3dx9_24_x64.cab",
	L"Feb2006_d3dx9_29_x64.cab",
	L"Feb2006_XACT_x64.cab",
	L"FEB2007_XACT_x64.cab",
	L"Feb2010_X3DAudio_x64.cab",
	L"Feb2010_XACT_x64.cab",
	L"Feb2010_XAudio_x64.cab",
	L"Jun2005_d3dx9_26_x64.cab",
	L"JUN2006_XACT_x64.cab",
	L"JUN2007_d3dx9_34_x64.cab",
	L"JUN2007_d3dx10_34_x64.cab",
	L"JUN2007_XACT_x64.cab",
	L"JUN2008_d3dx9_38_x64.cab",
	L"JUN2008_d3dx10_38_x64.cab",
	L"JUN2008_X3DAudio_x64.cab",
	L"JUN2008_XACT_x64.cab",
	L"JUN2008_XAudio_x64.cab",
	L"Jun2010_D3DCompiler_43_x64.cab",
	L"Jun2010_d3dcsx_43_x64.cab",
	L"Jun2010_d3dx9_43_x64.cab",
	L"Jun2010_d3dx10_43_x64.cab",
	L"Jun2010_d3dx11_43_x64.cab",
	L"Jun2010_XACT_x64.cab",
	L"Jun2010_XAudio_x64.cab",
	L"Mar2008_d3dx9_37_x64.cab",
	L"Mar2008_d3dx10_37_x64.cab",
	L"Mar2008_X3DAudio_x64.cab",
	L"Mar2008_XACT_x64.cab",
	L"Mar2008_XAudio_x64.cab",
	L"Mar2009_d3dx9_41_x64.cab",
	L"Mar2009_d3dx10_41_x64.cab",
	L"Mar2009_X3DAudio_x64.cab",
	L"Mar2009_XACT_x64.cab",
	L"Mar2009_XAudio_x64.cab",
	L"Nov2007_d3dx9_36_x64.cab",
	L"Nov2007_d3dx10_36_x64.cab",
	L"NOV2007_X3DAudio_x64.cab",
	L"NOV2007_XACT_x64.cab",
	L"Nov2008_d3dx9_40_x64.cab",
	L"Nov2008_d3dx10_40_x64.cab",
	L"Nov2008_X3DAudio_x64.cab",
	L"Nov2008_XACT_x64.cab",
	L"Nov2008_XAudio_x64.cab",
	L"Oct2005_xinput_x64.cab",
	L"OCT2006_d3dx9_31_x64.cab",
	L"OCT2006_XACT_x64.cab"
};

const wchar_t* vccpp[] = {
	L"api-ms-win-core-console-l1-1-0.dll",
	L"api-ms-win-core-datetime-l1-1-0.dll",
	L"api-ms-win-core-debug-l1-1-0.dll",
	L"api-ms-win-core-errorhandling-l1-1-0.dll",
	L"api-ms-win-core-file-l1-1-0.dll",
	L"api-ms-win-core-file-l1-2-0.dll",
	L"api-ms-win-core-file-l2-1-0.dll",
	L"api-ms-win-core-handle-l1-1-0.dll",
	L"api-ms-win-core-heap-l1-1-0.dll",
	L"api-ms-win-core-interlocked-l1-1-0.dll",
	L"api-ms-win-core-libraryloader-l1-1-0.dll",
	L"api-ms-win-core-localization-l1-2-0.dll",
	L"api-ms-win-core-memory-l1-1-0.dll",
	L"api-ms-win-core-namedpipe-l1-1-0.dll",
	L"api-ms-win-core-processenvironment-l1-1-0.dll",
	L"api-ms-win-core-processthreads-l1-1-0.dll",
	L"api-ms-win-core-processthreads-l1-1-1.dll",
	L"api-ms-win-core-profile-l1-1-0.dll",
	L"api-ms-win-core-rtlsupport-l1-1-0.dll",
	L"api-ms-win-core-string-l1-1-0.dll",
	L"api-ms-win-core-synch-l1-1-0.dll",
	L"api-ms-win-core-synch-l1-2-0.dll",
	L"api-ms-win-core-sysinfo-l1-1-0.dll",
	L"api-ms-win-core-timezone-l1-1-0.dll",
	L"api-ms-win-core-util-l1-1-0.dll",
	L"api-ms-win-crt-conio-l1-1-0.dll",
	L"api-ms-win-crt-convert-l1-1-0.dll",
	L"api-ms-win-crt-environment-l1-1-0.dll",
	L"api-ms-win-crt-filesystem-l1-1-0.dll",
	L"api-ms-win-crt-heap-l1-1-0.dll",
	L"api-ms-win-crt-locale-l1-1-0.dll",
	L"api-ms-win-crt-math-l1-1-0.dll",
	L"api-ms-win-crt-multibyte-l1-1-0.dll",
	L"api-ms-win-crt-private-l1-1-0.dll",
	L"api-ms-win-crt-process-l1-1-0.dll",
	L"api-ms-win-crt-runtime-l1-1-0.dll",
	L"api-ms-win-crt-stdio-l1-1-0.dll",
	L"api-ms-win-crt-string-l1-1-0.dll",
	L"api-ms-win-crt-time-l1-1-0.dll",
	L"api-ms-win-crt-utility-l1-1-0.dll"
};

wchar_t n[83][MAX_PATH + 1];

SHELLEXECUTEINFOW sei;
int c;
const wchar_t* cb_box[15] = {
	L"League of Legends", L"SMITE", L"DOTA2", L"Unreal Tournament (2017)", L"Minecraft: Java Edition",
	L"Black Desert", L"Paladins", L"World of Tanks (x64)", L"World of Warships (x64)", L"Lineage II",
	L"Elder Scrolls", L"GameLoop (Android Emulator)", L"DirectX9", L"VCRedist", L"Creative Alchemy",
};

void unblockfile(std::wstring file)
{
	DeleteFile(file.append(L":Zone.Identifier").c_str());
}

std::wstring j(const int j, const std::wstring& add)
{
	const std::filesystem::path p = n[j];
	return (p / add).c_str();
}

void pa(const int j, const std::wstring& add)
{
	std::filesystem::path p = n[j];
	const std::filesystem::path f = p / add;
	wcsncpy_s(n[j], f.c_str(), _TRUNCATE);
}

void pc(const int j, const int k, const std::wstring& add)
{
	std::filesystem::path p = n[k];
	const std::filesystem::path f = p / add;
	wcsncpy_s(n[j], f.c_str(), _TRUNCATE);
}

void cf(const int i, const int k, const std::wstring& add)
{
	copy_file(n[i], j(k, add), std::filesystem::copy_options::overwrite_existing);
}

void process_end(const std::wstring& name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(2, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if (Process32FirstW(snapshot, &process))
	{
		while (Process32NextW(snapshot, &process))
		{
			if (process.szExeFile == name)
			{
				snapshot = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, 1,
					process.th32ProcessID);
				TerminateProcess(snapshot, 0);
				break;
			}
		}
	}
	CloseHandle(snapshot);
}

void download(const std::wstring& url, int j)
{
	URLDownloadToFileW(nullptr, std::wstring(L"https://mobasuite.com/moba_files/" + url).c_str(), n[j], 0, nullptr);
	unblockfile(n[j]);
}


void bulk_apimswin(const wchar_t* url)
{
	for (int i = 0; i < 40; i++)
	{
		pc(i + 1, 0, vccpp[i]);
		download(&std::wstring(url + std::wstring(vccpp[i]))[0], i + 1);
	}
}

bool detect_x64()
{
	BOOL f64 = FALSE;
	return IsWow64Process(GetCurrentProcess(), &f64) && f64;
}

void cfg(const std::wstring& key)
{
	*n[0] = '\0';
	*n[82] = '\0';
	pa(82, std::filesystem::current_path());
	pa(82, L"mobasuite.ini");
	GetPrivateProfileString(L"Path", key.c_str(), nullptr, n[0], 261, n[82]);
	if (std::wstring(n[0]).empty())
	{
		BROWSEINFOW i{};
		i.ulFlags = 64 | 256 | 512 | 32768;
		if (key == L"al")
		{
			i.lpszTitle = L"<drive>:\\Program Files(x86)\\Warcraft III\\_retail_\\x86_64, <drive>:\\Program Files (x86)\\StarCraft\\x86_64, <drive>:\\Program Files (x86)\\World of Warcraft\\_retail_";
		}
		if (key == L"ll")
		{
			i.lpszTitle = L"<drive>:\\Riot Games\\";
			pa(0, L"League of Legends");
		}
		if (key == L"dota2" || key == L"pl")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\Steam";
		}
		if (key == L"sm")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\Steam\\steamapps\\common\\SMITE\\Binaries , <drive>:\\<Program Files>\\Epic Games\\SMITE\\Binaries";
		}
		if (key == L"gl")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\TxGameAssistant\\AppMarket";
		}
		if (key == L"es")
		{
			i.lpszTitle = L"<drive>:\\Zenimax Online\\The Elder Scrolls Online";
		}
		if (key == L"ut")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\Epic Games";
		}
		if (key == L"l2")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\NCSOFT";
		}
		if (key == L"wt")
		{
			i.lpszTitle = L"<drive>:\\Games\\World_of_Tanks_<region>\\win64";
		}
		if (key == L"ww")
		{
			i.lpszTitle = L"<drive>:\\Games\\World_of_Warships\\win64";
		}
		if (key == L"bd")
		{
			i.lpszTitle = L"<drive>:\\<Program Files>\\Black Desert Online";
		}
		if (key == L"dota2")
		{
			pa(0, L"<drive>:\\<Program Files>\\Steam\\steamapps\\common\\dota 2 beta\\game\\bin");
		}
		if (key == L"pl")
		{
			pa(0, L"<drive>:\\<Program Files>\\Steam\\steamapps\\common\\Paladins\\Binaries");
		}
		if (key == L"ut")
		{
			pa(0, L"UnrealTournament");
		}
		if (key == L"l2")
		{
			pa(0, L"Lineage II");
		}
		const auto dl = SHBrowseForFolderW(&i);
		if (dl == nullptr)
		{
			exit(0);
		}
		SHGetPathFromIDListW(dl, n[0]);
		WritePrivateProfileString(L"Path", key.c_str(), n[0], n[82]);
	}
}

void game(const std::wstring& dir, const std::wstring& key)
{
	for (int i = 0; i < 57; i++)
	{
		*n[i] = '\0';
	}
	cfg(key);
	pa(0, dir);
	pc(41, 0, L"D3DCompiler_42.dll");
	pc(42, 0, L"d3dx9_42.dll");
	pc(43, 0, L"d3dx11_42.dll");
	pc(44, 0, L"msvcp140.dll");
	pc(45, 0, L"ucrtbase.dll");
	pc(46, 0, L"vcruntime140.dll");
	pc(47, 0, L"d3dcompiler_43.dll");
	pc(48, 0, L"d3dcompiler_47.dll");
	pc(49, 0, L"concrt140.dll");
	pc(52, 0, L"vccorlib140.dll");
	pc(53, 0, L"mfc140u.dll");
	pc(54, 0, L"mfcm140u.dll");
	pc(55, 0, L"vcomp140.dll");
	pc(56, 0, L"vccorlib140.dll");
	pc(57, 0, L"d3dcompiler_46.dll");
}

void c_alchemy(bool restore)
{
	process_end(L"StarCraft.exe");
	process_end(L"WarCraft III.exe");
	process_end(L"Wow.exe");
	for (auto i = 0; i < 3; i++)
	{
		*n[i] = '\0';
	}
	cfg(L"al");
	unblockfile(j(0, L"StarCraft.exe"));
	unblockfile(j(0, L"WarCraft III.exe"));
	unblockfile(j(0, L"Wow.exe"));
	pc(1, 0, L"dsound.ini");
	pc(2, 0, L"dsound.dll");


	if (restore)
	{
		std::filesystem::remove_all(n[1]);
		std::filesystem::remove_all(n[2]);
	}
	else
	{
		download(L"bnet_alchemy/dsound.ini", 1);
		download(L"bnet_alchemy/dsound.dll", 2);
	}

	exit(0);
}

void dota2(bool restore)
{
	process_end(L"dota2.exe");
	if (detect_x64())
	{
		*n[1] = '\0';
		*n[2] = '\0';
		cfg(L"dota2");
		pa(0, L"win64");
		pc(1, 0, L"d3dcompiler_43.dll");
		pc(2, 0, L"embree.dll");
		unblockfile(j(0, L"dota2.exe"));
		if (restore)
		{
			download(L"r/dota/x64/d3dcompiler_43.dll", 1);
			download(L"r/dota/x64/embree.dll", 2);
		}
		else
		{
			download(L"6/D3DCompiler_47.dll", 1);
			download(L"6/embree3.dll", 2);
		}
	}
	*n[1] = '\0';
	cfg(L"dota2");
	pa(0, L"win32");
	pc(1, 0, L"d3dcompiler_43.dll");
	unblockfile(j(0, L"dota2.exe"));
	if (restore)
	{
		download(L"r/dota/d3dcompiler_43.dll", 1);
	}
	else
	{
		download(L"D3DCompiler_47.dll", 1);
	}
	cfg(L"dota2");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	if (detect_x64())
	{
		pa(0, L"win64");
	}
	else
	{
		pa(0, L"win32");
	}
	sei.lpFile = j(0, L"dota2.exe").c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void lineage2(bool restore)
{
	for (auto i = 0; i < 8; i++)
	{
		*n[i] = '\0';
	}
	process_end(L"NCLauncherR.exe");
	process_end(L"NCLauncher.exe");
	process_end(L"L2.bin");
	cfg(L"l2");
	pa(0, L"System");
	unblockfile(j(0, L"L2.bin"));
	pc(1, 0, L"d3dcompiler_43.dll");
	pc(2, 0, L"d3dcompiler_47.dll");
	pc(3, 0, L"D3DX9_40.dll");
	pc(4, 0, L"vcomp120.dll");
	pc(6, 0, L"plugins");
	if (restore)
	{
		download(L"r/l2/d3dcompiler_43.dll", 1);
		download(L"r/l2/d3dcompiler_47.dll", 2);
		download(L"r/l2/D3DX9_40.dll", 3);
		download(L"r/l2/vcomp120.dll", 4);
	}
	else
	{
		download(L"D3DCompiler_47.dll", 1);
		download(L"D3DCompiler_47.dll", 2);
		download(L"D3DX9_43.dll", 3);
		download(L"vcomp120.dll", 4);
	}
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	*n[0] = '\0';
	SHGetSpecialFolderPathW(nullptr, n[0], 42, 0);
	sei.lpParameters = L"/LauncherID:\"NCWest\" /CompanyID:\"12\" /GameID:\"LINEAGE2\" /LUpdateAddr:\"updater.nclauncher.ncsoft.com\"";
	sei.lpFile = j(0, L"NCWest\\NCLauncher\\NCLauncher.exe").c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void bdo_remastered(bool restore)
{
	process_end(L"BlackDesert32.exe");
	process_end(L"BlackDesert64.exe");
	cfg(L"bdo");
	game(L"bin", L"bdo");
	if (restore)
	{
		bulk_apimswin(L"r/bdo/");
		download(L"r/bdo/msvcp140.dll", 44);
		download(L"r/bdo/ucrtbase.dll", 45);
		download(L"r/bdo/vcruntime140.dll", 46);
		download(L"r/bdo/D3DCompiler_43.dll", 47);
		download(L"r/bdo/concrt140.dll", 49);
		download(L"r/bdo/mfc140u.dll", 53);
		download(L"r/bdo/mfcm140u.dll", 54);
		download(L"r/bdo/vcomp140.dll", 55);
		download(L"r/bdo/vccorlib140.dll", 56);
	}
	else
	{
		bulk_apimswin(L"");
		download(L"msvcp140.dll", 44);
		download(L"ucrtbase.dll", 45);
		download(L"vcruntime140.dll", 46);
		download(L"D3DCompiler_47.dll", 47);
		download(L"concrt140.dll", 49);
		download(L"mfc140u.dll", 53);
		download(L"mfcm140u.dll", 54);
		download(L"vcomp140.dll", 55);
		download(L"vccorlib140.dll", 56);
	}
	game(L"bin64", L"bdo");
	if (restore)
	{
		download(L"r/bdo/x64/msvcp140.dll", 44);
		download(L"r/bdo/x64/ucrtbase.dll", 45);
		download(L"r/bdo/x64/vcruntime140.dll", 46);
		download(L"r/bdo/x64/D3DCompiler_43.dll", 47);
		download(L"r/bdo/x64/concrt140.dll", 49);
		download(L"r/bdo/x64/mfc140u.dll", 53);
		download(L"r/bdo/x64/mfcm140u.dll", 54);
		download(L"r/bdo/x64/vcomp140.dll", 55);
		download(L"r/bdo/x64/vccorlib140.dll", 56);
		bulk_apimswin(L"r/bdo/x64/");
	}
	else
	{
		download(L"6/msvcp140.dll", 44);
		download(L"6/ucrtbase.dll", 45);
		download(L"6/vcruntime140.dll", 46);
		download(L"6/D3DCompiler_47.dll", 47);
		download(L"6/concrt140.dll", 49);
		download(L"6/mfc140u.dll", 53);
		download(L"6/mfcm140u.dll", 54);
		download(L"6/vcomp140.dll", 55);
		download(L"6/vccorlib140.dll", 56);
		bulk_apimswin(L"6/");
	}
	if (restore)
	{
		download(L"r/bdo/main/d3dcompiler_43.dll", 47);
		download(L"r/bdo/main/d3dcompiler_46.dll", 57);
	}
	else
	{
		download(L"D3DCompiler_47.dll", 47);
		download(L"D3DCompiler_47.dll", 57);
	}

	game(L"", L"bdo");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpFile = L"Black Desert Online Launcher.exe";
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void elderscrolls_online(bool restore)
{
	for (int i = 0; i < 7; i++)
	{
		*n[i] = '\0';
	}
	process_end(L"eso.exe");
	process_end(L"eso64.exe");
	cfg(L"es");
	pa(0, L"game\\client");
	pc(1, 0, L"tbb.dll");
	pc(2, 0, L"tbbmalloc.dll");
	pc(3, 0, L"x64");
	pc(4, 0, L"x86");
	pa(3, L"D3DCompiler_47.dll");
	pa(4, L"D3DCompiler_47.dll");
	pc(5, 0, L"eso.exe");
	pc(6, 0, L"eso64.exe");
	if (restore)
	{
		download(L"r/teso/tbb.dll", 1);
		download(L"r/teso/tbbmalloc.dll", 2);
		download(L"r/teso/x64/D3DCompiler_47.dll", 3);
		download(L"r/teso/D3DCompiler_47.dll", 4);
	}
	else
	{
		download(L"tbb12.dll", 1);
		download(L"tbbmalloc.dll", 2);
		download(L"6/D3DCompiler_47.dll", 3);
		download(L"D3DCompiler_47.dll", 4);
	}
	unblockfile(n[5]);
	unblockfile(n[6]);
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	if (detect_x64())
	{
		sei.lpFile = n[6];
	}
	else
	{
		sei.lpFile = n[5];
	}
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void worldoftanks(bool restore)
{
	for (int i = 0; i < 46; i++)
	{
		*n[i] = '\0';
	}
	cfg(L"wt");
	wchar_t wt[261] = L"WorldOfTanks.exe";
	process_end(L"WorldOfTanks.exe");
	unblockfile(j(0, wt));
	pc(41, 0, L"concrt140.dll");
	pc(42, 0, L"msvcp140.dll");
	pc(43, 0, L"tbb.dll");
	pc(44, 0, L"vcruntime140.dll");
	pc(45, 0, L"system");
	pc(46, 45, L"ucrtbase.dll");
	if (restore)
	{
		download(L"r/wg/concrt140.dll", 41);
		download(L"r/wg/msvcp140.dll", 42);
		download(L"r/wg/tbb12.dll", 43);
		download(L"r/wg/vcruntime140.dll", 44);
		download(L"r/wg/ucrtbase.dll", 46);
		pa(0, L"system");
		bulk_apimswin(L"r/wg/");
	}
	else
	{
		download(L"6/concrt140.dll", 41);
		download(L"6/msvcp140.dll", 42);
		download(L"6/tbb12.dll", 43);
		download(L"6/vcruntime140.dll", 44);
		download(L"6/ucrtbase.dll", 46);
		pa(0, L"system");
		bulk_apimswin(L"6/");
	}
	cfg(L"wt");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpFile = j(0, wt).c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void worldofwarships(bool restore)
{
	for (int i = 0; i < 46; i++)
	{
		*n[i] = '\0';
	}
	cfg(L"ww");
	wchar_t www[261] = L"WorldOfWarships.exe";
	process_end(L"WorldOfWarships.exe");
	unblockfile(j(0, www));
	pc(41, 0, L"msvcp140.dll");
	pc(42, 0, L"ucrtbase.dll");
	pc(43, 0, L"vcruntime140.dll");
	pc(44, 0, L"cef");
	pc(45, 44, L"d3dcompiler_43.dll");
	pc(46, 44, L"d3dcompiler_47.dll");
	if (restore)
	{
		bulk_apimswin(L"r/wg/");
		download(L"r/wg/msvcp140.dll", 41);
		download(L"r/wg/ucrtbase.dll", 42);
		download(L"r/wg/vcruntime140.dll", 43);
		pa(0, L"cef");
		download(L"r/wg/d3dcompiler_43.dll", 45);
		download(L"r/wg/d3dcompiler_47.dll", 46);
	}
	else
	{
		bulk_apimswin(L"6/");
		download(L"msvcp140.dll", 41);
		download(L"ucrtbase.dll", 42);
		download(L"vcruntime140.dll", 43);
		pa(0, L"cef");
		download(L"D3DCompiler_47.dll", 45);
		download(L"D3DCompiler_47.dll", 46);
	}
	cfg(L"ww");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpFile = j(0, www).c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void epicgames_launch(bool restore, bool lastsequence)
{
	if (lastsequence)
	{
		if (restore)
		{
			download(L"r/ut/d3dcompiler_43.dll", 47);
			download(L"r/ut/d3dcompiler_47.dll", 48);
		}
		else
		{
			download(L"6/D3DCompiler_47.dll", 47);
			download(L"6/D3DCompiler_47.dll", 48);
		}
		sei = {};
		sei.cbSize = sizeof(SHELLEXECUTEINFOW);
		sei.fMask = 64;
		sei.nShow = 5;
		*n[0] = '\0';
		SHGetSpecialFolderPathW(nullptr, n[0], 42, 0);
		sei.lpFile = j(0, L"Epic Games\\Launcher\\Portal\\Binaries\\Win32\\EpicGamesLauncher.exe").c_str();
		ShellExecuteExW(&sei);
		if (sei.hProcess != nullptr)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
		}
		exit(0);
	}
	if (restore)
	{
		bulk_apimswin(L"r/ut/");
		download(L"r/ut/concrt140.dll", 49);
		download(L"r/ut/ucrtbase.dll", 45);
		download(L"r/ut/vccorlib140.dll", 52);
		download(L"r/ut/msvcp140.dll", 44);
		download(L"r/ut/vcruntime140.dll", 46);
	}
	else
	{
		download(L"6/concrt140.dll", 49);
		bulk_apimswin(L"6/");
		download(L"6/ucrtbase.dll", 45);
		download(L"6/vccorlib140.dll", 52);
		download(L"6/msvcp140.dll", 44);
		download(L"6/vcruntime140.dll", 46);
	}
}

void ut_alpha(bool restore)
{
	cfg(L"ut");
	process_end(L"UE4-Win64-Shipping.exe");
	process_end(L"EpicGamesLauncher.exe");

	game(L"UnrealTournament\\UnrealTournament\\Binaries\\Win64", L"ut");
	epicgames_launch(restore, false);
	game(L"UnrealTournament\\Binaries\\Win64", L"ut");
	epicgames_launch(restore, false);
	game(L"UnrealTournament\\Engine\\Binaries\\Win64", L"ut");
	unblockfile(j(0, L"UE4-Win64-Shipping.exe"));
	epicgames_launch(restore, false);
	game(L"UnrealTournament\\Engine\\Binaries\\ThirdParty\\CEF3\\Win64", L"ut");
	epicgames_launch(restore, true);
}

void gameloop(bool restore)
{
	process_end(L"AppMarket.exe");
	process_end(L"QQExternal.exe");
	for (auto i = 0; i < 44; i++)
	{
		*n[i] = '\0';
	}
	cfg(L"gl");
	pc(40, 0, L"msvcp140.dll");
	pc(41, 0, L"ucrtbase.dll");
	pc(42, 0, L"vcomp140.dll");
	pc(43, 0, L"vcruntime140.dll");
	if (restore)
	{
		bulk_apimswin(L"r/gameloop");
		download(L"r/gameloop/msvcp140.dll", 40);
		download(L"r/gameloop/ucrtbase.dll", 41);
		download(L"r/gameloop/vcomp140.dll", 42);
		download(L"r/gameloop/vcruntime140.dll", 43);
	}
	else
	{
		bulk_apimswin(L"");
		download(L"msvcp140.dll", 40);
		download(L"ucrtbase.dll", 41);
		download(L"vcomp140.dll", 42);
		download(L"vcruntime140.dll", 43);
	}
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpFile = j(0, L"AppMarket.exe").c_str();
	unblockfile(j(0, L"AppMarket.exe"));
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void lol(bool restore)
{
	cfg(L"ll");
	pa(1, L"League of Legends.exe");
	pa(2, L"RiotClientServices.exe");
	pa(3, L"RiotClientUX.exe");
	pa(4, L"RiotClientUXRender.exe");
	pa(5, L"LeagueClient.exe");
	pa(6, L"LeagueClientUX.exe");
	pa(7, L"LeagueClientUXRender.exe");
	for (auto i = 1; i < 8; i++)
	{
		process_end(n[i]);
		*n[i] = '\0';
	}
	pc(54, 0, L"Riot Client");
	pa(0, L"League of Legends");
	pc(42, 0, L"Game");
	unblockfile(j(42, L"League of Legends.exe"));
	unblockfile(j(0, L"LeagueClient.exe"));
	unblockfile(j(0, L"LeagueClientUx.exee"));
	unblockfile(j(0, L"LeagueClientUxRender.exe"));
	unblockfile(j(54, L"RiotClientServices.exe"));
	pc(49, 42, L"D3DCompiler_43.dll");
	pc(44, 0, L"concrt140.dll");
	pc(45, 0, L"vcruntime140.dll");
	pc(46, 0, L"ucrtbase.dll");
	pc(47, 0, L"msvcp140.dll");
	pc(48, 42, L"tbb.dll");
	pc(50, 42, L"D3DCompiler_47.dll");
	pc(51, 0, L"D3DCompiler_47.dll");
	pc(52, 0, L"msvcp140_1.dll");
	pc(53, 0, L"msvcp140_2.dll");

	if (restore)
	{

		bulk_apimswin(L"r/lol/");
		download(L"r/lol/D3DCompiler_43.dll", 42);
		download(L"r/lol/concrt140.dll", 44);
		download(L"r/lol/vcruntime140.dll", 45);
		download(L"r/lol/ucrtbase.dll", 46);
		download(L"r/lol/msvcp140.dll", 47);
		download(L"r/lol/D3DCompiler_43.dll", 49);
		download(L"r/lol/d3dcompiler_47.dll", 50);
		download(L"r/lol/d3dcompiler_47.dll", 51);
		download(L"r/lol/msvcp140_1.dll", 52);
		download(L"r/lol/msvcp140_2.dll", 53);
		std::filesystem::remove_all(n[48]);
	}
	else
	{

		download(L"concrt140.dll", 44);
		download(L"vcruntime140.dll", 45);
		download(L"ucrtbase.dll", 46);
		download(L"msvcp140.dll", 47);
		download(L"D3DCompiler_47.dll", 50);
		download(L"D3DCompiler_47.dll", 51);
		download(L"msvcp140_1.dll", 52);
		download(L"msvcp140_2.dll", 53);
		if (detect_x64())
		{
			bulk_apimswin(L"6/");
			download(L"6/tbb12.dll", 48);
			download(L"6/D3DCompiler_47.dll", 49);
		}
		else
		{
			bulk_apimswin(L"");
			download(L"tbb12.dll", 48);
			download(L"D3DCompiler_47.dll", 49);
		}
	}
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpFile = j(0, L"LeagueClient.exe").c_str();

	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void smite(bool restore)
{
	pa(1, L"HirezLauncherUI.exe");
	pa(2, L"Smite.exe");
	pa(3, L"SteamLauncherUI.exe");
	for (auto i = 1; i < 6; i++)
	{
		process_end(n[i]);
		*n[i] = '\0';
	}
	cfg(L"sm");
	pc(6, 0, L"win32");
	pa(0, L"Win64");
	pc(1, 0, L"tbbmalloc.dll");
	pc(2, 0, L"concrt140.dll");
	pc(3, 0, L"vccorlib140.dll");
	pc(4, 0, L"vcruntime140.dll");
	pc(5, 0, L"d3dcompiler_46.dll");
	unblockfile(j(0, L"Smite.exe"));
	unblockfile(j(0, L"ShippingPC - BattleGame.exe"));
	unblockfile(j(0, L"SmiteEAC.exe"));
	if (restore)
	{
		download(L"r/hirez/s/x64/tbbmalloc.dll", 1);
		download(L"r/hirez/s/x64/concrt140.dll", 2);
		download(L"r/hirez/s/x64/vccorlib140.dll", 3);
		download(L"r/hirez/s/x64/vcruntime140.dll", 4);
		download(L"r/hirez/s/x64/d3dcompiler_46.dll", 5);
	}
	else
	{
		download(L"6/tbbmalloc.dll", 1);
		download(L"6/concrt140.dll", 2);
		download(L"6/vccorlib140.dll", 3);
		download(L"6/vcruntime140.dll", 4);
		download(L"6/D3DCompiler_47.dll", 5);
	}
	for (auto i = 7; i < 12; i++)
	{
		*n[i] = '\0';
	}
	pc(7, 6, L"tbbmalloc.dll");
	pc(8, 6, L"concrt140.dll");
	pc(9, 6, L"vccorlib140.dll");
	pc(10, 6, L"vcruntime140.dll");
	pc(11, 6, L"d3dcompiler_46.dll");
	unblockfile(j(6, L"Smite.exe"));
	unblockfile(j(6, L"ShippingPC - BattleGame.exe"));
	unblockfile(j(6, L"SmiteEAC.exe"));
	if (restore)
	{
		download(L"r/hirez/s/tbbmalloc.dll", 7);
		download(L"r/hirez/s/concrt140.dll", 8);
		download(L"r/hirez/s/vccorlib140.dll", 9);
		download(L"r/hirez/s/vcruntime140.dll", 10);
		download(L"r/hirez/s/d3dcompiler_46.dll", 11);
	}
	else
	{
		download(L"tbbmalloc.dll", 7);
		download(L"concrt140.dll", 8);
		download(L"vccorlib140.dll", 9);
		download(L"vcruntime140.dll", 10);
		download(L"D3DCompiler_47.dll", 11);
	}

	MessageBox(nullptr,
		L"Done !",
		L"Patch Status", MB_OK);
	exit(0);
}

void paladins(bool restore)
{
	process_end(L"HirezLauncherUI.exe");
	process_end(L"Paladins.exe");
	process_end(L"SteamLauncherUI.exe");
	if (detect_x64())
	{
		*n[0] = '\0';
		*n[1] = '\0';
		cfg(L"pl");
		pa(0, L"Win64");
		pc(1, 0, L"tbbmalloc.dll");
		unblockfile(j(0, L"Paladins.exe"));
		if (restore)
		{
			download(L"r/hirez/p/x64/tbbmalloc.dll", 1);
		}
		else
		{
			download(L"6/tbbmalloc.dll", 1);
		}
	}
	*n[0] = '\0';
	*n[1] = '\0';
	cfg(L"pl");
	pa(0, L"Win32");
	pc(1, 0, L"tbbmalloc.dll");
	unblockfile(j(0, L"Paladins.exe"));
	if (restore)
	{
		download(L"r/hirez/p/tbbmalloc.dll", 1);
	}
	else
	{
		download(L"tbbmalloc.dll", 1);
	}
	cfg(L"pl");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpParameters = L"game=400 product=402";
	sei.lpFile = j(0, L"SteamLauncherUI.exe").c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	exit(0);
}

void minecraft()
{
	*n[82] = '\0';
	pa(82, std::filesystem::current_path());
	if (detect_x64())
	{
		pa(82, L"jdk-19_windows-x64_bin.exe");
		download(L"jdk-19_windows-x64_bin.exe", 82);
	}
	else
	{
		pa(82, L"jdk-8u351-windows-i586.exe");
		download(L"jdk-8u351-windows-i586.exe", 82);
	}
	if (detect_x64())
	{
		sei = {};
		sei.cbSize = sizeof(SHELLEXECUTEINFOW);
		sei.fMask = 64;
		sei.nShow = 5;
		sei.lpFile = n[82];
		ShellExecuteExW(&sei);
		if (sei.hProcess != nullptr)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
		}
		std::filesystem::remove_all(n[0]);
		MessageBox(nullptr,
			L"Minecraft Launcher > Minecraft: Java Edition > Installations > Latest > Edit > More Options > Java Executable Path > <drive>:\\Program Files\\Java\\jdk-19\\bin\\javaw.exe",
			L"Post-Install Instructions", MB_OK);
	}
	else
	{
		sei = {};
		sei.cbSize = sizeof(SHELLEXECUTEINFOW);
		sei.fMask = 64;
		sei.nShow = 5;
		sei.lpFile = n[82];
		ShellExecuteExW(&sei);
		if (sei.hProcess != nullptr)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
		}
		std::filesystem::remove_all(n[0]);
		MessageBox(nullptr,
			L"Minecraft Launcher > Minecraft: Java Edition > Installations > Latest > Edit > More Options > Java Executable Path > <drive>:\\Program Files\\Java\\jre-8u351\\bin\\javaw.exe",
			L"Post-Install Instructions", MB_OK);
	}

}

void unblock_dx9()
{
	*n[82] = '\0';
	pa(82, std::filesystem::current_path());
	pa(82, L"temp_dx");
	std::filesystem::create_directory(n[82]);
	for (auto i = 0; i < 77; i++)
	{
		*n[i] = '\0';
		pc(i, 82, dxx86_cab[i]);
		download(&std::wstring(L"dx9/" + std::wstring(dxx86_cab[i]))[0], i);
	}
	if (detect_x64())
	{
		for (auto i = 0; i < 75; i++)
		{
			*n[i] = '\0';
			pc(i, 82, dxx64_cab[i]);
			download(&std::wstring(L"dx9/" + std::wstring(dxx64_cab[i]))[0], i);
		}
	}

	const wchar_t* dxsetup_files[] = {
	L"DSETUP.dll", L"dsetup32.dll", L"dxdllreg_x86.cab", L"DXSETUP.exe", L"dxupdate.cab"
	};

	for (auto i = 0; i < 4; i++)
	{
		*n[i] = '\0';
		pc(i, 82, dxsetup_files[i]);
		download(&std::wstring(L"dx9/" + std::wstring(dxsetup_files[i]))[0], i);
	}
	process_end(L"DXSETUP.exe");
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	sei.lpParameters = L"/silent";
	sei.lpFile = j(82, L"DXSETUP.exe").c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	std::filesystem::remove_all(n[82]);
}


void winaio(bool restore)
{
	*n[0] = '\0';
	pa(0, std::filesystem::current_path());
	pa(0, L"aboddi_vcredist.exe");
	download(L"VisualCppRedist_AIO.exe", 0);
	sei = {};
	sei.cbSize = sizeof(SHELLEXECUTEINFOW);
	sei.fMask = 64;
	sei.nShow = 5;
	if (restore)
	{
		sei.lpParameters = L"/aiD";
	}
	else
	{
		sei.lpParameters = L"/aiD /ai /gm2";
	}
	sei.lpFile = std::wstring(n[0]).c_str();
	ShellExecuteExW(&sei);
	if (sei.hProcess != nullptr)
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
	}
	std::filesystem::remove_all(n[0]);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	if (detect_x64())
	{
		*n[82] = '\0';
		pa(82, std::filesystem::current_path());
		pa(82, L"vc_redist.x64.exe");
		download(L"vc_redist.x64.exe", 82);
		sei = {};
		sei.cbSize = sizeof(SHELLEXECUTEINFOW);
		sei.fMask = 64;
		sei.nShow = 5;
		sei.lpFile = n[82];
		sei.lpParameters = L"/q /norestart";
		ShellExecuteExW(&sei);
		if (sei.hProcess != nullptr)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
		}
		std::filesystem::remove_all(n[82]);
	}
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MOBASUITE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOBASUITE));
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return static_cast<int>(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOBASUITE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MOBASUITE);
	wcex.lpszClassName = szWindowClass;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindow(szWindowClass, L"MOBASuite FPS-Booster", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 470, 180,
		nullptr, nullptr, hInstance, nullptr);

	CreateWindow(L"BUTTON", L"Patch", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 100,
		100, hWnd, reinterpret_cast<HMENU>(1), hInstance, nullptr);
	CreateWindow(L"BUTTON", L"Restore", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 350, 10, 100,
		100, hWnd, reinterpret_cast<HMENU>(2), hInstance, nullptr);
	HWND hWndComboBox = CreateWindow(WC_COMBOBOX, L"",
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		120, 10, 220, 360, hWnd, NULL, hInstance,
		NULL);
	for (auto& i : cb_box)
	{
		SendMessage(hWndComboBox, CB_ADDSTRING, static_cast<WPARAM>(0), reinterpret_cast<LPARAM>(i));
	}
	SendMessage(hWndComboBox, CB_SETCURSEL, static_cast<WPARAM>(0), 0);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			c = SendMessage(reinterpret_cast<HWND>(lParam), static_cast<UINT>(CB_GETCURSEL), static_cast<WPARAM>(0), 0);
		}
		if (LOWORD(wParam) == 1)
		{
			switch (c)
			{
			case 0:
				lol(false);
				break;
			case 1:
				smite(false);
				break;
			case 2:
				dota2(false);
				break;
			case 3:
				ut_alpha(false);
				break;
			case 4:
				minecraft();
				break;
			case 5:
				bdo_remastered(false);
				break;
			case 6:
				paladins(false);
				break;
			case 7:
				worldoftanks(false);
				break;
			case 8:
				worldofwarships(false);
				break;
			case 9:
				lineage2(false);
				break;
			case 10:
				elderscrolls_online(false);
				break;
			case 11:
				gameloop(false);
				break;
			case 12:
				unblock_dx9();
				break;
			case 13:
				winaio(false);
				break;
			case 14:
				c_alchemy(false);
				break;
			default:;
			}
		}
		else if (LOWORD(wParam) == 2)
		{
			switch (c)
			{
			case 0:
				lol(true);
				break;
			case 1:
				smite(true);
				break;
			case 2:
				dota2(true);
				break;
			case 3:
				ut_alpha(true);
				break;
			case 5:
				bdo_remastered(true);
				break;
			case 6:
				paladins(true);
				break;
			case 7:
				worldoftanks(true);
				break;
			case 8:
				worldofwarships(true);
				break;
			case 9:
				lineage2(true);
				break;
			case 10:
				elderscrolls_online(true);
				break;
			case 11:
				gameloop(true);
				break;
			case 12:
				unblock_dx9();
				break;
			case 13:
				winaio(true);
				break;
			case 14:
				c_alchemy(true);
				break;
			default:;
			}
		}

		switch (LOWORD(wParam))
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	default:;
	}
	return FALSE;
}
