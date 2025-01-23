#include "includes.hpp"
#include <shellapi.h> 

void start_overlay() {
	ShellExecute(NULL, "open", "C:\\Windows\\system32\\snippingtool.exe", NULL, NULL, SW_SHOWNORMAL);
}

auto start_ue5_renderer() -> void {
	UnrealEngine5::render ue5_renderer(0);

	thread([&]() { ue5_renderer.run_actor_loop(); }).detach();
	thread([&]() { ue5_renderer.run_camera_loop(); }).detach();
	//thread( [ & ]( ) { ue5_renderer.run_aimbot_loop( ); } ).detach( );

	return ue5_renderer.run_render_loop();
}
uint64_t FindModuleBaseAddress(uint64_t ProcessID, const char* modulename)
{
	uint64_t BaseAddress = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 Module{};
		Module.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(snapshot, &Module))
		{
			while (BaseAddress == 0)
			{
				if (strcmp(Module.szModule, modulename) == 0)
				{
					BaseAddress = (uint64_t)Module.modBaseAddr;
				}
				else
					Module32Next(snapshot, &Module);
			}
		}
		CloseHandle(snapshot);
	}
	return BaseAddress;
}
auto main() -> int {
	start_overlay();
	HWND window = FindWindowA(NULL, "ArkAscended");
	GetWindowThreadProcessId(window, &Memory::ProcessID);
	if (Memory::ProcessID == 0) return 0;

	Memory::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::ProcessID);
	Memory::ModuleBaseAddress = FindModuleBaseAddress(Memory::ProcessID, "ArkAscended.exe");
	inits::initialize();

	start_ue5_renderer();

	return 0;
}