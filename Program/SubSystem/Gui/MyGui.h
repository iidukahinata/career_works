/**
* @file    MyGui.h
* @brief   gui�Ǘ��N���X
*
* @date	   2022/04/29 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <functional>

/**
* �f�o�b�O���[�h���̂ݗL���B
* �����[�X���[�h���͊֐����������s���Ȃ��悤�ɂȂ��Ă���B
*/
class MyGui
{
private:

	MyGui() = default;
	MyGui(const MyGui&) = default;
	MyGui& operator=(const MyGui&) = default;

public:

	static MyGui& Get() noexcept
	{
		static MyGui instance;
		return instance;
	}

	void Init();
	void Draw();
	void Exit();
	void Clear();

	typedef std::function<void()> Widget;

	/**
	* GUI�`�掞�ɏ�������鏈���̒ǉ�
	* @param widget [����] �ǉ���������֐����w��B
	*					   null�w���z�肵�Ă��Ȃ��B
	*/
	void AddWidget(Widget&& widget) noexcept;

private:

	// * imgui�p�`�� function �֐��z��
	std::vector<Widget> m_widgets;
};