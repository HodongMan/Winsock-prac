#pragma once

// SDKDDKVer.h를 포함하면 최고 수준의 가용성을 가진 Windows 플랫폼이 정의됩니다.

// 이전 Windows 플랫폼에 대해 응용 프로그램을 빌드하려는 경우에는 SDKDDKVer.h를 포함하기 전에
// WinSDKVer.h를 포함하고 _WIN32_WINNT 매크로를 지원하려는 플랫폼으로 설정하십시오.

#include <SDKDDKVer.h>


#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <assert.h>
#include <set>
#include <deque>
#include <mutex>
#include <thread>



#include <errno.h>

#if defined(WIN32) || defined(WIN64)
#define OS_PLATFORM_WINDOWS
#elif defined(LINUX32) || defined(LINUX64)
#define OS_PLATFORM_LINUX
#endif


#ifdef OS_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <io.h>
#include <process.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <mswsock.h>
#include <time.h>
#include <stdarg.h>
#pragma  comment(lib,"ws2_32")
#pragma  comment(lib, "Mswsock")

#endif