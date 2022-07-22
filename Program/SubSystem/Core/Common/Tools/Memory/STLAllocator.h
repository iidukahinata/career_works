#pragma once


#include "Memory.h"

template<class T>
class myallocator {

public:

	using _From_primary = myallocator;

	using value_type = T;

	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using propagate_on_container_move_assignment = std::true_type;

	myallocator() { }
	myallocator(const myallocator& x) { }
	template<class U>
	myallocator(const myallocator<U>& x) { }

	T* allocate(size_t n) {
		return static_cast<T*>(std::malloc(n * sizeof(T)));
		//return static_cast<T*>(Memory::Malloc(n * sizeof(T)));
	}

	void deallocate(T* ptr, size_t n) {
		std::free(ptr);
		//Memory::Free(ptr);
	}
};