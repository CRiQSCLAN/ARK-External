#include "ark_inits.h"

bool inits::init_console() {
	const char* date = __DATE__;
	const char* title = ("project msa | Built ");

	string final_title = string(title) + date;

	nsa_import(SetConsoleTitleA)(final_title.c_str());

	return true;
}

namespace utl
{
	inline DWORD get_process_id(
		const LPCWSTR process_name)
	{
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		DWORD procID = NULL;

		if (handle == INVALID_HANDLE_VALUE)
			return procID;

		PROCESSENTRY32W entry = { 0 };
		entry.dwSize = sizeof(PROCESSENTRY32W);

		if (Process32FirstW(handle, &entry)) {
			if (!_wcsicmp(process_name, entry.szExeFile))
			{
				procID = entry.th32ProcessID;
			}
			else while (Process32NextW(handle, &entry)) {
				if (!_wcsicmp(process_name, entry.szExeFile)) {
					procID = entry.th32ProcessID;
				}
			}
		}

		CloseHandle(handle);
		return procID;
	}
}

auto init_driver() -> bool
{
	//Sleep(5000);
	system(/*VMProtectDecryptStringA*/("cls"));

	if (!device_t.start_service())
		return false;

	device_t.m_pid = utl::get_process_id(_(L"ArkAscended.exe"));

	if (device_t.is_mapped(device_t.m_pid)) {

		device_t.m_base = device_t.get_module_base(0);

		if (!device_t.m_base) {
			printf(/*VMProtectDecryptStringA*/("invalid base address: 0x%llx.\n"), device_t.m_base);
			return false;
		}

		printf(/*VMProtectDecryptStringA*/("m_base: 0x%llx.\n"), device_t.m_base);

		if (!device_t.resolve_dtb()) {
			printf(/*VMProtectDecryptStringA*/("failed to get dtb.\n"));
			return false;
		}

		globals::memory::base_address = device_t.m_base;
	}

	Sleep(1000);
	system(/*VMProtectDecryptStringA*/("cls"));
}


bool inits::initialize() {

	if (!init_driver())
	{
		return false;
	}
	if (!init_console()) {
		return false;
	}

	return true;
}