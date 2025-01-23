#pragma once
#define WIN32_LEAN_AND_MEAN  
#define _CRT_SECURE_NO_WARNINGS_
#define IMGUI_DEFINE_MATH_OPERATORS
#include <Windows.h>
#include <WinUser.h>
#include <tlhelp32.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dwmapi.h>
#include <winioctl.h>
#include <bcrypt.h>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <string>
#include <list>
#include <d3d11.h>
#include <algorithm>
#include <commdlg.h>
#include <ShObjIdl.h>
#include <iomanip>
#include <Pdh.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "pdh.lib")

// START OF FRAMEWORK
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_edited.hpp"
#include "ImGui/imgui_freetype.h"
// END OF FRAMEWORK 

// START OF PROTECTION
#include "lazy.hpp"
// END OF PROTECTION

// START OF COMMUNICATION
#include "Driver/driver.h"
// END OF COMMUNICATION

#include "globals.h"
#include "utils.h"
#include "ark_inits.h"
#include "structs.h"
#include "offsets.h"
#include "SDK.hpp"
#include "UnrealEngine.h"


using namespace std;
using namespace settings;
using namespace settings::visuals;
using namespace settings::other;