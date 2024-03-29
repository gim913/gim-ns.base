/**
 * @file Memory.hpp
 * @author Michal 'GiM' Spadlinski <gim913@gmail.com>
 *
 * 
 */

#pragma once
#ifndef GIM_BASE_MEMORY_HPP
#define GIM_BASE_MEMORY_HPP

#include "types.h"

namespace gim { namespace pod {

    template <class T>
    struct GMemory {
        typedef T ValueType;
        
        GMemory(T* ptr, size_t count) : ptr(ptr), count(count) {}

        template<size_t S>
        GMemory(const T (&staticArray)[S]) : ptr(const_cast<T*>(staticArray)), count(S) {}

        template<class U>
        GMemory<U> as() const {
            return GMemory<U>(reinterpret_cast<U*>(ptr), count*sizeof(T)/sizeof(U));
        }

        bool isValid() const {
            return (0 != ptr);
        }
        T* ptr;
        // warning: count not size!
        size_t count;
    };

    typedef GMemory<char>  String;
    typedef GMemory<Gubyte> Memory;

} }

#endif // GIM_BASE_MEMORY_HPP
