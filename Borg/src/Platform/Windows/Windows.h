#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlobj.h>
#include <shellscalingapi.h>
#include <Lmcons.h>
#include <wininet.h>
#include <commctrl.h>

// prevent name conflict with Path::GetTempFileName
#undef GetTempFileName
#undef GetTempPath