/**
* @file    Chack.h
* @brief
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
* @note
*  �f�o�b�O���[�h�ł̋N�����̂݃��O�o��
*  assert ���������ł͕�����Ȃ�������ǋL�o����悤�ɂ��邽�߂ɍ쐬�B
*  �ǂ̂悤�Ȏ����Ȃ�o�O�̏C���ɖ𗧂��ґz���B
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