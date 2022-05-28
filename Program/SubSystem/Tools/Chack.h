/**
* @file    Chack.h
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
* @note
*  デバッグモードでの起動時のみログ出力
*/
#pragma once


#include <assert.h>

#ifdef _DEBUG

void chack(const char* text, const wchar_t* file, unsigned line);

#define Chack(Expression)  assert(Expression)
#define Chack(isTrue, text)  if(!isTrue) { chack(text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)); }

#else
#define Chack(Expression)
#define Chack(isTrue, text)
#endif // _DEBUG