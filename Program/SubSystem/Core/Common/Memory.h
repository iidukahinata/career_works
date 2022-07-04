#pragma once


#include "Macro.h"

void* Malloc(uint32_t size) noexcept;
void Free(void* ptr) noexcept;

template<class T, class ...Args>
T* NewObject(Args... args)
{
	void* ptr = Malloc(sizeof(T));
	return new (ptr) T(args...);
}

template<class T>
void DeleteObject(T* ptr)
{
	ptr->~T();
	Free(ptr);
}

template<class T>
class UniquePtr
{
	COPY_PROHIBITED(UniquePtr)
public:

	UniquePtr() : m_data(nullptr) {}
	UniquePtr(T* ptr) : m_data(ptr) {}

	~UniquePtr() noexcept
	{
		Reset();
	}

	UniquePtr<T>& operator=(UniquePtr<T>&& uptr) noexcept
	{
		Reset(uptr.Release());
		return *this;
	}

	UniquePtr<T>& operator=(nullptr_t) noexcept
	{
		Reset();
		return *this;
	}

	T& operator*() const noexcept
	{
		return *m_data;
	}

	T* operator->() const noexcept
	{
		return m_data;
	}

	T* Get() const noexcept
	{
		return m_data;
	}

	explicit operator bool() const noexcept 
	{
		return (!!m_data);
	}

	void Reset(T* ptr = nullptr) noexcept
	{
		if (m_data)
		{
			FreeObject(m_data);
		}

		m_data = ptr;
	}

	T* Release() noexcept
	{
		T* ptr = m_data;
		m_data = nullptr;
		return ptr;
	}

private:

	T* m_data;
};

template<class T, class ...Args>
UniquePtr<T> MakeUnique(Args... args) noexcept
{
	return UniquePtr<T>(NewObject<T>(args...));
}