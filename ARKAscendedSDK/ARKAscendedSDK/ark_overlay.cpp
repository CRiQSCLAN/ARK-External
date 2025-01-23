#pragma once
#include "includes.hpp"
#include "font.h"

bool UnrealEngine5::render::hijack_overlay() {
	hwnd = FindWindowA(_("Microsoft-Windows-SnipperCaptureForm"), NULL);
	if (!hwnd)
	{
		printf("nmo");
		return false;
	}
	DwmExtendFrameIntoClientArea(hwnd, &margin);

	SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE);
	SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetWindowPos(hwnd, 0, 0, 0, globals::n_width, globals::n_height, 0);
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(hwnd, &margin);
	return true;
}


bool UnrealEngine5::render::init_imgui() {
	ImGui::CreateContext();

	if (!ImGui_ImplWin32_Init(hwnd) || !ImGui_ImplDX11_Init(device, device_context)) {
		return false;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.0f / 60.0f;
	io.IniFilename = NULL;

	ImFontConfig cfg;
	cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

	ImFont* fonts[] = {
		font = io.Fonts->AddFontFromMemoryTTF(burbank_bold, sizeof(burbank_bold), 15, NULL, io.Fonts->GetGlyphRangesCyrillic()),
		font::lexend_widget = io.Fonts->AddFontFromMemoryTTF(lexend_medium, sizeof(lexend_medium), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic()),
		font::weapon_icon = io.Fonts->AddFontFromMemoryTTF(weapon_icon, sizeof(weapon_icon), 23.f, &cfg, io.Fonts->GetGlyphRangesCyrillic()),
		font::icomoon = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 19.f, &cfg, io.Fonts->GetGlyphRangesCyrillic()),
		font::icomoon_x = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 25.f, &cfg, io.Fonts->GetGlyphRangesCyrillic())
	};

	for (ImFont* f : fonts) {
		if (!f) {
			return false;
		}
	}

	D3DX11_IMAGE_LOAD_INFO info;
	ID3DX11ThreadPump* pump{ nullptr };
	if (image::logo == nullptr && D3DX11CreateShaderResourceViewFromMemory(device, logo, sizeof(logo), &info, pump, &image::logo, 0) != S_OK) {
		return false;
	}
	if (image::male == nullptr && D3DX11CreateShaderResourceViewFromMemory(device, male, sizeof(male), &info, pump, &image::male, 0) != S_OK) {
		return false;
	}
	if (image::female == nullptr && D3DX11CreateShaderResourceViewFromMemory(device, female, sizeof(female), &info, pump, &image::female, 0) != S_OK) {
		return false;
	}

	return true;
}

bool UnrealEngine5::render::create_render_target() {
	ID3D11Texture2D* render_buffer{ nullptr };

	auto result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&render_buffer));
	if (FAILED(result)) {
		return false;
	}

	result = device->CreateRenderTargetView(render_buffer, nullptr, &render_target);
	if (FAILED(result)) {
		return false;
	}

	render_buffer->Release();

	return true;
}

bool UnrealEngine5::render::create_swapchain() {
	DXGI_RATIONAL refresh_rate = {};
	refresh_rate.Numerator = 0;
	refresh_rate.Denominator = 1;

	DXGI_MODE_DESC buffer_desc = {};
	buffer_desc.Width = 0;
	buffer_desc.Height = 0;
	buffer_desc.RefreshRate = refresh_rate;
	buffer_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	buffer_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	buffer_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SAMPLE_DESC sample_desc = {};
	sample_desc.Count = 1;
	sample_desc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC swapchain_desc = {};
	swapchain_desc.BufferDesc = buffer_desc;
	swapchain_desc.SampleDesc = sample_desc;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.BufferCount = 2;
	swapchain_desc.OutputWindow = hwnd;
	swapchain_desc.Windowed = TRUE;
	swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL w_feature_level;
	const D3D_FEATURE_LEVEL w_feature_level_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

	HRESULT ret = D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		w_feature_level_array,
		2,
		D3D11_SDK_VERSION,
		&swapchain_desc,
		&swapchain,
		&device,
		&w_feature_level,
		&device_context
	);

	if (FAILED(ret)) {
		return false;
	}

	if (!create_render_target()) {
		return false;
	}

	return true;
}

bool UnrealEngine5::render::initialize_overlay() {
	if (!hijack_overlay()) {
		n_print("failed to hijack window");
		return false;
	}

	if (!create_swapchain()) {
		n_print("failed to initialize swapchain");
		return false;
	}

	if (!init_imgui()) {
		n_print("failed to initialize framework");
		return false;
	}

	return true;
}

void UnrealEngine5::render::handle_inputs() {
	if (show_menu) {
		render_menu();
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		show_menu = !show_menu;
	}

	if (GetAsyncKeyState(VK_F6) & 1) {
		show_render = !show_render;
	}

	if (GetAsyncKeyState(VK_F4) & 1) {
		nsa_import(exit)(0);
	}
}

void UnrealEngine5::render::process_messages() {
	if (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void UnrealEngine5::render::start_scene() {
	ImGui_ImplDX11_NewFrame();
	POINT p;
	GetCursorPos(&p);
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos.x = p.x;
	io.MousePos.y = p.y;

	if (GetAsyncKeyState(VK_LBUTTON)) {
		io.MouseDown[0] = true;
		io.MouseClicked[0] = true;
		io.MouseClickedPos[0].x = io.MousePos.x;
		io.MouseClickedPos[0].x = io.MousePos.y;
	}
	else {
		io.MouseDown[0] = false;
	}

	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void UnrealEngine5::render::end_scene() {
	const float color[]{ 0, 0, 0, 0 };

	ImGui::Render();

	device_context->OMSetRenderTargets(1, &render_target, nullptr);
	device_context->ClearRenderTargetView(render_target, color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapchain->Present(settings::other::vsync, 0); // settings::other::vsync 1 = Cap To VSync / 0 = Cap GPU 100% Power
}

void UnrealEngine5::render::clean_up() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(hwnd);
}

void UnrealEngine5::render::run_render_loop() {
	while (msg.message != WM_QUIT) {
		process_messages();
		//device_t.IO_MOVE_MOUSE(10, 0);

		start_scene();
		{
			render_actors();
			handle_inputs();
		}
		end_scene();
	}

	clean_up();
}

UnrealEngine5::render::render(HMODULE hModule) {
	globals::n_width = GetSystemMetrics(SM_CXSCREEN); globals::n_half_width = globals::n_width / 2;
	globals::n_height = GetSystemMetrics(SM_CYSCREEN); globals::n_half_height = globals::n_height / 2;

	if (!initialize_overlay()) {
		n_print("failed to initialize overlay");
		return;
	}

	return;
}