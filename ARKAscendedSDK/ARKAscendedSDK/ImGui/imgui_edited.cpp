#include "imgui_edited.hpp"

using namespace ImGui;

namespace edited
{
    const char* keys[] =
    {
        "None",
        "Mouse 1",
        "Mouse 2",
        "CN",
        "Mouse 3",
        "Mouse 4",
        "Mouse 5",
        "-",
        "Back",
        "Tab",
        "-",
        "-",
        "CLR",
        "Enter",
        "-",
        "-",
        "Shift",
        "CTL",
        "Menu",
        "Pause",
        "Caps Lock",
        "KAN",
        "-",
        "JUN",
        "FIN",
        "KAN",
        "-",
        "Escape",
        "CON",
        "NCO",
        "ACC",
        "MAD",
        "Space",
        "PGU",
        "PGD",
        "End",
        "Home",
        "Left",
        "Up",
        "Right",
        "Down",
        "SEL",
        "PRI",
        "EXE",
        "PRI",
        "INS",
        "Delete",
        "HEL",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "WIN",
        "WIN",
        "APP",
        "-",
        "SLE",
        "Numpad 0",
        "Numpad 1",
        "Numpad 2",
        "Numpad 3",
        "Numpad 4",
        "Numpad 5",
        "Numpad 6",
        "Numpad 7",
        "Numpad 8",
        "Numpad 9",
        "MUL",
        "ADD",
        "SEP",
        "MIN",
        "Delete",
        "DIV",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "F13",
        "F14",
        "F15",
        "F16",
        "F17",
        "F18",
        "F19",
        "F20",
        "F21",
        "F22",
        "F23",
        "F24",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "NUM",
        "SCR",
        "EQU",
        "MAS",
        "TOY",
        "OYA",
        "OYA",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "Shift",
        "Shift",
        "Ctrl",
        "Ctrl",
        "Alt",
        "Alt"
    };

    bool BeginChild(ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
    {
        return BeginChildEx(NULL, id, size_arg, child_flags, window_flags);
    }

    bool BeginChild(const char* str_id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
    {
        ImGuiID id = GetCurrentWindow()->GetID(str_id);
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20) * dpi);
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20) * dpi);
        return BeginChildEx(str_id, id, size_arg * dpi, child_flags, window_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
    }

    struct child_state
    {
        bool collapsed;
        float size_offset = 0.f;
    };

    bool BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* parent_window = g.CurrentWindow;
        IM_ASSERT(id != 0);

        const ImGuiChildFlags ImGuiChildFlags_SupportedMask_ = ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_FrameStyle;
        IM_UNUSED(ImGuiChildFlags_SupportedMask_);
        IM_ASSERT((child_flags & ~ImGuiChildFlags_SupportedMask_) == 0 && "Illegal ImGuiChildFlags value. Did you pass ImGuiWindowFlags values instead of ImGuiChildFlags?");
        IM_ASSERT((window_flags & ImGuiWindowFlags_AlwaysAutoResize) == 0 && "Cannot specify ImGuiWindowFlags_AlwaysAutoResize for BeginChild(). Use ImGuiChildFlags_AlwaysAutoResize!");
        if (child_flags & ImGuiChildFlags_AlwaysAutoResize)
        {
            IM_ASSERT((child_flags & (ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY)) == 0 && "Cannot use ImGuiChildFlags_ResizeX or ImGuiChildFlags_ResizeY with ImGuiChildFlags_AlwaysAutoResize!");
            IM_ASSERT((child_flags & (ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY)) != 0 && "Must use ImGuiChildFlags_AutoResizeX or ImGuiChildFlags_AutoResizeY with ImGuiChildFlags_AlwaysAutoResize!");
        }
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        if (window_flags & ImGuiWindowFlags_AlwaysUseWindowPadding)
            child_flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
