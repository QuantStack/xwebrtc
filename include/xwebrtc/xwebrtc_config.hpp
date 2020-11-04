/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_CONFIG_HPP
#define XWEBRTC_CONFIG_HPP

// Visual C++ declspec macros
#ifdef _WIN32
    #ifdef XWEBRTC_EXPORTS
        #define XWEBRTC_API __declspec(dllexport)
    #else
        #define XWEBRTC_API __declspec(dllimport)
    #endif
#else
    #define XWEBRTC_API
#endif

// Project version
#define XWEBRTC_VERSION_MAJOR 0
#define XWEBRTC_VERSION_MINOR 6
#define XWEBRTC_VERSION_PATCH 0

// Binary version
#define XWEBRTC_BINARY_CURRENT 1
#define XWEBRTC_BINARY_REVISION 0
#define XWEBRTC_BINARY_AGE 1

// Semver requirement for jupyter-webrtc
#define XJUPYTER_WEBRTC_VERSION_MAJOR 0
#define XJUPYTER_WEBRTC_VERSION_MINOR 4
#define XJUPYTER_WEBRTC_VERSION_PATCH 1

// Composing the version strings from major, minor and patch
#define XWEBRTC_CONCATENATE(A, B) XWEBRTC_CONCATENATE_IMPL(A, B)
#define XWEBRTC_CONCATENATE_IMPL(A, B) A##B
#define XWEBRTC_STRINGIFY(a) XWEBRTC_STRINGIFY_IMPL(a)
#define XWEBRTC_STRINGIFY_IMPL(a) #a

#define XJUPYTER_WEBRTC_VERSION XWEBRTC_STRINGIFY(XWEBRTC_CONCATENATE(XJUPYTER_WEBRTC_VERSION_MAJOR,   \
                             XWEBRTC_CONCATENATE(.,XWEBRTC_CONCATENATE(XJUPYTER_WEBRTC_VERSION_MINOR,   \
                                                  XWEBRTC_CONCATENATE(.,XJUPYTER_WEBRTC_VERSION_PATCH)))))

inline std::string jupyter_webrtc_semver()
{
    return std::string("^") + XJUPYTER_WEBRTC_VERSION;
}

#ifdef __CLING__
#include "xwebrtc_config_cling.hpp"
#endif

#endif
