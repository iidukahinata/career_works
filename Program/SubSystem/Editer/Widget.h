/**
* @file		Widget.h
* @brief
*
* @date		2022/07/19 2022年度初版
*/
#pragma once


/**
* 他のJobSystemなどのクラスと共通的なアクセス、使用方法にすることと、各Widgetの汎用性を高めるため
* 今回は std::function クラスを使用した実装にする。
*/
class Widget
{
	typedef std::function<void()> Task;
public:

	Widget() = default;
	Widget(Task&& task) noexcept;

	~Widget();

	/** Widget の描画処理 */
	void Draw();

	/** EditerSystem で実行される関数 function を設定 */
	void SetFunction(Task&& task) noexcept;

	/** 更新処理を行うためには、一度実行しなければならない。*/
	void RegisterToEditerSystem() noexcept;

	/** EditerSystem に登録した場合、呼び出す必要があります。*/
	void UnRegisterFromEditerSystem() noexcept;

	bool IsRegistered() const noexcept;

private:

	bool m_isRegistered = false;

	// * EditerSystem セット後実行させる関数
	Task m_task;
};