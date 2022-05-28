/**
* @file    Tools.h
* @brief   �֗��֐�
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include<string>

/**
* �����񂩂� wstring �^�ւ̕ϊ�
*
* @param str [����] ��������̕�����ł���K�v������܂��B
*					null �w��͑z�肵�Ă��Ȃ��B
*/
std::wstring ToWstring(std::string_view str) noexcept;

/**
* wstring �^���� string �^�ւ̕ϊ�
*
* @param str [����] ��������̕�����ł���K�v������܂��B
*					null �w��͑z�肵�Ă��Ȃ��B
*/
std::string ToString(std::wstring_view str) noexcept;

/**
* �p�X����g���q�擾
*
* @param filePath [����] ��������̃t�@�C�����ł���K�v������܂��B
*/
std::string GetExt(std::string_view filePath) noexcept;

/**
* �l���w��{���ɐ؂�グ����
*
* @param value [����] �����O�̒l���w�肷��K�v������܂��B
* @param multiple [����] �w�肳�ꂽ���̒l�̔{���ɒ����B0���w��͏o���Ȃ�
* @return multiple �l�� 0 �̎��A�v�Z���ꂸ value ��Ԃ�
*/
constexpr int AdjustToMultiples(int value, int multiple) noexcept
{
	// 0 ���Z�h�~�̂���
	if (multiple == 0)
		return value;

	const int excess = value % multiple;

	// ���ɒ����ς݂̒l���w�肳�ꂽ�ꍇ�A
	// �l���傫���Ȃ��肪���������ߒ����ς݂��ŏ����𕪂��Ă���
	if (excess == 0)
	{
		return value;
	}
	else
	{
		return value + multiple - excess;
	}
}