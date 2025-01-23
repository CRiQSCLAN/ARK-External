#include "imgui.h"
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")
inline float dpi = 0.7f;
inline int tabs_state = 0, subtab_state = 0, weapon_state = 0;

inline bool dark = true;

namespace font
{
	inline ImFont* lexend_widget = nullptr;
	inline ImFont* weapon_icon = nullptr;
	inline ImFont* icomoon = nullptr;
	inline ImFont* icomoon_x = nullptr;
}

namespace image
{
	inline ID3D11ShaderResourceView* logo = nullptr;
	inline ID3D11ShaderResourceView* male = nullptr;
	inline ID3D11ShaderResourceView* female = nullptr;
}

namespace c
{

	inline ImVec4 accent = ImColor(144, 238, 144); // Soft green accent

	inline ImVec4 color_bg1 = ImColor(15, 15, 15); // Darker background
	inline ImVec4 color_bg2 = ImColor(45, 45, 45); // Slightly lighter dark

	namespace bg
	{
		inline ImVec4 background = ImColor(25, 28, 34); // Dark mode base

		inline ImVec4 weapon_border = ImColor(35, 38, 44); // Slightly lighter dark border
		inline ImVec4 tab_border = ImColor(40, 43, 49); // Subtle contrast border
		inline ImVec4 sub_border = ImColor(37, 40, 46); // Darker border

		inline ImVec2 size = ImVec2(1100, 600);
		inline float rounding = 8.f;
	}

	namespace child
	{
		inline ImVec4 background = ImColor(32, 35, 41); // Dark child background
		inline ImVec4 cap = ImColor(35, 38, 44); // Slightly lighter cap
		inline float rounding = 7.f;
	}

	namespace tab
	{
		inline ImVec4 tab_active = ImColor(42, 45, 51); // Active tab with slight contrast
		inline float rounding = 4.f;
	}

	namespace widget
	{
		inline ImVec4 bg_inactive = ImColor(42, 45, 51); // Inactive widget background
		inline ImVec4 mark = ImColor(20, 20, 20); // Dark mark color for contrast
		inline float rounding = 2.f;
	}

	namespace text
	{
		inline ImVec4 text_active = ImColor(220, 255, 220); // Light greenish white text
		inline ImVec4 text_hov = ImColor(169, 228, 169); // Hover text with soft green tint
		inline ImVec4 text = ImColor(125, 135, 125); // Neutral grayish-green text
	}

}
