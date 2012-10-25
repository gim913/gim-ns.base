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

	/**
	 * generic StringRef class, does not own the underlying data
	 */
	template <class T>
	class StringRef_
	{
		StringRef_& operator=(const StringRef_&);
	public:
		// expects string to be null terminated
		// cStringLen should be length without terminating '\0'
		StringRef_(const T* cString, size_t cStringLen = 0) : ptr(cString), len(cStringLen) {
			if (!len) {
				len = stringLen(cString);
			}
			len += 1;
		}

		StringRef_(const StringRef_& oth) : ptr(oth.ptr), len(oth.len) {
		}

		// length of a string without terminating null
		size_t length() const {
			return len-1;
		}

		size_t size() const {
			return len*sizeof(T);
		}

		typedef const T* iterator;
		iterator begin() const {
			return ptr;
		}

		// returns iterator, that points at terminating null
		iterator end() const {
			return ptr+len-1;
		}
	private:
		const T* ptr;
		size_t len;
	};
}

namespace gim {
	typedef StringRef_<char> StringRef;
}

#endif // GIM_BASE_STRINGREF_HPP
