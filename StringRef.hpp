/**
 * @file StringRef.hpp
 * @author Michal 'GiM' Spadlinski <gim913@gmail.com>
 *
 * 
 */

#pragma once
#ifndef GIM_BASE_STRINGREF_HPP
#define GIM_BASE_STRINGREF_HPP

#include <vector>
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
		StringRef_(const T* cString, size_t cStringLen = 0) : m_ptr(cString), m_len(cStringLen) {
			if (!m_len) {
				m_len = stringLen(cString);
			}
			m_len += 1;
		}

		StringRef_(const StringRef_& oth) : m_ptr(oth.m_ptr), m_len(oth.m_len) {
		}

		// length of a string without terminating null
		size_t length() const {
			return m_len-1;
		}

		size_t size() const {
			return m_len*sizeof(T);
		}

		typedef const T* iterator;
		iterator begin() const {
			return m_ptr;
		}

		// returns iterator, that points "past" terminating null
		iterator end() const {
			return m_ptr+m_len;
		}
	private:
		const T* m_ptr;
		size_t m_len;
	};

	template <class T>
	class StringPool_
	{
		StringPool_(const StringPool_&);             // you definitely neither do want a copy
		StringPool_& operator=(const StringPool_&);  // nor assignemnt ;p
		typedef StringRef_<T> StringRef;
	public:
		StringPool_() : m_offset(0) {}

		// return 'id' of added element
		size_t push_back(const StringRef& stringRef) {
			const uint8_t* b = reinterpret_cast<const uint8_t*>( stringRef.begin() );
			const uint8_t* e = reinterpret_cast<const uint8_t*>( stringRef.end() );
			m_memory.insert(m_memory.end(), b, e);

			m_offset.push_back(m_currentOffset);
			m_currentOffset += (e-b);

			return m_offset.size()-1;
		}

	private:
		size_t m_currentOffset;
		std::vector<uint8_t> m_memory;
		std::vector<size_t> m_offset;
	};
}

namespace gim {
	typedef StringRef_<char>     StringRef;
	typedef StringRef_<wchar_t>  WStringRef;
	typedef StringPool_<char>    StringPool;
	typedef StringPool_<wchar_t> WStringPool;
}

#endif // GIM_BASE_STRINGREF_HPP
