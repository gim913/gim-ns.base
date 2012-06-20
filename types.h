/**
 * @file types.h
 * @author Michal 'GiM' Spadlinski <gim913@gmail.com>
 *
 * 
 */
#pragma once
#ifndef GIM_BASE_TYPES_H
#define GIM_BASE_TYPES_H

#if defined(_MSC_VER) && _MSC_VER < 1600

#else

#include <stdint.h>

// names based on digitalmars' D
typedef int8_t   Gbyte;
typedef uint8_t  Gubyte;
typedef int16_t  Gshort;
typedef uint16_t Gushort;
typedef int32_t  Gint;
typedef uint32_t Guint;
typedef int64_t  Glong;
typedef uint64_t Gulong;

#endif

#include <stddef.h> // size_t, intptr_t, uintptr_t, wchar_t

typedef uint64_t FileSize;

#endif // GIM_COMMON_TYPES_H
