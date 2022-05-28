/**
* @file    Chack.h
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
* @note
*  デバッグモードでの起動時のみログ出力
*  assert 処理だけでは分からない部分を追記出来るようにするために作成。
*  どのような実装ならバグの修正に役立つか瞑想中。
*/
#pragma once


#include <corecrt.h>

#ifdef _DEBUG
void chack(const char* message, const char* file, unsigned line, const char* text);

#define Chack(expr)  if(!(expr)) { chack(#expr, __FILE__, __LINE__, ""); }
#define ChackF(expr, text)  if(!(expr)) { chack(#expr, __FILE__, __LINE__, text); }

#else
#define Chack(expr)
#define ChackF(expr, text)
#endif // _DEBUG