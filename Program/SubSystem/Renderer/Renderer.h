/**
* @file	   Renderer.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "LightMap.h"
#include "SubSystem/Core/ISubsystem.h"

class Light;
class Camera;
class RenderObject;
class PostProcessEffect;

/**
* Renderer���ۃN���X
* ���̃N���X�ł̓C���^�[�t�F�[�X�݂̂������B
* �h���N���X�ŏ��������̊֐�����������B
*/
class Renderer : public ISubsystem
{
	SUB_CLASS(Renderer)
public:

	virtual bool Initialize() override { return true; }
	virtual void Shutdown() override {}

	/** Light ���\�b�h */
	void AddLight(Light* light) noexcept;
	void RemoveLight(Light* light) noexcept;

	/** Camera ���\�b�h */
	void AddCamera(Camera* camera) noexcept;
	void RemoveCamera(Camera* camera) noexcept;
	Camera* GetMainCamera() const noexcept;

	/** Render Object ���\�b�h */
	void AddRenderObject(RenderObject* rederObject) noexcept;
	void RemoveRenderObject(RenderObject* rederObject) noexcept;

	/** Post Process Effect ���\�b�h */
	void RegisterPostProcess(PostProcessEffect* postProcess) noexcept;
	void OnRegisterPostProcess(PostProcessEffect* postProcess) noexcept;

protected:

	// * ���C�g�Ǘ��̂��߂̃}�b�v�N���X
	UniquePtr<LightMap> m_lightMap;

	// * Scene�ɐݒu���ꂽ�`��I�u�W�F�N�g�z��B
	Set<RenderObject*> m_renderObjects;

	Camera* m_mainCamera = nullptr;

	// * �z��ɂ���̂͌�Ƀ��C���[�Ȃǂ�UI�Ȃǂ̕`��𐧌䂳���Ă������߁B
	Set<Camera*> m_cameras;

	PostProcessEffect* m_postProcessEffect = nullptr;
};