#endif
        if (child_flags & ImGuiChildFlags_AutoResizeX)
            child_flags &= ~ImGuiChildFlags_ResizeX;
        if (child_flags & ImGuiChildFlags_AutoResizeY)
            child_flags &= ~ImGuiChildFlags_ResizeY;

        // Set window flags
        window_flags |= ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoTitleBar;
        window_flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove); // Inherit the NoMove flag
        if (child_flags & (ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize))
            window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
        if ((child_flags & (ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY)) == 0)
            window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

        // Special framed style
        if (child_flags & ImGuiChildFlags_FrameStyle)
        {
            PushStyleColor(ImGuiCol_ChildBg, g.Style.Colors[ImGuiCol_FrameBg]);
            PushStyleVar(ImGuiStyleVar_ChildRounding, g.Style.FrameRounding);
            PushStyleVar(ImGuiStyleVar_ChildBorderSize, g.Style.FrameBorderSize);
            PushStyleVar(ImGuiStyleVar_WindowPadding, g.Style.FramePadding);
            child_flags |= ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysUseWindowPadding;
            window_flags |= ImGuiWindowFlags_NoMove;
        }

        g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasChildFlags;
        g.NextWindowData.ChildFlags = child_flags;

        const ImVec2 size_avail = GetContentRegionAvail();
        const ImVec2 size_default((child_flags & ImGuiChildFlags_AutoResizeX) ? 0.0f : size_avail.x, (child_flags & ImGuiChildFlags_AutoResizeY) ? 0.0f : size_avail.y);
        const ImVec2 size = CalcItemSize(size_arg, size_default.x, size_default.y);

        ImGui::SetCursorPos(GetCursorPos() + ImVec2(0.f, 40.f * dpi));

        static std::map<ImGuiID, child_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, child_state() });
            it_anim = anim.find(id);
        }

        GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos - ImVec2(0, 40 * dpi), parent_window->DC.CursorPos + ImVec2(size_arg.x, 0), GetColorU32(c::child::cap), c::child::rounding * dpi, ImDrawFlags_RoundCornersTop);

        GetWindowDrawList()->AddText(parent_window->DC.CursorPos + (ImVec2(size_arg.x, -40 * dpi) - CalcTextSize(name)) / 2, GetColorU32(c::text::text_active), name);

        const char* temp_window_name;

        if (name)
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
        else
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);


        const bool ret = Begin(temp_window_name, NULL, window_flags);

        if (child_flags & ImGuiChildFlags_FrameStyle)
        {
            PopStyleVar(3);
            PopStyleColor();
        }

        ImGuiWindow* child_window = g.CurrentWindow;
        child_window->ChildId = id;

        bool panel_hovered, panel_clicked = false;

        panel_hovered = g.IO.MousePos.x > parent_window->DC.CursorPos.x + size_arg.x - 50 && g.IO.MousePos.y > parent_window->DC.CursorPos.y - 35 && g.IO.MousePos.x < parent_window->DC.CursorPos.x + size.x && g.IO.MousePos.y < parent_window->DC.CursorPos.y;
        panel_clicked = panel_hovered && g.IO.MouseClicked[0];

        if (panel_clicked) it_anim->second.collapsed = !it_anim->second.collapsed;

        if (child_window->BeginCount == 1) parent_window->DC.CursorPos = child_window->Pos;

        it_anim->second.size_offset = ImLerp(it_anim->second.size_offset, child_window->ContentSize.y > 0 ? child_window->ContentSize.y + 41 * dpi : 1.f, g.IO.DeltaTime * 20.f);

        SetWindowSize(ImVec2(size.x, it_anim->second.size_offset));

        parent_window->DrawList->AddRectFilled(child_window->Pos, child_window->Pos + ImVec2(size_arg.x, it_anim->second.size_offset), GetColorU32(c::child::background), c::child::rounding * dpi, ImDrawFlags_RoundCornersBottom);

        if (child_window->BeginCount == 1) parent_window->DC.CursorPos = child_window->Pos;

        const ImGuiID temp_id_for_activation = ImHashStr("##Child", 0, id);
        if (g.ActiveId == temp_id_for_activation)
            ClearActiveID();
        if (g.NavActivateId == id && !(window_flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavWindowHasScrollY))
        {
            FocusWindow(child_window);
            NavInitWindow(child_window, false);
            SetActiveID(temp_id_for_activation, child_window);
            g.ActiveIdSource = g.NavInputSource;
        }
        return ret;
    }

    void EndChild()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* child_window = g.CurrentWindow;
        PopStyleVar(2);
        IM_ASSERT(g.WithinEndChild == false);
        IM_ASSERT(child_window->Flags & ImGuiWindowFlags_ChildWindow);

        g.WithinEndChild = true;
        ImVec2 child_size = child_window->Size;
        End();
        if (child_window->BeginCount == 1)
        {
            ImGuiWindow* parent_window = g.CurrentWindow;
            ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + child_size);
            ItemSize(child_size);
            if ((child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavWindowHasScrollY) && !(child_window->Flags & ImGuiWindowFlags_NavFlattened))
            {
                ItemAdd(bb, child_window->ChildId);
            }
            else
            {
                ItemAdd(bb, 0);

                if (child_window->Flags & ImGuiWindowFlags_NavFlattened) parent_window->DC.NavLayersActiveMaskNext |= child_window->DC.NavLayersActiveMaskNext;
            }
            if (g.HoveredWindow == child_window)
                g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
        }
        g.WithinEndChild = false;
        g.LogLinePosY = -FLT_MAX;
    }

    struct button_state
    {
        ImVec4 text;
        float alpha;
    };

    bool Tab(bool selected, const char* icon, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(icon);
        const ImVec2 label_size = CalcTextSize(icon, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = CalcItemSize(size_arg, label_size.x, label_size.y);

        const ImRect bb(pos, pos + size * dpi);

        ItemSize(size * dpi, 0.f);
        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, NULL);

        static std::map<ImGuiID, button_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, button_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.alpha = ImLerp(it_anim->second.alpha, selected ? 1.f : hovered ? 0.5f : 0.f, g.IO.DeltaTime * 6.f);

        it_anim->second.text = ImLerp(it_anim->second.text, selected ? c::accent : hovered ? c::text::text_hov : c::text::text , g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(c::tab::tab_active, it_anim->second.alpha), c::tab::rounding * dpi);

        PushFont(font::icomoon);
        GetWindowDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x * dpi - CalcTextSize(icon).x) / 2, bb.Max.y - CalcTextSize(icon).y - (size_arg.y * dpi - CalcTextSize(icon).y) / 2), GetColorU32(it_anim->second.text), icon);
        PopFont();

        return pressed;
    }

    bool SubTab(bool selected, const char* label, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = CalcItemSize(size_arg, 0, 0);

        const ImRect bb(pos, pos + size * dpi);

        ItemSize(size * dpi, 0.f);
        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, NULL);

        static std::map<ImGuiID, button_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, button_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.alpha = ImLerp(it_anim->second.alpha, selected ? 1.f : hovered ? 0.5f : 0.f, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, selected ? c::accent : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(c::tab::tab_active, it_anim->second.alpha), c::tab::rounding * dpi);

        GetWindowDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x * dpi - CalcTextSize(label).x) / 2, bb.Max.y - CalcTextSize(label).y - (size_arg.y * dpi - CalcTextSize(label).y) / 2 + 1), GetColorU32(it_anim->second.text), label);

        return pressed;
    }


    struct weapon_state
    {
        ImVec4 text;
        float alpha;
    };

    bool weapon_preview(bool selected, const char* label, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = CalcItemSize(size_arg, 0, 0);

        const ImRect bb(pos, pos + size * dpi);

        ItemSize(size * dpi, 0.f);
        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, NULL);

        static std::map<ImGuiID, weapon_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, weapon_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.alpha = ImLerp(it_anim->second.alpha, selected ? 1.f : hovered ? 0.5f : 0.f, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, selected ? c::accent : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        PushFont(font::weapon_icon);
        GetWindowDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x * dpi - CalcTextSize(label).x) / 2, bb.Max.y - CalcTextSize(label).y - (size_arg.y * dpi - CalcTextSize(label).y) / 2 + 1), GetColorU32(it_anim->second.text), label);
        PopFont();

        return pressed;
    }

    void Separator_line()
    {
        GetWindowDrawList()->AddRectFilled(GetCursorScreenPos(), GetCursorScreenPos() + ImVec2(GetContentRegionMax().x - GetStyle().WindowPadding.x, 1), GetColorU32(c::widget::bg_inactive));
        Spacing();
    }

    struct check_state
    {
        ImVec4 background, text;
        float alpha_mark;
    };

    bool Checkbox( const char* label, bool* v )
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float square_sz = 20 * dpi, y_size = 20 * dpi;

        const ImVec2 pos = window->DC.CursorPos;

        const float w = GetContentRegionMax().x - style.WindowPadding.x;

        const ImRect total_bb(pos + ImVec2(0, 0), pos + ImVec2(w, y_size));
        ItemSize(total_bb, 0.f);

        if (!ItemAdd(total_bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(total_bb, id, &hovered, &held);

        static std::map<ImGuiID, check_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, check_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.background = ImLerp(it_anim->second.background, *v ? c::accent : c::widget::bg_inactive, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, *v ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        it_anim->second.alpha_mark = ImLerp(it_anim->second.alpha_mark, *v ? 1.f : 0.f, g.IO.DeltaTime * 6.f);

        if (IsItemClicked()) {
            *v = !(*v);
            MarkItemEdited(id);
        }

        const ImRect check_bb(pos + ImVec2(w - square_sz, (y_size - square_sz) / 2), pos + ImVec2(w, (y_size + square_sz) / 2));

        GetWindowDrawList()->AddRectFilled(check_bb.Min, check_bb.Max, GetColorU32(it_anim->second.background), c::widget::rounding * dpi);

        RenderCheckMark(GetWindowDrawList(), check_bb.Min + ImVec2(square_sz / 2, square_sz / 2) / 2, GetColorU32(c::widget::mark, it_anim->second.alpha_mark), square_sz / 2);

        GetWindowDrawList()->AddText(pos + ImVec2(0, (y_size - CalcTextSize(label).y) / 2), GetColorU32(it_anim->second.text), label);

        return pressed;
    }

    bool CheckboxPicker(const char* label, bool* v, float col[3], ImGuiColorEditFlags flags)
    {
        std::string label_picker = "picker", label_checkbox = label + label_picker;

        SetCursorPos(GetCursorPos() - ImVec2(40 * dpi, 0));

        edited::ColorEdit4(label_checkbox.c_str(), col, flags | ImGuiColorEditFlags_NoLabel);

        SetCursorPos(GetCursorPos() - ImVec2(0, 40 * dpi));

        edited::Checkbox(label, v);

    }

    bool CheckboxKeybind(const char* label, bool* v, int* key)
    {
        std::string label_keybind = "keybind", label_checkbox = label + label_keybind;

        SetCursorPos(GetCursorPos() - ImVec2(40 * dpi, 0));

        edited::Keybind(label_checkbox.c_str(), key, false);

        SetCursorPos(GetCursorPos() - ImVec2(0, 40 * dpi));

        edited::Checkbox(label, v);

    }
    struct slider_state
    {
        ImVec4 text, circle;
        float slow, hint_opticaly, hint_alpha, circle_pump;
    };

    bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = GetContentRegionMax().x - style.WindowPadding.x;
        const float y_size = 20 * dpi;
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        char value_buf[64];
        const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

        const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, y_size));
        const ImRect slider_bb(window->DC.CursorPos + ImVec2((w / 1.8f), (y_size / 2) - 1), window->DC.CursorPos + ImVec2(w, (y_size / 2) + 1));
        const ImRect slider_active(window->DC.CursorPos + ImVec2((w / 1.8f), 0), window->DC.CursorPos + ImVec2(w, y_size));

        const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x, 0));

        const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;

        ItemSize(ImRect(total_bb.Min, total_bb.Max));

        if (!ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0)) return false;

        if (format == NULL) format = DataTypeGetInfo(data_type)->PrintFmt;

        bool hovered = ItemHoverable(slider_active, id, g.LastItemData.InFlags), held, pressed = ButtonBehavior(slider_active, id, &hovered, &held, NULL);
        bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);

        if (temp_input_is_active)
        {
            const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
            return TempInputScalar(frame_bb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
        }

        static std::map<ImGuiID, slider_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, slider_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.hint_opticaly = ImLerp(it_anim->second.hint_opticaly, hovered ? 0.3f : 0.0f, g.IO.DeltaTime * 6.f);
        it_anim->second.hint_alpha = ImLerp(it_anim->second.hint_alpha, hovered || IsItemActive() ? 1.f : 0.f, g.IO.DeltaTime * 6.f);
        it_anim->second.circle_pump = ImLerp(it_anim->second.circle_pump, hovered || IsItemActive() ? 7.f * dpi : 5.f * dpi, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, IsItemActive() ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(slider_bb.Min + ImVec2(0, 0), slider_bb.Max + ImVec2(0, 1), GetColorU32(c::widget::bg_inactive), 30.f);

        POINT p;
        ImRect grab_bb;

        const bool value_changed = SliderBehavior(ImRect(slider_bb.Min + ImVec2(0, 0), slider_bb.Max + ImVec2(7, 0)), id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
        if (value_changed) MarkItemEdited(id);

        if (grab_bb.Max.x > grab_bb.Min.x) {

            it_anim->second.slow = ImLerp(it_anim->second.slow, grab_bb.Min.x - frame_bb.Min.x, g.IO.DeltaTime * 25.f);

            PushClipRect(slider_bb.Min - ImVec2(0, 5), slider_bb.Max + ImVec2(0, 5), true);
            GetWindowDrawList()->AddRectFilled(slider_bb.Min + ImVec2(0, 1), ImVec2(it_anim->second.slow + frame_bb.Min.x - 3 * dpi - it_anim->second.circle_pump, grab_bb.Max.y + 1), GetColorU32(c::accent), 30.f);
            PopClipRect();

            GetWindowDrawList()->AddCircleFilled(ImVec2(frame_bb.Min.x + it_anim->second.slow + 2, grab_bb.Max.y + 1), it_anim->second.circle_pump, GetColorU32(c::accent), 30.f);
            GetWindowDrawList()->AddCircleFilled(ImVec2(frame_bb.Min.x + it_anim->second.slow + 2, grab_bb.Max.y + 1), it_anim->second.circle_pump * 2, GetColorU32(c::accent, 0.1f), 30.f);

        }


        GetWindowDrawList()->AddText(ImVec2(frame_bb.Max.x - (w / 2.2f) - (CalcTextSize(value_buf).x + 15), frame_bb.Max.y - ((y_size + CalcTextSize(value_buf).y) / 2)), GetColorU32(c::text::text_active), value_buf);

        GetWindowDrawList()->AddText(ImVec2(frame_bb.Max.x - w, frame_bb.Max.y - ((y_size + CalcTextSize(label).y) / 2)), GetColorU32(it_anim->second.text), label);

        return value_changed;
    }

    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
    }

    bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
    }

    static void ColorEditRestoreH(const float* col, float* H)
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.ColorEditCurrentID != 0);
        if (g.ColorEditSavedID != g.ColorEditCurrentID || g.ColorEditSavedColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0)))
            return;
        *H = g.ColorEditSavedHue;
    }

    static void ColorEditRestoreHS(const float* col, float* H, float* S, float* V)
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.ColorEditCurrentID != 0);
        if (g.ColorEditSavedID != g.ColorEditCurrentID || g.ColorEditSavedColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0))) return;

        if (*S == 0.0f || (*H == 0.0f && g.ColorEditSavedHue == 1))
            *H = g.ColorEditSavedHue;

        if (*V == 0.0f) *S = g.ColorEditSavedSat;
    }

    struct edit_state
    {
        float alpha = 0.f;
        bool hovered, active;
    };

    bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const float square_sz = GetFrameHeight();
        const float w_full = CalcItemWidth();
        const float w_button = (flags & ImGuiColorEditFlags_NoSmallPreview) ? 0.0f : (square_sz + style.ItemInnerSpacing.x);
        const float w_inputs = w_full - w_button;
        const char* label_display_end = FindRenderedTextEnd(label);
        g.NextItemData.ClearFlags();

        BeginGroup();
        PushID(label);
        const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
        if (set_current_color_edit_id)
            g.ColorEditCurrentID = window->IDStack.back();

        // If we're not showing any slider there's no point in doing any HSV conversions
        const ImGuiColorEditFlags flags_untouched = flags;
        if (flags & ImGuiColorEditFlags_NoInputs)
            flags = (flags & (~ImGuiColorEditFlags_DisplayMask_)) | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoOptions;

        // Context menu: display and modify options (before defaults are applied)
        if (!(flags & ImGuiColorEditFlags_NoOptions))
            ColorEditOptionsPopup(col, flags);

        // Read stored options
        if (!(flags & ImGuiColorEditFlags_DisplayMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DisplayMask_);
        if (!(flags & ImGuiColorEditFlags_DataTypeMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DataTypeMask_);
        if (!(flags & ImGuiColorEditFlags_PickerMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_);
        if (!(flags & ImGuiColorEditFlags_InputMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_InputMask_);
        flags |= (g.ColorEditOptions & ~(ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_DisplayMask_)); // Check that only 1 is selected
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));   // Check that only 1 is selected

        const bool alpha = (flags & ImGuiColorEditFlags_NoAlpha) == 0;
        const bool hdr = (flags & ImGuiColorEditFlags_HDR) != 0;
        const int components = alpha ? 4 : 3;

        // Convert to the formats we need
        float f[4] = { col[0], col[1], col[2], alpha ? col[3] : 1.0f };
        if ((flags & ImGuiColorEditFlags_InputHSV) && (flags & ImGuiColorEditFlags_DisplayRGB))
            ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
        else if ((flags & ImGuiColorEditFlags_InputRGB) && (flags & ImGuiColorEditFlags_DisplayHSV))
        {
            // Hue is lost when converting from grayscale rgb (saturation=0). Restore it.
            ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);
            ColorEditRestoreHS(col, &f[0], &f[1], &f[2]);
        }
        int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

        bool value_changed = false;
        bool value_changed_as_float = false;

        const ImVec2 pos = window->DC.CursorPos;
        const float inputs_offset_x = (style.ColorButtonPosition == ImGuiDir_Left) ? w_button : 0.0f;
        window->DC.CursorPos.x = pos.x + inputs_offset_x;

        if ((flags & (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV)) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
        {
            // RGB/HSV 0..255 Sliders
            const float w_item_one = ImMax(1.0f, IM_FLOOR((w_inputs - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
            const float w_item_last = ImMax(1.0f, IM_FLOOR(w_inputs - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));

            const bool hide_prefix = (w_item_one <= CalcTextSize((flags & ImGuiColorEditFlags_Float) ? "M:0.000" : "M:000").x);
            static const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
            static const char* fmt_table_int[3][4] =
            {
                {   "%3d",   "%3d",   "%3d",   "%3d" }, // Short display
                { "R:%3d", "G:%3d", "B:%3d", "A:%3d" }, // Long display for RGBA
                { "H:%3d", "S:%3d", "V:%3d", "A:%3d" }  // Long display for HSVA
            };
            static const char* fmt_table_float[3][4] =
            {
                {   "%0.3f",   "%0.3f",   "%0.3f",   "%0.3f" }, // Short display
                { "R:%0.3f", "G:%0.3f", "B:%0.3f", "A:%0.3f" }, // Long display for RGBA
                { "H:%0.3f", "S:%0.3f", "V:%0.3f", "A:%0.3f" }  // Long display for HSVA
            };
            const int fmt_idx = hide_prefix ? 0 : (flags & ImGuiColorEditFlags_DisplayHSV) ? 2 : 1;

            for (int n = 0; n < components; n++)
            {
                if (n > 0)
                    SameLine(0, style.ItemInnerSpacing.x);
                SetNextItemWidth((n + 1 < components) ? w_item_one : w_item_last);

                // FIXME: When ImGuiColorEditFlags_HDR flag is passed HS values snap in weird ways when SV values go below 0.
                if (flags & ImGuiColorEditFlags_Float)
                {
                    value_changed |= DragFloat(ids[n], &f[n], 1.0f / 255.0f, 0.0f, hdr ? 0.0f : 1.0f, fmt_table_float[fmt_idx][n]);
                    value_changed_as_float |= value_changed;
                }
                else
                {
                    value_changed |= DragInt(ids[n], &i[n], 1.0f, 0, hdr ? 0 : 255, fmt_table_int[fmt_idx][n]);
                }
                if (!(flags & ImGuiColorEditFlags_NoOptions))
                    OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
            }
        }

        ImGuiWindow* picker_active_window = NULL;
        if (!(flags & ImGuiColorEditFlags_NoSmallPreview))
        {
            const float button_offset_x = ((flags & ImGuiColorEditFlags_NoInputs) || (style.ColorButtonPosition == ImGuiDir_Left)) ? 0.0f : w_inputs + style.ItemInnerSpacing.x;
            window->DC.CursorPos = ImVec2(pos.x + button_offset_x, pos.y);

            const ImVec4 col_v4(col[0], col[1], col[2], alpha ? col[3] : 1.0f);
            if (ColorButton("##ColorButton", col_v4, flags, ImVec2(20, 20)))
            {
                if (!(flags & ImGuiColorEditFlags_NoPicker))
                {
                    // Store current color and open a picker
                    g.ColorPickerRef = col_v4;
                    OpenPopup("picker");
                    SetNextWindowPos(g.LastItemData.Rect.GetBL() + ImVec2(0.0f, style.ItemSpacing.y));
                }
            }
            if (!(flags & ImGuiColorEditFlags_NoOptions))
                OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

            static std::map<ImGuiID, edit_state> anim;
            auto it_anim = anim.find(ImGui::GetID(label));

            if (it_anim == anim.end())
            {
                anim.insert({ ImGui::GetID(label), edit_state() });
                it_anim = anim.find(ImGui::GetID(label));
            }

            if (ItemHoverable(g.LastItemData.Rect, g.LastItemData.ID, NULL) && g.IO.MouseClicked[0] || it_anim->second.active && g.IO.MouseClicked[0] && !it_anim->second.hovered)
                it_anim->second.active = !it_anim->second.active;

            it_anim->second.alpha = ImClamp(it_anim->second.alpha + (8.f * g.IO.DeltaTime * (it_anim->second.active ? 1.f : -1.f)), 0.f, 1.f);

            PushStyleColor(ImGuiCol_WindowBg, GetColorU32(c::widget::bg_inactive));
            PushStyleVar(ImGuiStyleVar_WindowRounding, c::widget::rounding);
            PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15 * dpi, 15 * dpi));
            PushStyleVar(ImGuiStyleVar_Alpha, it_anim->second.alpha);

            if (it_anim->second.alpha >= 0.01f)
            {
                SetNextWindowPos(g.LastItemData.Rect.GetTR() + ImVec2(-25 * dpi, -5 * dpi));

                Begin("picker", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
                {
                    it_anim->second.hovered = IsWindowHovered();

                    char buf[64];

                    ImVec4 col_v4(col[0], col[1], col[2], (flags & ImGuiColorEditFlags_NoAlpha) ? 1.0f : col[3]);

                    int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };
                    ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255));

                    if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel))
                    ImGui::GetWindowDrawList()->AddText(GetCursorScreenPos() + ImVec2(0, 0), GetColorU32(c::text::text_active), label);
                    else
                    ImGui::GetWindowDrawList()->AddText(GetCursorScreenPos() + ImVec2(0, 0), GetColorU32(c::text::text_active), "Color picker");

                    ImGui::GetWindowDrawList()->AddText(GetCursorScreenPos() + ImVec2(GetContentRegionMax().x - (CalcTextSize(buf).x + 15 * dpi), 0), GetColorU32(c::text::text_active), buf);

                    ImGui::SetCursorPosY(GetCursorPosY() + 33 * dpi);

                    picker_active_window = g.CurrentWindow;
                    ImGuiColorEditFlags picker_flags_to_forward = ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar;
                    ImGuiColorEditFlags picker_flags = (flags_untouched & picker_flags_to_forward) | ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf;
                    SetNextItemWidth(square_sz * 10.0f); // Use 256 + bar sizes?

                    value_changed |= ColorPicker4("##picker", col, picker_flags, &g.ColorPickerRef.x);
                }
                End();
            }
        }
        PopStyleColor(1);
        PopStyleVar(3);

        if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel))
        {
            char buf[64];

            SameLine(0.0f, style.ItemInnerSpacing.x);
            window->DC.CursorPos.x = pos.x - w_button + ((flags & ImGuiColorEditFlags_NoInputs) ? w_button : w_full);

            ImGui::GetWindowDrawList()->AddText(window->DC.CursorPos + ImVec2(0, 0), GetColorU32(c::text::text), label);

        }

        // Convert back
        if (value_changed && picker_active_window == NULL)
        {
            if (!value_changed_as_float)
                for (int n = 0; n < 4; n++)
                    f[n] = i[n] / 255.0f;
            if ((flags & ImGuiColorEditFlags_DisplayHSV) && (flags & ImGuiColorEditFlags_InputRGB))
            {
                g.ColorEditSavedHue = f[0];
                g.ColorEditSavedSat = f[1];
                ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
                g.ColorEditSavedID = g.ColorEditCurrentID;
                g.ColorEditSavedColor = ColorConvertFloat4ToU32(ImVec4(f[0], f[1], f[2], 0));
            }
            if ((flags & ImGuiColorEditFlags_DisplayRGB) && (flags & ImGuiColorEditFlags_InputHSV))
                ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);

            col[0] = f[0];
            col[1] = f[1];
            col[2] = f[2];
            if (alpha)
                col[3] = f[3];
        }

        if (set_current_color_edit_id)
            g.ColorEditCurrentID = 0;
        PopID();
        EndGroup();

        // Drag and Drop Target
        // NB: The flag test is merely an optional micro-optimization, BeginDragDropTarget() does the same test.
        if ((g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect) && !(flags & ImGuiColorEditFlags_NoDragDrop) && BeginDragDropTarget())
        {
            bool accepted_drag_drop = false;
            if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
            {
                memcpy((float*)col, payload->Data, sizeof(float) * 3); // Preserve alpha if any //-V512 //-V1086
                value_changed = accepted_drag_drop = true;
            }
            if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
            {
                memcpy((float*)col, payload->Data, sizeof(float) * components);
                value_changed = accepted_drag_drop = true;
            }

            // Drag-drop payloads are always RGB
            if (accepted_drag_drop && (flags & ImGuiColorEditFlags_InputHSV))
                ColorConvertRGBtoHSV(col[0], col[1], col[2], col[0], col[1], col[2]);
            EndDragDropTarget();
        }

        // When picker is being actively used, use its active id so IsItemActive() will function on ColorEdit4().
        if (picker_active_window && g.ActiveId != 0 && g.ActiveIdWindow == picker_active_window)
            g.LastItemData.ID = g.ActiveId;

        if (value_changed && g.LastItemData.ID != 0) // In case of ID collision, the second EndGroup() won't catch g.ActiveId
            MarkItemEdited(g.LastItemData.ID);

        return value_changed;
    }

    // Helper for ColorPicker4()
    static void RenderArrowsForVerticalBar(ImDrawList* draw_list, ImVec2 pos, ImVec2 half_sz, float bar_w, float alpha)
    {
        ImU32 alpha8 = IM_F32_TO_INT8_SAT(alpha);
        ImGui::RenderArrowPointingAt(draw_list, ImVec2(pos.x + half_sz.x + 1, pos.y), ImVec2(half_sz.x + 2, half_sz.y + 1), ImGuiDir_Right, IM_COL32(0, 0, 0, alpha8));
        ImGui::RenderArrowPointingAt(draw_list, ImVec2(pos.x + half_sz.x, pos.y), half_sz, ImGuiDir_Right, IM_COL32(255, 255, 255, alpha8));
        ImGui::RenderArrowPointingAt(draw_list, ImVec2(pos.x + bar_w - half_sz.x - 1, pos.y), ImVec2(half_sz.x + 2, half_sz.y + 1), ImGuiDir_Left, IM_COL32(0, 0, 0, alpha8));
        ImGui::RenderArrowPointingAt(draw_list, ImVec2(pos.x + bar_w - half_sz.x, pos.y), half_sz, ImGuiDir_Left, IM_COL32(255, 255, 255, alpha8));
    }

    struct picker_state
    {
        float hue_bar;
        float alpha_bar;
        float circle;
        ImVec2 circle_move;
    };

    bool ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags, const float* ref_col)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImDrawList* draw_list = window->DrawList;
        ImGuiStyle& style = g.Style;
        ImGuiIO& io = g.IO;

        const float width = CalcItemWidth();
        g.NextItemData.ClearFlags();

        PushID(label);
        const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
        if (set_current_color_edit_id)
            g.ColorEditCurrentID = window->IDStack.back();
        BeginGroup();

        if (!(flags & ImGuiColorEditFlags_NoSidePreview)) flags |= ImGuiColorEditFlags_NoSmallPreview;

        if (!(flags & ImGuiColorEditFlags_NoOptions)) ColorPickerOptionsPopup(col, flags);

        if (!(flags & ImGuiColorEditFlags_PickerMask_)) flags |= ((g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_) ? g.ColorEditOptions : ImGuiColorEditFlags_DefaultOptions_) & ImGuiColorEditFlags_PickerMask_;
        if (!(flags & ImGuiColorEditFlags_InputMask_)) flags |= ((g.ColorEditOptions & ImGuiColorEditFlags_InputMask_) ? g.ColorEditOptions : ImGuiColorEditFlags_DefaultOptions_) & ImGuiColorEditFlags_InputMask_;
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_PickerMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_)); 
        if (!(flags & ImGuiColorEditFlags_NoOptions)) flags |= (g.ColorEditOptions & ImGuiColorEditFlags_AlphaBar);

        int components = (flags & ImGuiColorEditFlags_NoAlpha) ? 3 : 4;
        bool alpha_bar = (flags & ImGuiColorEditFlags_AlphaBar) && !(flags & ImGuiColorEditFlags_NoAlpha);
        ImVec2 picker_pos = window->DC.CursorPos;
        float square_sz = GetFrameHeight();
        float bars_width = 15.f * dpi;
        float sv_picker_size = ImMax(bars_width * 1, width - (alpha_bar ? 2 : 1) * (bars_width)); 
        float bar0_pos_x = picker_pos.x + sv_picker_size + 10 * dpi;
        float bar1_pos_x = bar0_pos_x + bars_width + 10 * dpi;
        float bars_triangles_half_sz = IM_TRUNC(bars_width * 0.20f);

        float backup_initial_col[4];
        memcpy(backup_initial_col, col, components * sizeof(float));

        float H = col[0], S = col[1], V = col[2];
        float R = col[0], G = col[1], B = col[2];
        if (flags & ImGuiColorEditFlags_InputRGB)
        {
            ColorConvertRGBtoHSV(R, G, B, H, S, V);
            ColorEditRestoreHS(col, &H, &S, &V);
        }
        else if (flags & ImGuiColorEditFlags_InputHSV)
        {
            ColorConvertHSVtoRGB(H, S, V, R, G, B);
        }

        bool value_changed = false, value_changed_h = false, value_changed_sv = false;

            InvisibleButton("sv", ImVec2(sv_picker_size, sv_picker_size));
            if (IsItemActive())
            {
                S = ImSaturate((io.MousePos.x - picker_pos.x) / (sv_picker_size - 1));
                V = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
                ColorEditRestoreH(col, &H);
                value_changed = value_changed_sv = true;
            }
            if (!(flags & ImGuiColorEditFlags_NoOptions)) OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

            SetCursorScreenPos(ImVec2(bar0_pos_x, picker_pos.y));
            InvisibleButton("hue", ImVec2(bars_width, sv_picker_size));
            if (IsItemActive())
            {
                H = ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
                value_changed = value_changed_h = true;
            }

        if (alpha_bar)
        {
            SetCursorScreenPos(ImVec2(bar1_pos_x, picker_pos.y));
            InvisibleButton("alpha", ImVec2(bars_width, sv_picker_size));
            if (IsItemActive())
            {
                col[3] = 1.0f - ImSaturate((io.MousePos.y - picker_pos.y) / (sv_picker_size - 1));
                value_changed = true;
            }
        }

        PopItemFlag();

        if (!(flags & ImGuiColorEditFlags_NoLabel))
        {
            const char* label_display_end = FindRenderedTextEnd(label);
            if (label != label_display_end)
            {
                if ((flags & ImGuiColorEditFlags_NoSidePreview))
                    SameLine(0, style.ItemInnerSpacing.x);
                TextEx(label, label_display_end);
            }
        }

        if (value_changed_h || value_changed_sv)
        {
            if (flags & ImGuiColorEditFlags_InputRGB)
            {
                ColorConvertHSVtoRGB(H, S, V, col[0], col[1], col[2]);
                g.ColorEditSavedHue = H;
                g.ColorEditSavedSat = S;
                g.ColorEditSavedID = g.ColorEditCurrentID;
                g.ColorEditSavedColor = ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0));
            }
            else if (flags & ImGuiColorEditFlags_InputHSV)
            {
                col[0] = H;
                col[1] = S;
                col[2] = V;
            }
        }

        if (value_changed)
        {
            if (flags & ImGuiColorEditFlags_InputRGB)
            {
                R = col[0];
                G = col[1];
                B = col[2];
                ColorConvertRGBtoHSV(R, G, B, H, S, V);
                ColorEditRestoreHS(col, &H, &S, &V);
            }
            else if (flags & ImGuiColorEditFlags_InputHSV)
            {
                H = col[0];
                S = col[1];
                V = col[2];
                ColorConvertHSVtoRGB(H, S, V, R, G, B);
            }
        }

        const int style_alpha8 = IM_F32_TO_INT8_SAT(style.Alpha);
        const ImU32 col_black = IM_COL32(0, 0, 0, style_alpha8);
        const ImU32 col_white = IM_COL32(255, 255, 255, style_alpha8);
        const ImU32 col_midgrey = IM_COL32(128, 128, 128, style_alpha8);
        const ImU32 col_hues[6 + 1] = { IM_COL32(255,0,0,style_alpha8), IM_COL32(255,255,0,style_alpha8), IM_COL32(0,255,0,style_alpha8), IM_COL32(0,255,255,style_alpha8), IM_COL32(0,0,255,style_alpha8), IM_COL32(255,0,255,style_alpha8), IM_COL32(255,0,0,style_alpha8) };

        ImVec4 hue_color_f(1, 1, 1, style.Alpha); ColorConvertHSVtoRGB(H, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z);
        ImU32 hue_color32 = ColorConvertFloat4ToU32(hue_color_f);
        ImU32 user_col32_striped_of_alpha = ColorConvertFloat4ToU32(ImVec4(R, G, B, style.Alpha)); 

        static std::map<ImGuiID, picker_state> anim;
        auto it_anim = anim.find(ImGui::GetID(label));

        if (it_anim == anim.end())
        {
            anim.insert({ ImGui::GetID(label), picker_state() });
            it_anim = anim.find(ImGui::GetID(label));
        }

        ImVec2 sv_cursor_pos;

            draw_list->AddRectFilledMultiColor(picker_pos, picker_pos + ImVec2(sv_picker_size, sv_picker_size), col_white, hue_color32, hue_color32, col_white, 5.f * dpi);
            draw_list->AddRectFilledMultiColor(picker_pos - ImVec2(1, 1), picker_pos + ImVec2(sv_picker_size + 1, sv_picker_size + 1), 0, 0, col_black, col_black, 5.f * dpi);

            sv_cursor_pos.x = ImClamp(IM_ROUND(picker_pos.x + ImSaturate(S) * sv_picker_size), picker_pos.x + 2, picker_pos.x + sv_picker_size - 2); // Sneakily prevent the circle to stick out too much
            sv_cursor_pos.y = ImClamp(IM_ROUND(picker_pos.y + ImSaturate(1 - V) * sv_picker_size), picker_pos.y + 2, picker_pos.y + sv_picker_size - 2);

            for (int i = 0; i < 6; ++i)
            draw_list->AddRectFilledMultiColor(ImVec2(bar0_pos_x, picker_pos.y + i * (sv_picker_size / 6) - (i == 5 ? 1 : 0)), ImVec2(bar0_pos_x + bars_width, picker_pos.y + (i + 1) * (sv_picker_size / 6) + (i == 0 ? 1 : 0)), col_hues[i], col_hues[i], col_hues[i + 1], col_hues[i + 1], 10.f * dpi, i == 0 ? ImDrawFlags_RoundCornersTop : i == 5 ? ImDrawFlags_RoundCornersBottom : ImDrawFlags_RoundCornersNone);

            float bar0_line_y = IM_ROUND(picker_pos.y + H * sv_picker_size);
            bar0_line_y = ImClamp(bar0_line_y, picker_pos.y + 3.f * dpi, picker_pos.y + (sv_picker_size - 13 * dpi) );

            it_anim->second.hue_bar = ImLerp(it_anim->second.hue_bar, bar0_line_y + 5 * dpi, g.IO.DeltaTime * 24.f);
            draw_list->AddCircleFilled(ImVec2(bar0_pos_x + 7.5f * dpi, it_anim->second.hue_bar), 4.5f * dpi, col_black, 100.f);

        float sv_cursor_rad = value_changed_sv ? 10.0f : 6.0f;
        int sv_cursor_segments = draw_list->_CalcCircleAutoSegmentCount(sv_cursor_rad);

        it_anim->second.circle_move = ImLerp(it_anim->second.circle_move, sv_cursor_pos, g.IO.DeltaTime * 24.f);
        it_anim->second.circle = ImLerp(it_anim->second.circle, value_changed_sv ? 6.0f : 4.0f, g.IO.DeltaTime * 24.f);

        draw_list->AddCircle(it_anim->second.circle_move, it_anim->second.circle * dpi, col_white, sv_cursor_segments, 2.f);

        if (alpha_bar)
        {
            float alpha = ImSaturate(col[3]);
            ImRect bar1_bb(bar1_pos_x, picker_pos.y, bar1_pos_x + bars_width, picker_pos.y + sv_picker_size);

            RenderColorRectWithAlphaCheckerboard(draw_list, bar1_bb.Min, bar1_bb.Max, 0, bar1_bb.GetWidth() / 3.0f, ImVec2(0.0f, 0.0f), 100.f * dpi);
            draw_list->AddRectFilledMultiColor(bar1_bb.Min, bar1_bb.Max, user_col32_striped_of_alpha, user_col32_striped_of_alpha, user_col32_striped_of_alpha & ~IM_COL32_A_MASK, user_col32_striped_of_alpha & ~IM_COL32_A_MASK, 100.f * dpi);

            float bar1_line_y = IM_ROUND(picker_pos.y + (1.0f - alpha) * sv_picker_size);
            bar1_line_y = ImClamp(bar1_line_y, picker_pos.y + 3.f * dpi, picker_pos.y + (sv_picker_size - 13 * dpi));

            it_anim->second.alpha_bar = ImLerp(it_anim->second.alpha_bar, bar1_line_y + 5 * dpi, g.IO.DeltaTime * 24.f);
            draw_list->AddCircleFilled(ImVec2(bar1_pos_x + 7.5f * dpi, it_anim->second.alpha_bar), 4.5f * dpi, col_black, 100.f);

        }

        EndGroup();

        if (value_changed && memcmp(backup_initial_col, col, components * sizeof(float)) == 0) value_changed = false;
        if (value_changed) MarkItemEdited(g.LastItemData.ID);

        PopID();

        return value_changed;
    }


    bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiID id = window->GetID(desc_id);
        const float default_size = GetFrameHeight();
        const ImVec2 pos = window->DC.CursorPos;
        const float width = GetContentRegionMax().x - ImGui::GetStyle().WindowPadding.x;
        const ImRect rect(pos, pos + ImVec2(width, 20 * dpi));

        const ImRect clickable(rect.Min + ImVec2(width - 20 * dpi, 0), rect.Max);

        ItemSize(ImRect(rect.Min, rect.Max - ImVec2(0, 0)));
        if (!ItemAdd((flags & ImGuiColorEditFlags_NoLabel) ? clickable : rect, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(clickable, id, &hovered, &held);

        if (flags & ImGuiColorEditFlags_NoAlpha) flags &= ~(ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaPreviewHalf);

        ImVec4 col_rgb = col;
        if (flags & ImGuiColorEditFlags_InputHSV) ColorConvertHSVtoRGB(col_rgb.x, col_rgb.y, col_rgb.z, col_rgb.x, col_rgb.y, col_rgb.z);

        GetWindowDrawList()->AddRectFilled(clickable.Min, clickable.Max, GetColorU32(col_rgb), c::widget::rounding * dpi);

        RenderColorRectWithAlphaCheckerboard(window->DrawList, clickable.Min, clickable.Max, GetColorU32(col_rgb), ImMin(30 * dpi, 30 * dpi) / 2.99f, ImVec2(0.f, 0.f), c::widget::rounding * dpi);

        return pressed;
    }

    struct key_state
    {
        ImVec4 background, text;
        bool active = false;
        bool hovered = false;
        float alpha = 0.f;
    };

    bool Keybind(const char* label, int* key, bool show_label)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        ImGuiIO& io = g.IO;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const float w = (GetContentRegionMax().x - style.WindowPadding.x);

        const ImRect rect(window->DC.CursorPos + ImVec2(0, 0), window->DC.CursorPos + ImVec2(w, 20.f * dpi));

        char buf_display[64] = "None";
        const ImVec2 label_size = CalcTextSize(buf_display, NULL, true);
        ImRect clickable(ImVec2(rect.Max.x - 15 * dpi - label_size.x, rect.Min.y - 5 * dpi), rect.Max + ImVec2(0, 5 * dpi));

        ItemSize(ImRect(rect.Min, rect.Max + ImVec2(0, 0)));

        if (!ImGui::ItemAdd(show_label ? rect : clickable, id)) return false;

        bool value_changed = false;
        int k = *key;

        std::string active_key = "";
        active_key += keys[*key];

        if (*key != 0 && g.ActiveId != id) {
            strcpy_s(buf_display, active_key.c_str());
        }
        else if (g.ActiveId == id) {
            strcpy_s(buf_display, "...");
        }

        bool hovered = ItemHoverable(show_label ? rect : clickable, id, NULL);

        static std::map<ImGuiID, key_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, key_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, g.ActiveId == id ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);
        
        if (show_label)
        window->DrawList->AddText(rect.Min + ImVec2(0, 3 * dpi), GetColorU32(it_anim->second.text), label);

        PushStyleColor(ImGuiCol_Text, c::text::text);

        PushFont(font::icomoon_x);
        RenderTextClipped(clickable.Min, clickable.Max, "o", NULL, NULL, ImVec2(1.0, 0.5f));
        PopFont();

        PopStyleColor();

        if (ItemHoverable(g.LastItemData.Rect, g.LastItemData.ID, NULL) && g.IO.MouseClicked[0] || it_anim->second.active && g.ActiveId != id && !it_anim->second.hovered) it_anim->second.active = !it_anim->second.active;
        it_anim->second.alpha = ImLerp(it_anim->second.alpha, it_anim->second.active ? 1.f : 0.f, g.IO.DeltaTime * 6.f);

        PushStyleColor(ImGuiCol_WindowBg, GetColorU32(c::widget::bg_inactive));
        PushStyleVar(ImGuiStyleVar_WindowRounding, c::widget::rounding * dpi);
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15 * dpi, 15 * dpi));
        PushStyleVar(ImGuiStyleVar_Alpha, it_anim->second.alpha);

        if (it_anim->second.alpha >= 0.01f)
        {
            SetNextWindowPos(ImVec2(clickable.Max.x - 141 * dpi, clickable.Max.y - 31 * dpi));
            SetNextWindowSize(ImVec2(150, 30) * dpi);
            Begin("keybind", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
            {
                it_anim->second.hovered = IsWindowHovered();

                GetWindowDrawList()->AddText(GetCursorScreenPos() - ImVec2(5, 8) * dpi, GetColorU32(c::accent), buf_display);

                GetWindowDrawList()->AddText(font::icomoon_x, 25 * dpi, GetCursorScreenPos() + ImVec2(101, -12) * dpi, GetColorU32(c::accent), "o");

            }
            End();
        }
        PopStyleColor(1);
        PopStyleVar(3);

        if (hovered && io.MouseClicked[0])
        {
            if (g.ActiveId != id) {
                memset(io.MouseDown, 0, sizeof(io.MouseDown));
                memset(io.KeysDown, 0, sizeof(io.KeysDown));
                *key = 0;
            }
            ImGui::SetActiveID(id, window);
            ImGui::FocusWindow(window);
        }
        else if (io.MouseClicked[0]) {
            if (g.ActiveId == id)
                ImGui::ClearActiveID();
        }

        if (g.ActiveId == id) {
            for (auto i = 0; i < 5; i++) {
                if (io.MouseDown[i]) {
                    switch (i) {
                    case 0:
                        k = 0x01;
                        break;
                    case 1:
                        k = 0x02;
                        break;
                    case 2:
                        k = 0x04;
                        break;
                    case 3:
                        k = 0x05;
                        break;
                    case 4:
                        k = 0x06;
                        break;
                    }
                    value_changed = true;
                    ImGui::ClearActiveID();
                }
            }
            if (!value_changed) {
                for (auto i = 0x08; i <= 0xA5; i++) {
                    if (io.KeysDown[i]) {
                        k = i;
                        value_changed = true;
                        ImGui::ClearActiveID();
                    }
                }
            }

            if (IsKeyPressedMap(ImGuiKey_Escape)) {
                *key = 0;
                ImGui::ClearActiveID();
            }
            else {
                *key = k;
            }
        }

        return value_changed;
    }

    struct theme_state
    {
        ImVec4 background;
        float smooth_swap, alpha_line, line_size;
    };

    bool ThemeButton(const char* id_theme, bool dark, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(id_theme);
        const ImVec2 label_size = CalcTextSize(id_theme, NULL, true), pos = window->DC.CursorPos;

        ImVec2 size = CalcItemSize(size_arg, label_size.x, label_size.y);

        const ImRect bb(pos, pos + size * dpi);

        ItemSize(size * dpi, 0.f);
        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, NULL);

        static std::map<ImGuiID, theme_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, theme_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.alpha_line = ImLerp(it_anim->second.alpha_line, dark ? 1.f : 0.f, g.IO.DeltaTime * 6.f);
        it_anim->second.line_size = ImLerp(it_anim->second.line_size, dark ? (size_arg.x / 4) : (size_arg.x / 2), g.IO.DeltaTime * 6.f);

        it_anim->second.smooth_swap = ImLerp(it_anim->second.smooth_swap, dark ? size_arg.y : 0, g.IO.DeltaTime * 12.f);

        GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(c::widget::bg_inactive), c::widget::rounding);

        PushClipRect(bb.Min, bb.Max, true);

        PushFont(font::icomoon);
        GetWindowDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x * dpi - CalcTextSize("t").x) / 2, bb.Max.y - CalcTextSize("t").y - (size_arg.y * dpi - CalcTextSize("t").y) / 2 + it_anim->second.smooth_swap * dpi), GetColorU32(c::accent), "t");
        GetWindowDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x * dpi - CalcTextSize("j").x) / 2, bb.Max.y - CalcTextSize("j").y - (size_arg.y * dpi - CalcTextSize("j").y) / 2 - 44 * dpi + it_anim->second.smooth_swap * dpi), GetColorU32(c::accent), "j");
        PopFont();

        PopClipRect();


        return pressed;
    }

    struct ButtonState 
    {
        float alpha_line = 0.0f;
        float line_size = 0.0f;
        float smooth_swap = 0.0f;
    };

    bool Button( const char* label, const ImVec2& size_arg ) 
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow( );

        if ( window->SkipItems )
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiID id = window->GetID( label );
        const ImVec2 labelSize = ImGui::CalcTextSize( label, NULL, true );
        const ImVec2 pos = window->DC.CursorPos;

        const ImRect bb( pos, pos + size_arg );

        ImGui::ItemSize( size_arg, 0.f );
        if ( !ImGui::ItemAdd( bb, id ) )
            return false;

        bool hovered, held, pressed;
        pressed = ImGui::ButtonBehavior( bb, id, &hovered, &held );

        static std::map<ImGuiID, ButtonState> anim;
        auto it_anim = anim.find( id );

        if ( it_anim == anim.end( ) ) {
            anim.insert( { id, ButtonState( ) } );
            it_anim = anim.find( id );
        }

        it_anim->second.alpha_line = ImLerp( it_anim->second.alpha_line, hovered ? 1.0f : 0.0f, g.IO.DeltaTime * 6.f );
        it_anim->second.line_size = ImLerp( it_anim->second.line_size, held ? ( size_arg.x / 4 ) : ( size_arg.x / 2 ), g.IO.DeltaTime * 6.f );
        it_anim->second.smooth_swap = ImLerp( it_anim->second.smooth_swap, held ? size_arg.y : 0.0f, g.IO.DeltaTime * 12.f );

        ImVec4 buttonColor = c::widget::bg_inactive;
        if ( hovered )
            buttonColor = c::accent;
        if ( held )
            buttonColor = c::accent;

        ImGui::GetWindowDrawList( )->AddRectFilled( bb.Min, bb.Max, ImGui::ColorConvertFloat4ToU32( buttonColor ), 4.0f );

        ImGui::PushClipRect( bb.Min, bb.Max, true );

        ImGui::GetWindowDrawList( )->AddText( ImVec2( bb.Min.x + ( size_arg.x - labelSize.x ) / 2,
            bb.Min.y + ( size_arg.y - labelSize.y ) / 2 ),
            IM_COL32( 255, 255, 255, 255 ), label );

        ImGui::PopClipRect( );

        return pressed;
    }

    struct begin_state
    {
        ImVec4 background, text, outline;
        float open, alpha, combo_size = 0.f, shadow_opticaly;
        bool opened_combo = false, hovered = false;
        float arrow_roll;
    };

    static float CalcMaxPopupHeightFromItemCount(int items_count)
    {
        ImGuiContext& g = *GImGui;
        if (items_count <= 0)
            return FLT_MAX;
        return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
    }

    int rotation_start_index;
    void ImRotateStart()
    {
        rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
    }

    ImVec2 ImRotationCenter()
    {
        ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX);

        const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

        return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2);
    }

    void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
    {
        float s = sin(rad), c = cos(rad);
        center = ImRotate(center, s, c) - center;

        auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
    }

    bool BeginCombo(const char* label, const char* preview_value, int val, bool multi, ImGuiComboFlags flags)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = GetCurrentWindow();

        g.NextWindowData.ClearFlags();
        if (window->SkipItems) return false;

        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const float w = ((GetContentRegionMax().x - style.WindowPadding.x));
        const float y_size = 32 * dpi;

        const ImRect bb(window->DC.CursorPos + ImVec2(w / 1.8, 0), window->DC.CursorPos + ImVec2(w, 20 * dpi));
        const ImRect rect(window->DC.CursorPos + ImVec2(w / 1.8, -5 * dpi), window->DC.CursorPos + ImVec2(w, (y_size - 5 * dpi)));

        const ImRect total_bb(bb.Min, bb.Max);
        ItemSize(bb, 0.f);

        if (!ItemAdd(bb, id, &bb)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held);

        static std::map<ImGuiID, begin_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, begin_state() });
            it_anim = anim.find(id);
        }

        if (hovered && g.IO.MouseClicked[0] || it_anim->second.opened_combo && g.IO.MouseClicked[0] && !it_anim->second.hovered) it_anim->second.opened_combo = !it_anim->second.opened_combo;

        it_anim->second.arrow_roll = ImLerp(it_anim->second.arrow_roll, it_anim->second.opened_combo ? -1.f : 1.f, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, it_anim->second.opened_combo ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);
        it_anim->second.combo_size = ImLerp(it_anim->second.combo_size, it_anim->second.opened_combo ? (val * 32 * dpi) + 15 * dpi : 0.f, g.IO.DeltaTime * 12.f);

        GetWindowDrawList()->AddRectFilled(rect.Min, rect.Max, GetColorU32(c::widget::bg_inactive), c::widget::rounding);

        GetWindowDrawList()->AddText(ImVec2(window->DC.CursorPos.x, rect.Min.y + (22 * dpi - CalcTextSize(label).y) / 2 + 4 * dpi), GetColorU32(it_anim->second.text), label);

        PushClipRect(rect.Min, rect.Max, true);
        GetWindowDrawList()->AddText(ImVec2(rect.Min.x + ((y_size - CalcTextSize(label).y) / 2), rect.Min.y + (y_size - CalcTextSize(label).y) / 2), GetColorU32(c::text::text_active), preview_value);
        PopClipRect();

        GetWindowDrawList()->AddRectFilled(rect.Max - ImVec2(y_size, y_size), rect.Max, GetColorU32(it_anim->second.background), c::widget::rounding);
        GetWindowDrawList()->AddRectFilledMultiColor(rect.Max - ImVec2(130 * dpi, y_size), rect.Max, GetColorU32(c::widget::bg_inactive, 0.f), GetColorU32(c::widget::bg_inactive, 1.f), GetColorU32(c::widget::bg_inactive, 1.f), GetColorU32(c::widget::bg_inactive, 0.f), c::widget::rounding);

        ImRotateStart();
        PushFont(font::icomoon);
        GetWindowDrawList()->AddText(ImVec2(bb.Max.x - (y_size + CalcTextSize("i").y) / 2, bb.Min.y + (y_size - CalcTextSize("i").y) / 2 - 5 * dpi), GetColorU32(c::text::text), "i");
        PopFont();
        ImRotateEnd(1.57f * it_anim->second.arrow_roll);

        if (!IsRectVisible(rect.Min, rect.Max + ImVec2(0, 2)))
        {
            it_anim->second.opened_combo = false;
            it_anim->second.combo_size = 0.f;
        }

        if (!it_anim->second.opened_combo && it_anim->second.combo_size < 2.f) return false;

        ImGui::SetNextWindowPos(ImVec2(rect.Min.x, rect.Max.y + 5 * dpi));
        ImGui::SetNextWindowSize(ImVec2(rect.GetWidth(), it_anim->second.combo_size));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoScrollWithMouse;

        PushStyleColor(ImGuiCol_WindowBg, c::widget::bg_inactive);
        PushStyleVar(ImGuiStyleVar_WindowRounding, c::widget::rounding);
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15 * dpi, 15 * dpi));
        PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

        bool ret = Begin(label, NULL, window_flags);

        PopStyleVar(3);
        PopStyleColor(1);

        it_anim->second.hovered = IsWindowHovered();

        if (multi && it_anim->second.hovered && g.IO.MouseClicked[0]) it_anim->second.opened_combo = false;

        return true;
    }

    void EndCombo()
    {
        End();
    }

    void MultiCombo(const char* label, bool variable[], const char* labels[], int count)
    {
        ImGuiContext& g = *GImGui;

        std::string preview = "None";

        for (auto i = 0, j = 0; i < count; i++)
        {
            if (variable[i])
            {
                if (j)
                    preview += (", ") + (std::string)labels[i];
                else
                    preview = labels[i];

                j++;
            }
        }

        if (BeginCombo(label, preview.c_str(), count))
        {
            for (auto i = 0; i < count; i++)
            {
                PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15 * dpi, 15 * dpi));
                PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15 * dpi, 15 * dpi));
                edited::Selectable(labels[i], &variable[i], ImGuiSelectableFlags_DontClosePopups);
                PopStyleVar(2);
            }
            End();
        }

        preview = ("None");
    }

    bool BeginComboPreview()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImGuiComboPreviewData* preview_data = &g.ComboPreviewData;

        if (window->SkipItems || !(g.LastItemData.StatusFlags & ImGuiItemStatusFlags_Visible)) return false;

        IM_ASSERT(g.LastItemData.Rect.Min.x == preview_data->PreviewRect.Min.x && g.LastItemData.Rect.Min.y == preview_data->PreviewRect.Min.y);

        if (!window->ClipRect.Overlaps(preview_data->PreviewRect)) return false;

        preview_data->BackupCursorPos = window->DC.CursorPos;
        preview_data->BackupCursorMaxPos = window->DC.CursorMaxPos;
        preview_data->BackupCursorPosPrevLine = window->DC.CursorPosPrevLine;
        preview_data->BackupPrevLineTextBaseOffset = window->DC.PrevLineTextBaseOffset;
        preview_data->BackupLayout = window->DC.LayoutType;
        window->DC.CursorPos = preview_data->PreviewRect.Min + g.Style.FramePadding;
        window->DC.CursorMaxPos = window->DC.CursorPos;
        window->DC.LayoutType = ImGuiLayoutType_Horizontal;
        window->DC.IsSameLine = false;
        PushClipRect(preview_data->PreviewRect.Min, preview_data->PreviewRect.Max, true);

        return true;
    }

    void EndComboPreview()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImGuiComboPreviewData* preview_data = &g.ComboPreviewData;

        ImDrawList* draw_list = window->DrawList;
        if (window->DC.CursorMaxPos.x < preview_data->PreviewRect.Max.x && window->DC.CursorMaxPos.y < preview_data->PreviewRect.Max.y)
            if (draw_list->CmdBuffer.Size > 1)
            {
                draw_list->_CmdHeader.ClipRect = draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 1].ClipRect = draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 2].ClipRect;
                draw_list->_TryMergeDrawCmds();
            }
        PopClipRect();
        window->DC.CursorPos = preview_data->BackupCursorPos;
        window->DC.CursorMaxPos = ImMax(window->DC.CursorMaxPos, preview_data->BackupCursorMaxPos);
        window->DC.CursorPosPrevLine = preview_data->BackupCursorPosPrevLine;
        window->DC.PrevLineTextBaseOffset = preview_data->BackupPrevLineTextBaseOffset;
        window->DC.LayoutType = preview_data->BackupLayout;
        window->DC.IsSameLine = false;
        preview_data->PreviewRect = ImRect();
    }

    static const char* Items_ArrayGetter(void* data, int idx)
    {
        const char* const* items = (const char* const*)data;
        return items[idx];
    }

    static const char* Items_SingleStringGetter(void* data, int idx)
    {
        const char* items_separated_by_zeros = (const char*)data;
        int items_count = 0;
        const char* p = items_separated_by_zeros;
        while (*p)
        {
            if (idx == items_count)
                break;
            p += strlen(p) + 1;
            items_count++;
        }
        return *p ? p : NULL;
    }

    bool Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items)
    {
        ImGuiContext& g = *GImGui;

        const char* preview_value = NULL;
        if (*current_item >= 0 && *current_item < items_count)
            preview_value = getter(user_data, *current_item);

        if (popup_max_height_in_items != -1 && !(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint))
            SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

        if (!BeginCombo(label, preview_value, items_count, ImGuiComboFlags_None)) return false;

        bool value_changed = false;
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(15 * dpi, 15 * dpi));
        for (int i = 0; i < items_count; i++)
        {
            const char* item_text = getter(user_data, i);
            if (item_text == NULL)
                item_text = "*Unknown item*";

            PushID(i);
            const bool item_selected = (i == *current_item);
            if (edited::Selectable(item_text, item_selected) && *current_item != i)
            {
                value_changed = true;
                *current_item = i;
            }
            if (item_selected)
                SetItemDefaultFocus();
            PopID();
        }
        PopStyleVar();

        EndCombo();

        if (value_changed)
            MarkItemEdited(g.LastItemData.ID);

        return value_changed;
    }

    bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
    {
        const bool value_changed = Combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
        return value_changed;
    }

    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
    {
        int items_count = 0;
        const char* p = items_separated_by_zeros;
        while (*p)
        {
            p += strlen(p) + 1;
            items_count++;
        }
        bool value_changed = Combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
        return value_changed;
    }


    struct select_state
    {
        ImVec4 text;
    };

    bool Selectable(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        ImGuiID id = window->GetID(label);
        ImVec2 label_size = CalcTextSize(label, NULL, true);
        ImVec2 size(size_arg.x != 0.0f ? size_arg.x : label_size.x, size_arg.y != 0.0f ? size_arg.y : label_size.y);
        ImVec2 pos = window->DC.CursorPos;
        pos.y += window->DC.CurrLineTextBaseOffset;
        ItemSize(size, 0.0f);

        const bool span_all_columns = (flags & ImGuiSelectableFlags_SpanAllColumns) != 0;
        const float min_x = span_all_columns ? window->ParentWorkRect.Min.x : pos.x;
        const float max_x = span_all_columns ? window->ParentWorkRect.Max.x : window->WorkRect.Max.x;
        if (size_arg.x == 0.0f || (flags & ImGuiSelectableFlags_SpanAvailWidth)) size.x = ImMax(label_size.x, max_x - min_x);

        const ImVec2 text_min = pos;
        const ImVec2 text_max(min_x + size.x, pos.y + size.y);

        ImRect bb(min_x, pos.y, text_max.x, text_max.y);
        if ((flags & ImGuiSelectableFlags_NoPadWithHalfSpacing) == 0)
        {
            const float spacing_x = span_all_columns ? 0.0f : style.ItemSpacing.x;
            const float spacing_y = style.ItemSpacing.y;
            const float spacing_L = IM_TRUNC(spacing_x * 0.50f);
            const float spacing_U = IM_TRUNC(spacing_y * 0.50f);
            bb.Min.x -= spacing_L;
            bb.Min.y -= spacing_U;
            bb.Max.x += (spacing_x - spacing_L);
            bb.Max.y += (spacing_y - spacing_U);
        }

        const float backup_clip_rect_min_x = window->ClipRect.Min.x;
        const float backup_clip_rect_max_x = window->ClipRect.Max.x;
        if (span_all_columns)
        {
            window->ClipRect.Min.x = window->ParentWorkRect.Min.x;
            window->ClipRect.Max.x = window->ParentWorkRect.Max.x;
        }

        const bool disabled_item = (flags & ImGuiSelectableFlags_Disabled) != 0;
        const bool item_add = ItemAdd(bb, id, NULL, disabled_item ? ImGuiItemFlags_Disabled : ImGuiItemFlags_None);
        if (span_all_columns)
        {
            window->ClipRect.Min.x = backup_clip_rect_min_x;
            window->ClipRect.Max.x = backup_clip_rect_max_x;
        }

        if (!item_add) return false;

        const bool disabled_global = (g.CurrentItemFlags & ImGuiItemFlags_Disabled) != 0;
        if (disabled_item && !disabled_global) BeginDisabled();

        if (span_all_columns && window->DC.CurrentColumns) PushColumnsBackground();
        else if (span_all_columns && g.CurrentTable) TablePushBackgroundChannel();

        ImGuiButtonFlags button_flags = 0;
        if (flags & ImGuiSelectableFlags_NoHoldingActiveID) { button_flags |= ImGuiButtonFlags_NoHoldingActiveId; }
        if (flags & ImGuiSelectableFlags_NoSetKeyOwner) { button_flags |= ImGuiButtonFlags_NoSetKeyOwner; }
        if (flags & ImGuiSelectableFlags_SelectOnClick) { button_flags |= ImGuiButtonFlags_PressedOnClick; }
        if (flags & ImGuiSelectableFlags_SelectOnRelease) { button_flags |= ImGuiButtonFlags_PressedOnRelease; }
        if (flags & ImGuiSelectableFlags_AllowDoubleClick) { button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick; }
        if ((flags & ImGuiSelectableFlags_AllowOverlap) || (g.LastItemData.InFlags & ImGuiItemFlags_AllowOverlap)) { button_flags |= ImGuiButtonFlags_AllowOverlap; }

        const bool was_selected = selected;
        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, button_flags);

        if ((flags & ImGuiSelectableFlags_SelectOnNav) && g.NavJustMovedToId != 0 && g.NavJustMovedToFocusScopeId == g.CurrentFocusScopeId)
            if (g.NavJustMovedToId == id)  selected = pressed = true;

        // Update NavId when clicking or when Hovering (this doesn't happen on most widgets), so navigation can be resumed with gamepad/keyboard
        if (pressed || (hovered && (flags & ImGuiSelectableFlags_SetNavIdOnHover)))
        {
            if (!g.NavDisableMouseHover && g.NavWindow == window && g.NavLayer == window->DC.NavLayerCurrent)
            {
                SetNavID(id, window->DC.NavLayerCurrent, g.CurrentFocusScopeId, WindowRectAbsToRel(window, bb)); // (bb == NavRect)
                g.NavDisableHighlight = true;
            }
        }
        if (pressed) MarkItemEdited(id);

        if (selected != was_selected)  g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_ToggledSelection;


        if (g.NavId == id) RenderNavHighlight(bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);

        if (span_all_columns && window->DC.CurrentColumns) PopColumnsBackground();
        else if (span_all_columns && g.CurrentTable) TablePopBackgroundChannel();

        static std::map<ImGuiID, select_state> anim;
        auto it_anim = anim.find(id);

        if (it_anim == anim.end())
        {
            anim.insert({ id, select_state() });
            it_anim = anim.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, selected ? c::accent : c::text::text, g.IO.DeltaTime * 6.f);

        PushStyleColor(ImGuiCol_Text, GetColorU32(it_anim->second.text));
        RenderTextClipped(text_min, text_max, label, NULL, &label_size, style.SelectableTextAlign, &bb);
        PopStyleColor();

        if (pressed && (window->Flags & ImGuiWindowFlags_Popup) && !(flags & ImGuiSelectableFlags_DontClosePopups) && !(g.LastItemData.InFlags & ImGuiItemFlags_SelectableDontClosePopup)) CloseCurrentPopup();

        if (disabled_item && !disabled_global) EndDisabled();

        return pressed;
    }

    bool Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags, const ImVec2& size_arg)
    {
        if (Selectable(label, *p_selected, flags, size_arg))
        {
            *p_selected = !*p_selected;
            return true;
        }
        return false;
    }

}