/**
* @file    MyGui.h
* @brief   gui�Ǘ��N���X
*
* @date	   2022/07/19 2022�N�x����
*/
#pragma once


class Widget;

class EditerSystem
{
	EditerSystem() = default;
	COPY_PROHIBITED(EditerSystem);
public:

	static EditerSystem& Get() noexcept
	{
		static EditerSystem instance;
		return instance;
	}

	void Initialize();
	void Draw();
	void Exit();
	void Clear();

	/**
	* GUI�`�掞�ɏ�������鏈���̒ǉ�
	* @param widget [����] �ǉ���������֐����w��B
	*/
	void RegisterWidget(Widget* widget) noexcept;

	void RemoveWidget(Widget* widget) noexcept;

private:

	// * Gui �p�`��N���X�z��
	Set<Widget*> m_widgets;
};