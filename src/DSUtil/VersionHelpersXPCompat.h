/*
 * XP-compatible subset of the Windows SDK VersionHelpers.h.
 *
 * The Windows 7.0 SDK selected by the XP build does not ship
 * VersionHelpers.h. These inline helpers use VerifyVersionInfoW,
 * which is available on Windows XP, and introduce no Vista+ imports.
 */
#pragma once

#include <windows.h>

#ifndef VERSIONHELPERAPI
#define VERSIONHELPERAPI inline BOOL
#endif

VERSIONHELPERAPI
IsWindowsVersionOrGreater(WORD majorVersion, WORD minorVersion, WORD servicePackMajor)
{
    OSVERSIONINFOEXW versionInfo = {};
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
    versionInfo.dwMajorVersion = majorVersion;
    versionInfo.dwMinorVersion = minorVersion;
    versionInfo.wServicePackMajor = servicePackMajor;

    DWORDLONG conditionMask = 0;
    conditionMask = VerSetConditionMask(conditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    conditionMask = VerSetConditionMask(conditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
    conditionMask = VerSetConditionMask(conditionMask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

    return VerifyVersionInfoW(
        &versionInfo,
        VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR,
        conditionMask) != FALSE;
}

VERSIONHELPERAPI IsWindowsXPOrGreater()
{
    return IsWindowsVersionOrGreater(5, 1, 0);
}

VERSIONHELPERAPI IsWindowsXPSP1OrGreater()
{
    return IsWindowsVersionOrGreater(5, 1, 1);
}

VERSIONHELPERAPI IsWindowsXPSP2OrGreater()
{
    return IsWindowsVersionOrGreater(5, 1, 2);
}

VERSIONHELPERAPI IsWindowsXPSP3OrGreater()
{
    return IsWindowsVersionOrGreater(5, 1, 3);
}

VERSIONHELPERAPI IsWindowsVistaOrGreater()
{
    return IsWindowsVersionOrGreater(6, 0, 0);
}

VERSIONHELPERAPI IsWindowsVistaSP1OrGreater()
{
    return IsWindowsVersionOrGreater(6, 0, 1);
}

VERSIONHELPERAPI IsWindowsVistaSP2OrGreater()
{
    return IsWindowsVersionOrGreater(6, 0, 2);
}

VERSIONHELPERAPI IsWindows7OrGreater()
{
    return IsWindowsVersionOrGreater(6, 1, 0);
}

VERSIONHELPERAPI IsWindows7SP1OrGreater()
{
    return IsWindowsVersionOrGreater(6, 1, 1);
}

VERSIONHELPERAPI IsWindows8OrGreater()
{
    return IsWindowsVersionOrGreater(6, 2, 0);
}

VERSIONHELPERAPI IsWindows8Point1OrGreater()
{
    return IsWindowsVersionOrGreater(6, 3, 0);
}

VERSIONHELPERAPI IsWindows10OrGreater()
{
    return IsWindowsVersionOrGreater(10, 0, 0);
}

VERSIONHELPERAPI IsWindowsServer()
{
    OSVERSIONINFOEXW versionInfo = {};
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
    versionInfo.wProductType = VER_NT_WORKSTATION;

    const DWORDLONG conditionMask =
        VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);

    return VerifyVersionInfoW(&versionInfo, VER_PRODUCT_TYPE, conditionMask) == FALSE;
}
