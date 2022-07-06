/**
* @file    MyGui.h
* @brief   gui�Ǘ��N���X
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


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

	typedef Function<void()> Widget;

	/**
	* GUI�`�掞�ɏ�������鏈���̒ǉ�
	* @param widget [����] �ǉ���������֐����w��B
	*					   null�w���z�肵�Ă��Ȃ��B
	*/
	void AddWidget(Widget&& widget) noexcept;

private:

	// * imgui�p�`�� function �֐��z��
	Vector<Widget> m_widgets;
};