#pragma once


#include <set>
#include <map>
#include <list>
#include <array>
#include <string>
#include <vector>
#include <stdint.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "Memory.h"

using String = std::string;
using String_View = std::string_view;

using Wstring = std::wstring;
using Wstring_View = std::wstring_view;

template<class T>
using List = std::list<T>;

template<class T, size_t Size>
using Array = std::array<T, Size>;

template<class ...Args>
using Vector = std::vector<Args...>;

template<class T, class U>
using Map = std::map<T, U>;

template<class T, class U>
using Unordered_Map = std::unordered_map<T, U>;

template<class T>
using Set = std::set<T>;

template<class T>
using Unordered_Set = std::unordered_set<T>;

template<class T>
using Function = std::function<T>;