/**
* @file		Widget.h
* @brief
*
* @date		2022/07/19 2022�N�x����
*/
#pragma once


/**
* ����JobSystem�Ȃǂ̃N���X�Ƌ��ʓI�ȃA�N�Z�X�A�g�p���@�ɂ��邱�ƂƁA�eWidget�̔ėp�������߂邽��
* ����� std::function �N���X���g�p���������ɂ���B
*/
class Widget
{
	typedef std::function<void()> Task;
public:

	Widget() = default;
	Widget(Task&& task) noexcept;

	~Widget();

	/** Widget �̕`�揈�� */
	void Draw();

	/** EditerSystem �Ŏ��s�����֐� function ��ݒ� */
	void SetFunction(Task&& task) noexcept;

	/** �X�V�������s�����߂ɂ́A��x���s���Ȃ���΂Ȃ�Ȃ��B*/
	void RegisterToEditerSystem() noexcept;

	/** EditerSystem �ɓo�^�����ꍇ�A�Ăяo���K�v������܂��B*/
	void UnRegisterFromEditerSystem() noexcept;

	bool IsRegistered() const noexcept;

private:

	bool m_isRegistered = false;

	// * EditerSystem �Z�b�g����s������֐�
	Task m_task;
};