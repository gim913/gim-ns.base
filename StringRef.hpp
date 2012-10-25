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
		typedef StringPool_<T> MyStringPool;
		typedef StringRef_<T> MyStringRef;
	public:
		StringPool_() : m_currentOffset(0) {}

		// return 'id' of added element
		size_t push_back(const MyStringRef& stringRef) {
			const uint8_t* b = reinterpret_cast<const uint8_t*>( stringRef.begin() );
			const uint8_t* e = reinterpret_cast<const uint8_t*>( stringRef.end() );
			m_memory.insert(m_memory.end(), b, e);

			printf("%2d %ws\n", m_currentOffset, b);
			m_entries.push_back(StringPoolEntry(m_currentOffset, (e-b)));
			m_currentOffset += (e-b);

			return m_entries.size()-1;
		}

		struct EntriesIterator;
		typedef EntriesIterator iterator;
		iterator begin() {
			return iterator(*this, m_entries.begin());
		}
		iterator end() {
			return iterator(*this, m_entries.end());
		}
	private:
		struct StringPoolEntry {
			StringPoolEntry() : offset(0), size(0) {}
			StringPoolEntry(size_t a_offset, size_t a_size) : offset(a_offset), size(a_size) {}
			size_t offset;
			size_t size;
		};
		struct EntriesIterator {
			typedef typename std::vector<StringPoolEntry>::iterator It;
			EntriesIterator(MyStringPool& a_pool, It a_it) : pool(a_pool), it(a_it) {}
			bool operator==(const EntriesIterator& rhs) {
				return ((&pool == &(rhs.pool)) && (it == rhs.it));
			}
			bool operator!=(const EntriesIterator& rhs) {
				return !(*this == rhs);
			}

			MyStringRef operator*() {
				printf ("%d\n", (*it).offset);
				const T* ptr = reinterpret_cast<const T*>( &(pool.m_memory[(*it).offset]) );
				size_t len = (*it).size / sizeof(T)  - 1;
				return MyStringRef(ptr, len);
			}

			EntriesIterator& operator++() {
				++it;
				return *this;
			}
			MyStringPool& pool;
			It it;
		};
		size_t m_currentOffset;
		std::vector<uint8_t> m_memory;
		std::vector<StringPoolEntry> m_entries;
	};
}

namespace gim {
	typedef StringRef_<char>     StringRef;
	typedef StringRef_<wchar_t>  WStringRef;
	typedef StringPool_<char>    StringPool;
	typedef StringPool_<wchar_t> WStringPool;
}

#endif // GIM_BASE_STRINGREF_HPP
