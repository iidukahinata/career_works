/**
* @file    Chack.h
* @brief
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
* @note
*  �f�o�b�O���[�h�ł̋N�����̂݃��O�o��
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