#pragma once
#include <initializer_list>
#include <assert.h>
#include <new>  // For placement new
#include "global.h"

#if defined(_MSC_VER)
#define FINLINE __forceinline
#else
#define FINLINE inline constexpr
#endif // MSVC

FSTL_BEGIN
#define DEFAULT_SIZE 4

#define _alloc(size) { \
	this->m_pData = (T*)calloc(size, sizeof(T)); \
	this->m_iAllocated = size; \
	assert(this->m_pData != nullptr); \
}

#define _free() { \
	for (int i = 0; i < m_iSize; ++i) { \
		m_pData[i].~T(); \
	} \
	free(this->m_pData); \
}

#define calcGrowth { \
    const int temp = this->m_iAllocated + this->m_iAllocated / 2; \
    if (temp < this->m_iAllocated + 1) \
        this->m_iAllocated++; \
	else \
        this->m_iAllocated = temp; \
}

#define _realloc() { \
    T* oldData = this->m_pData; \
    calcGrowth; \
    _alloc(this->m_iAllocated); \
    \
    for (int i = 0; i < this->m_iSize; ++i) { \
        new (&this->m_pData[i]) T(std::move(oldData[i])); \
        oldData[i].~T(); \
    } \
    \
    free(oldData); \
}

template <typename T>
class vector {
public:
	// Constructors
	vector() {
		_alloc(DEFAULT_SIZE)
	}

	~vector() {
		_free();
	}

	vector(int size) {
		_alloc(size);
	}

	vector(const vector<T>& v) {
		this->m_iAllocated = v.capacity();
		this->m_iSize = v.size();
		_alloc(this->m_iAllocated);
		for (int i = 0; i < m_iSize; ++i) {
			new (&this->m_pData[i]) T(v.m_pData[i]);
		}
	}

	vector(std::initializer_list<T> list) {
		this->m_iAllocated = list.size();
		this->m_iSize = list.size();
		_alloc(this->m_iAllocated);

		int index = 0;
		for (const T& item : list) {
			new (&this->m_pData[index++]) T(item);
		}
	}

	// Operators
	__forceinline vector& operator =(const vector<T>& v) {
		if (this != &v) {
			_free();
			this->m_iAllocated = v.capacity();
			this->m_iSize = v.size();
			_alloc(this->m_iAllocated);
			for (int i = 0; i < m_iSize; ++i) {
				new (&this->m_pData[i]) T(v.m_pData[i]);
			}
		}
		return *this;
	}

	__forceinline T& operator[](int index) {
		assert(index >= 0 && index < this->m_iSize);
		return this->m_pData[index];
	}
	__forceinline const T& operator[](int index) const {
		assert(index >= 0 && index < this->m_iSize);
		return this->m_pData[index];
	}

	__forceinline bool operator==(const vector<T>& v) const {
		if (this->m_iSize != v.size())
			return false;

		for (int i = 0; i < this->m_iSize; i++) {
			if (!(this->m_pData[i] == v[i])) {
				return false;
			}
		}
		return true;
	}

	// Functions
	__forceinline void resize(int size) {
		T* oldData = this->m_pData;
		_alloc(size);
		int minSize = (this->m_iSize < size) ? this->m_iSize : size;
		for (int i = 0; i < minSize; ++i) {
			new (&this->m_pData[i]) T(std::move(oldData[i]));
			oldData[i].~T();
		}
		free(oldData);
		for (int i = this->m_iSize; i < size; ++i) {
			new (&this->m_pData[i]) T();
		}

		this->m_iSize = size;
	}

	__forceinline void reserve(int size) {
		assert(size > this->m_iSize);

		T* oldData = this->m_pData;
		_alloc(size);

		for (int i = 0; i < this->m_iSize; ++i) {
			new (&this->m_pData[i]) T(std::move(oldData[i]));
			oldData[i].~T();
		}

		free(oldData);
		this->m_iAllocated = size;
	}

	__forceinline T& at(int index) {
		assert(index >= 0 && index < this->m_iSize);
		return this->m_pData[index];
	}

	__forceinline const T& at(int index) const {
		assert(index >= 0 && index < this->m_iSize);
		return this->m_pData[index];
	}

	__forceinline void push_back(const T& item) {
		if (this->m_iSize == this->m_iAllocated) {
			_realloc();
		}
		new (&this->m_pData[this->m_iSize++]) T(item);
	}

	__forceinline void pop_back() {
		assert(m_iSize > 0);
		m_pData[--m_iSize].~T();
	}

	__forceinline void clear() {
		for (int i = 0; i < m_iSize; ++i) {
			m_pData[i].~T();
		}
		this->m_iSize = 0;
	}

	__forceinline void erase(int index) {
		assert(index >= 0 && index < this->m_iSize);
		this->m_pData[index].~T();
		for (int i = index; i < this->m_iSize - 1; ++i) {
			this->m_pData[i] = std::move(this->m_pData[i + 1]);
			this->m_pData[i + 1].~T();
		}
		this->m_iSize--;
	}

	__forceinline void fix_size() {
		T* old_data = this->m_pData;
		_alloc(this->m_iSize);
		for (int i = 0; i < this->m_iSize; ++i) {
			new (&this->m_pData[i]) T(old_data[i]);
			old_data[i].~T();
		}
		free(old_data);
	}

	// Global functions
	__forceinline T* data() const {
		return this->m_pData;
	}

	__forceinline int size() const {
		return this->m_iSize;
	}

	__forceinline int capacity() const {
		return this->m_iAllocated;
	}

	__forceinline bool empty() const {
		return this->m_iSize == 0;
	}

	// Other
	__forceinline T* begin() const {
		return m_pData;
	}

	__forceinline T* end() const {
		return m_pData + m_iSize;
	}

private:
	T* m_pData = nullptr;
	int m_iSize = 0;
	int m_iAllocated = 0;
};
FSTL_END