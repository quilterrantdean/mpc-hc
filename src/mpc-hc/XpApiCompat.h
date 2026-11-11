/*
 * Runtime compatibility helpers for the Windows XP build.
 *
 * Compile-time Windows 7 declarations are used for modern COM and common
 * control interfaces. APIs not present on XP must be resolved dynamically
 * or provided with an XP fallback.
 */
#pragma once

#include <mutex>

#ifndef TABLET_DISABLE_PRESSANDHOLD
#define TABLET_DISABLE_PRESSANDHOLD 0x00000001
#endif

#ifndef MICROSOFT_TABLETPENSERVICE_PROPERTY
#define MICROSOFT_TABLETPENSERVICE_PROPERTY _T("MicrosoftTabletPenServiceProperty")
#endif

#ifndef LVS_EX_AUTOSIZECOLUMNS
#define LVS_EX_AUTOSIZECOLUMNS 0x10000000
#endif

#ifndef BCM_SETSHIELD
#define BCM_SETSHIELD (BCM_FIRST + 0x000C)
#endif

inline ULONGLONG MpcGetTickCount64()
{
    typedef ULONGLONG (WINAPI* GetTickCount64Fn)(void);

    // GetTickCount64 is Vista+, so do not create a static Kernel32 import.
    static const GetTickCount64Fn nativeFunction =
        reinterpret_cast<GetTickCount64Fn>(
            GetProcAddress(GetModuleHandle(_T("kernel32.dll")), "GetTickCount64"));

    if (nativeFunction) {
        return nativeFunction();
    }

    // XP fallback: extend the 32-bit millisecond counter across wraparound.
    static std::mutex counterMutex;
    static DWORD previousTick = 0;
    static ULONGLONG upperBits = 0;

    std::lock_guard<std::mutex> guard(counterMutex);
    const DWORD currentTick = GetTickCount();
    if (currentTick < previousTick) {
        upperBits += (1ULL << 32);
    }
    previousTick = currentTick;

    return upperBits | static_cast<ULONGLONG>(currentTick);
}
