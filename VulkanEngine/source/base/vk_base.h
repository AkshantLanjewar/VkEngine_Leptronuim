#pragma once

#ifndef _WIN32

#pragma comment(linker, "/subsystem:windows")
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <ShellScalingAPI.h>

#endif // !_WIN32

#include <iostream>
#include <chrono>
#include <sys/stat.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>

#include <string>
#include <array>
#include <numeric>

#include <vulkan/vulkan.h>

#include "../vendor/key_codes.h"
#include "../lib/vulkan_tools.h"
#include "../lib/vulkan_debug.h"

#include "../lib/vk_initializers.hpp"
