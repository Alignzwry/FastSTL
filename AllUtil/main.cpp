#include <vector>
#include "vector.h"
#include <Windows.h>
#include <iostream>
#include <chrono>

int main() {
	// Test performance
	std::vector<int> vec1 = { 0, 0, 0, 0, 100, 0 };
	vector<int> vec2 = { 100, 14234, 123, 5342, 123, 531 };

	long long vec1_time = 0;
	long long vec2_time = 0;

	float ratio = 0.f;

	// First test
	std::cout << "Incrementing: " << std::endl;

	auto start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 50000000; i++) {
		for (auto& v : vec1) {
			v++;
		}
	}
	vec1_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "1. std::vector: " << vec1_time / 1000000 << " ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 50000000; i++) {
		for (auto& v : vec1) {
			v++;
		}
	}
	vec2_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "2. vector: " << vec2_time / 1000000 << " ms" << std::endl;

	ratio = vec1_time / vec2_time;

	// Second test
	std::cout << "\nCopying: " << std::endl;
	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		auto ret = vec1;
	}
	vec1_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "1. std::vector: " << vec1_time / 1000000 << " ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		auto ret = vec2;
	}
	vec2_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "2. vector: " << vec2_time / 1000000 << " ms" << std::endl;

	ratio += vec1_time / vec2_time;

	// Third test
	std::cout << "\nPushing and popping: " << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		vec1.push_back(10);
		vec1.pop_back();
	}
	vec1_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "1. std::vector: " << vec1_time / 1000000 << " ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {
		vec2.push_back(10);
		vec2.pop_back();
	}
	vec2_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "2. vector: " << vec2_time / 1000000 << " ms" << std::endl;

	ratio += vec1_time / vec2_time;

	// Fourth test
	std::cout << "\nErasing: " << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 2000000; i++) {
		vec1.push_back(10);
		vec1.erase(vec1.end()- 1);
	}
	vec1_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "1. std::vector: " << vec1_time / 1000000 << " ms" << std::endl;

	start_time = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 2000000; i++) {
		vec2.erase(vec2.size() - 1);
		vec2.push_back(10);
	}
	vec2_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	std::cout << "2. vector: " << vec2_time / 1000000 << " ms" << std::endl;

	ratio += vec1_time / vec2_time;

	std::cout << "\nAvarage Ratio: " << ratio / 4 * 100 << "%" << std::endl;

	std::cout << "\nAllocated Memory: std::vector = " << vec1.capacity() << ", vector = " << vec2.capacity() << std::endl;
}