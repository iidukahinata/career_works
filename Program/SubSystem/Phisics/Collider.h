#pragma once

#include <DirectXMath.h>

class Collider
{

public:
	static bool Test(Collider* c1, Collider* c2);

	void Update(); // �p�����[�^�̍X�V

	// ���^�C�v��Collider�C���X�^���X�𐶐�����
	static Collider* CreateSphere(
		class IGameObject* pOwner, DirectX::XMFLOAT3 centerPos, float radius);

	// ����Collider��������������\���ϐ�
	enum TYPE {
		SPHERE, // ��
		LINE,
	};

	TYPE mType;

	// ���L��GameObject�̃|�C���^
	class IGameObject* mOwner;

	// ���̏ꍇ�ɕK�v�ȕϐ�
	DirectX::XMVECTOR centerPos; // ���S�_���W
	float radius; // ���a

};

