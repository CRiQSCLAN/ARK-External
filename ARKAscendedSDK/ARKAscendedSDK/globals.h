#pragma once

namespace globals
{
    INLINED bool debug = false;
    INLINED float size = 5.f;
    namespace memory {
        INLINED uintptr_t base_address;
    }

    INLINED ImColor menu_color_dark;
    INLINED ImColor menu_color_light;
    INLINED ImColor misc_color;
    //INLINED ImColor player_name;
    //INLINED ImColor player_distance;
    //INLINED ImColor player_line;

    INLINED float n_width = 0;
    INLINED float n_height = 0;
    INLINED float n_half_width = 0;
    INLINED float n_half_height = 0;

    namespace threads {
        INLINED bool set_highest_priority() {
            BOOL result = SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
            if (result == 0) {
                return false;
            }

            return true;
        }
    }
}
namespace settings
{
    INLINED bool show_menu = false;
    INLINED bool show_render = true;
    INLINED bool misc_rgb = false;
    INLINED bool show_fov_circle = true;
    INLINED float fov_value = 10.0f;
    INLINED bool show_crosshair = true;
    namespace other {
        INLINED float menu_color_dark[4] = { 139 / 255.0f, 0 / 255.0f, 0 / 255.0f, 255 / 255.0f };
        INLINED float menu_color_light[4] = { 121 / 255.0f, 131 / 255.0f, 207 / 255.0f, 255 / 255.0f };
        INLINED float misc_color[4] = { 253 / 255.0f, 244 / 255.0f, 210 / 255.0f, 255 / 255.0f };
        INLINED bool vsync = true;
        INLINED bool show_fps = true;
    }
    namespace visuals {
        INLINED float box_rounding = 0.0f;
        INLINED bool misc_outline = true;
        INLINED float text_font_size = 11.0f;
        INLINED bool text_outline = true;
    }


}
namespace dinos {
    INLINED bool enable = true;
    INLINED bool name = false;
    INLINED bool distance = false;
    INLINED bool line = false;
    INLINED bool gender = false;
    INLINED bool matingprogress = false;
    INLINED bool aggressivity = false;
    INLINED bool isbaby = false;
    INLINED bool health = false;
    INLINED bool torpor = false;
    INLINED bool isboss = false;
    INLINED bool level = false;
    INLINED float render_range = 2150.f;

}

namespace loot {
    INLINED bool enable = false;
}
namespace colors
{
    INLINED ImColor player_distance = ImColor(255, 0, 0, 255);
}
#define n_print( fmt ) do { \
    if ( globals::debug ) { \
        printf( _("[nsa-logs] -> [%s:%d] -> " fmt "\n"), __FUNCTION__, __LINE__ ); \
    } \
} while ( 0 )

#define n_log( fmt, ... ) do { \
    if ( globals::debug ) { \
        printf( _("[nsa-logs] -> [%s:%d] -> " fmt "\n"), __FUNCTION__, __LINE__, ##__VA_ARGS__ ); \
    } \
} while ( 0 )
#define PI 3.14159265358979323846f
#define M_PI 3.14159265358979323846264338327950288419716939937510
#define UCONST_PI 3.1415926
#define POINTER reinterpret_cast< uint64_t >
#define READ device_t.read<uint64_t>
#define WREAD device_t.read<uintptr_t>