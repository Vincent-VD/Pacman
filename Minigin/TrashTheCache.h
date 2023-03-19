#pragma once
#include <chrono>

#include "MiniginPCH.h"

namespace TrashTheCache
{

	struct Transform
	{
		float matrix[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
		};
	};

	class GameObject3D
	{
	public:
		Transform transform{};
		int id{ 5 };
	};

	class GameObject3DAlt
	{
	public:
		Transform* transform{};
		int id{ 5 };
	};

	inline auto Exercise1(const int iterations)
	{
		std::vector<float> res(11);
		std::vector<int> array(100'000'000);
		int entry{ 0 };
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			long long avgTime{};
			for (int sample = 0; sample < iterations; ++sample)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int iter = 0; iter < array.size(); iter += stepsize)
				{
					array[iter]*= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
				avgTime += elapsedTime;
				avgTime /= static_cast<long long>(2.f);
			}
			res[entry] = static_cast<float>(avgTime);
			++entry;
		}
		return res;
	}

	template<typename Type>
	inline auto Exercise2(const int iterations)
	{
		std::vector<float> res(11);
		std::vector<Type> array(100'000'000);
		int entry{ 0 };
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			long long avgTime{};
			for (int sample = 0; sample < iterations; ++sample)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int iter = 0; iter < array.size(); iter += stepsize)
				{
					array[iter].id *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
				avgTime += elapsedTime;
				avgTime /= static_cast<long long>(2.f);
			}
			res[entry] = static_cast<float>(avgTime);
			++entry;
		}
		return res;
	}
	
}

