#pragma once

#include "config.h"
#include <iostream>

#define LOG_IMPL(FORMAT, ...) std::printf(FORMAT "\n", __VA_ARGS__)

#define LOG_INFO(FORMAT, ...) LOG_IMPL(FORMAT, __VA_ARGS__)

#if PBR_DEBUG_LEVEL
#define LOG_DEBUG(FORMAT, ...) LOG_IMPL(FORMAT, __VA_ARGS__)
#else
#define LOG_DEBUG(FORMAT, ...)
#endif
