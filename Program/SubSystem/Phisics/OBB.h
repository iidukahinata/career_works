#pragma once

#include "SubSystem/Math/MathCore.h"

class OBB
{
public:

	/* Axis�͐��K�����ꂽ���̂Ƃ���*/
	bool Collision(const OBB& obb)
	{
		Math::Vector3 separation;
		Math::Vector3 distance = m_center - obb.m_center;

		// this ��3���𕪗����Ƃ��ă`�F�b�N
		for (int i = 0; i < 3; ++i)
		{
			separation = m_axis[i];
			if (!DrawTheSeparationAxis(obb, obb, separation, distance))
			{
				return false;
			}
		}

		// other ��3���𕪗����Ƃ��ă`�F�b�N
		for (int i = 0; i < 3; ++i)
		{
			separation = obb.m_axis[i];
			if (!DrawTheSeparationAxis(*this, obb, separation, distance))
			{
				return false;
			}
		}

		// �O�ς𕪗����Ƃ��ă`�F�b�N
		for (int p1 = 0; p1 < 3; ++p1)
		{
			for (int p2 = 0; p2 < 3; ++p2)
			{
				separation = Math::Vector3::Cross(m_axis[p1], obb.m_axis[p2]);
				separation.Normalize();
				if (!DrawTheSeparationAxis(*this, obb, separation, distance))
				{
					return false;
				}
			}
		}
		return true;
	}

	// �_�Ƃ̍ŒZ�������擾
	float GetSqrShortestDistance(const Math::Vector3 point)
	{
		Math::Vector3 v;
		auto dis = point - m_center;
		for (int i = 0; i < 3; ++i)
		{
			float s = fabs(Math::Vector3::Dot(dis, m_axis[i]) / m_size[i]);
			if (s > 1.f) {
				v += (m_axis[i] * m_size[i] * (1.f - s));
			}
		}
		return v.GetSquaredLength();
	}

private:

	// �������������邩���ׂ�
	bool DrawTheSeparationAxis(
		const OBB& obbA,
		const OBB& obbB,
		const Math::Vector3& separation,
		const Math::Vector3& distance)
	{
		float dis = distance.Dot(separation);

		float shadowA = 0;
		shadowA += fabs(separation.Dot(obbA.m_axis[0] * obbA.m_size[0]));
		shadowA += fabs(separation.Dot(obbA.m_axis[1] * obbA.m_size[1]));
		shadowA += fabs(separation.Dot(obbA.m_axis[2] * obbA.m_size[2]));

		float shadowB = 0;
		shadowB += fabs(separation.Dot(obbB.m_axis[0] * obbB.m_size[0]));
		shadowB += fabs(separation.Dot(obbB.m_axis[1] * obbB.m_size[1]));
		shadowB += fabs(separation.Dot(obbB.m_axis[2] * obbB.m_size[2]));

		if (dis > shadowA + shadowB)
		{
			return false;
		}
		return true;
	}

private:

	Math::Vector3 m_center;

	// * �P�ʃx�N�g���̕���������
	Math::Vector3 m_axis[3];


	Math::Vector3 m_size;
};