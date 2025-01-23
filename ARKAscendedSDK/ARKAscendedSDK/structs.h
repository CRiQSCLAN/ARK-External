
namespace UnrealEngine5
{

    struct PlayerInformation {
        std::string PlayerName;
        std::string PrimalName;
        std::string ActorFName;
        int RequiredLevel;
        int PlayerLevel;
        FVector EntityPos;
        float Distance;
        uintptr_t Mesh;
    };
    INLINED std::vector<PlayerInformation> PlayerList;


    struct DinoInformation {
        std::string PlayerName;
        std::string PrimalName;
        std::string ActorFName;
        bool isCarnivore;
        bool isBaby;
        float MatingProgress;
        bool isFemale;
        float MaxHealth;
        float CurrentHealth;
        float MaxTorpor;
        float CurrentTorpor;
        bool isBoss;
        bool canFly;
        int RequiredLevel;
        int PlayerLevel;
        FVector EntityPos;
        float Distance;
        uintptr_t Mesh;
    };
    INLINED std::vector<DinoInformation> DinoList;


    struct LootInformation {
        std::string PrimalName;
        std::string ActorFName;
        int RequiredLevel;
        FVector EntityPos;
        float Distance;
        uintptr_t Mesh;
        FVector CurrentCrateLocation;
        bool FinishedMovement;
        float Health;
        float MaxHealth;

    };
    INLINED std::vector<LootInformation> LootList;

    struct DebugInformation {
        std::string FName;
        FVector Position;
    };
    INLINED std::vector<DebugInformation> DebugList;
}

namespace math_utils {
    INLINED float custom_sqrtf(float _X) {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_X)));
    }

    static INLINED void custom_Memcpy(const void* dstp, const void* srcp, UINT len) {
        ULONG* dst = (ULONG*)dstp;
        ULONG* src = (ULONG*)srcp;
        UINT i, tail;

        for (i = 0; i < (len / sizeof(ULONG)); i++)
            *dst++ = *src++;

        tail = len & (sizeof(ULONG) - 1);
        if (tail) {
            UCHAR* dstb = (UCHAR*)dstp;
            UCHAR* srcb = (UCHAR*)srcp;

            for (i = len - tail; i < len; i++)
                dstb[i] = srcb[i];
        }
    }

    INLINED float custom_sinf(float _X) {
        return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_cosf(float _X) {
        return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_acosf(float _X) {
        return _mm_cvtss_f32(_mm_acos_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_tanf(float _X) {
        return _mm_cvtss_f32(_mm_tan_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_atan2f(float _X, float _Y) {
        return _mm_cvtss_f32(_mm_atan2_ps(_mm_set_ss(_X), _mm_set_ss(_Y)));
    }

    INLINED float custom_pow(float _X, float _Y) {
        return _mm_cvtss_f32(_mm_pow_ps(_mm_set_ss(_X), _mm_set_ss(_Y)));
    }

    INLINED float custom_pow(float _X) {
        return _mm_cvtss_f32(_mm_sqrt_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_asinf(float _X) {
        return _mm_cvtss_f32(_mm_asin_ps(_mm_set_ss(_X)));
    }

    INLINED float custom_fabsf(float x) {
        __m128 x_vec = _mm_set_ss(x);
        x_vec = _mm_and_ps(x_vec, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
        return _mm_cvtss_f32(x_vec);
    }

    INLINED int custom_compare(const char* X, const char* Y) {
        while (*X && *Y) {
            if (*X != *Y) {
                return 0;
            }
            X++;
            Y++;
        }

        return (*Y == '\0');
    }

    INLINED int custom_wcompare(const wchar_t* X, const wchar_t* Y) {
        while (*X && *Y) {
            if (*X != *Y) {
                return 0;
            }
            X++;
            Y++;
        }

        return (*Y == L'\0');
    }

    INLINED const wchar_t* custom_wcsstr(const wchar_t* X, const wchar_t* Y) {
        while (*X != L'\0') {
            if ((*X == *Y) && custom_wcompare(X, Y)) {
                return X;
            }
            X++;
        }

        return NULL;
    }

    INLINED const char* custom_strstr(const char* X, const char* Y) {
        while (*X != '\0') {
            if ((*X == *Y) && custom_compare(X, Y)) {
                return X;
            }
            X++;
        }

        return NULL;
    }

    INLINED int custom_strlen(const char* string) {
        int cnt = 0;
        if (string) {
            for (; *string != 0; ++string) ++cnt;
        }

        return cnt;
    }

    INLINED int custom_wcslen(const wchar_t* string) {
        int cnt = 0;
        if (string) {
            for (; *string != 0; ++string) ++cnt;
        }

        return cnt;
    }

}