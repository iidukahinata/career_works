/**
* @file    MyGui.h
* @brief   gui�Ǘ��N���X
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <functional>
#include "SubSystem/Core/Common/Macro.h"

class MyGui
{
	MyGui() = default;
	COPY_PROHIBITED(MyGui);
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