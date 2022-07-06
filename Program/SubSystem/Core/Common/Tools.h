/**
* @file    Tools.h
* @brief   便利関数
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "TypeDef.h"

/**
* 文字列から wstring 型への変換
*
* @param str [入力] 何かしらの文字列である必要があります。
*					null 指定は想定していない。
*/
Wstring ToWstring(String_View str) noexcept;

/**
* wstring 型から string 型への変換
*
* @param str [入力] 何かしらの文字列である必要があります。
*					null 指定は想定していない。
*/
String ToString(Wstring_View str) noexcept;

/**
* パスから拡張子取得
*
* @param filePath [入力] 何かしらのファイル名である必要があります。
*/
String GetExt(String_View filePath) noexcept;

/**
* 値を指定倍数に切り上げ調整
*
* @param value [入力] 調整前の値を指定する必要があります。
* @param multiple [入力] 指定されたこの値の倍数に調整。0を指定は出来ない
* @return multiple 値が 0 の時、計算されず value を返す
*/
constexpr int AdjustToMultiples(int value, int multiple) noexcept
{
	// 0 除算防止のため
	if (multiple == 0)
		return value;

	const int excess = value % multiple;

	// 既に調整済みの値が指定された場合、
	// 値が大きくなる問題があったため調整済みかで処理を分けている
	if (excess == 0)
	{
		return value;
	}
	else
	{
		return value + multiple - excess;
	}
}