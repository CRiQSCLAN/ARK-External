#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui_internal.h"
#include "imgui_settings.h"
#include "imstb_textedit.h"

#include <cstdlib>

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include <map>

#include <string>
#include <wtypes.h>

namespace edited
{
    bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);
    void          EndChild();

    bool          BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags);

    bool          Tab(bool selected, const char* icon, const ImVec2& size_arg);
    bool          SubTab(bool selected, const char* label, const ImVec2& size_arg);
    bool          weapon_preview(bool selected, const char* label, const ImVec2& size_arg);

    void          Separator_line();

    bool          Checkbox( const char* label, bool* v );

    bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);

    bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
    bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
    bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0));

    bool		  Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
    bool		  Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));
                  
    bool		  BeginCombo(const char* label, const char* preview_value, int val = 0, bool multi = false, ImGuiComboFlags flags = 0);
    void		  EndCombo();
    void		  MultiCombo(const char* label, bool variable[], const char* labels[], int count);
    bool		  Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items = -1);
    bool		  Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
    bool		  Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);

    bool          CheckboxPicker(const char* label, bool* v, float col[3], ImGuiColorEditFlags flags = 0);
    bool          CheckboxKeybind(const char* label, bool* v, int* key);

    bool          Keybind(const char* label, int* key, bool show_label = true);
    bool          ThemeButton(const char* id_theme, bool dark, const ImVec2& size_arg);
    bool          Button( const char* label, const ImVec2& size_arg );
}