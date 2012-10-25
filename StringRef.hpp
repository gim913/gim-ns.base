/**
 * @file StringRef.hpp
 * @author Michal 'GiM' Spadlinski <gim913@gmail.com>
 *
 * 
 */

#pragma once
#ifndef GIM_BASE_STRINGREF_HPP
#define GIM_BASE_STRINGREF_HPP

#include <cstring>

namespace {
	template <class T>
	size_t stringLen(const T* str) { return 0; }

	template<>
	size_t stringLen<char>(const char* str) {
		return ::strlen(str);
	}

	template<>
	size_t stringLen<wchar_t>(const wchar_t* str) {
		return ::wcslen(str);
	}

	template <class T>
	class StringRef_
	{
	public:
		StringRef_(const T* cString, size_t cStringLen = 0) : ptr(cString), len(cStringLen) {
			if (!len) {
				len = stringLen(cString);
			}
		}

		size_t length() const {
			return len;
		}
	private:
		const char* ptr;
		size_t len;
	};
}

namespace gim {
	typedef StringRef_<char> StringRef;
}

#endif // GIM_BASE_STRINGREF_HPP
