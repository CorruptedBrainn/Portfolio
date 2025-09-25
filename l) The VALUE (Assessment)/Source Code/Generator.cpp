/// Name: Generator.cpp
/// Version: 0.0.3-alpha
/// Description: The function implementations of all my generation scripts
/// Author: Nicolas Martens

#include "Generator.h"

static std::queue<wchar_t*> dump;

static int fakes(std::mt19937& gen, std::uniform_int_distribution<int>& dist, int& ans) {
	int ret = dist(gen);
	while (ret == ans) ret = dist(gen);
	return ret;
}

static std::vector<int> fakes(std::mt19937& gen, std::uniform_int_distribution<int>& dist, std::vector<int>& ans) {
	std::vector<int> ret(ans.size());
	do {
		for (int i = 0; i < ret.size(); i++) ret[i] = dist(gen);
		std::sort(ret.begin(), ret.end());
	} while (ret == ans);
	return ret;
}

static int factorial(int n) {
	int ret = 1;
	for (int i = 1; i <= n; i++) ret *= i;
	return ret;
}

static question arithmetic(std::mt19937& gen, int diff, int range) {
	std::uniform_int_distribution<int> op(1, range);
	int operation = op(gen);

	switch (operation) {
	case 1:
	{
		std::uniform_int_distribution<int> genab(-std::pow(10, diff + 1), std::pow(10, diff + 1));
		int a = genab(gen), b = genab(gen);
		int c = a + b;
		int A = fakes(gen, genab, c), B = fakes(gen, genab, c), C = fakes(gen, genab, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L" + " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0};
	}
	case 2:
	{
		std::uniform_int_distribution<int> genbc(-std::pow(10, diff + 1), std::pow(10, diff + 1));
		int b = genbc(gen), c = genbc(gen);
		int a = b + c;
		int A = fakes(gen, genbc, c), B = fakes(gen, genbc, c), C = fakes(gen, genbc, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L" - " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 3:
	{
		std::uniform_int_distribution<int> genab(-std::pow(5, diff + 1), std::pow(5, diff + 1));
		int a = genab(gen), b = genab(gen);
		int c = a * b;
		int A = fakes(gen, genab, c), B = fakes(gen, genab, c), C = fakes(gen, genab, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L" * " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 4:
	{
		std::uniform_int_distribution<int> genbc(-std::pow(5, diff + 1), std::pow(5, diff + 1));
		int b = genbc(gen), c = genbc(gen);
		while (b == 0) b = genbc(gen);
		int a = b * c;
		int A = fakes(gen, genbc, c), B = fakes(gen, genbc, c), C = fakes(gen, genbc, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L" / " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 5:
	{
		std::uniform_int_distribution<int> gena(0, 3 * diff);
		std::uniform_int_distribution<int> genb(0, diff);
		std::uniform_int_distribution<int> genfake(0, pow(3 * diff, diff));
		int a = gena(gen), b = genb(gen);
		int c = pow(a, b);
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L" to the power of " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 6:
	{
		std::uniform_int_distribution<int> gena(2, 3 * diff);
		std::uniform_int_distribution<int> genc(0, diff);
		int a = gena(gen), c = genc(gen);
		int b = pow(a, c);
		int A = fakes(gen, genc, c), B = fakes(gen, genc, c), C = fakes(gen, genc, c);
		std::wstring q = L"Find:\nlog base " + std::to_wstring(a) + L" of " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 7:
	{
		std::uniform_int_distribution<int> gena(-pow(100, diff + 1), pow(100, diff + 1));
		int a = gena(gen);
		int c = abs(a);
		int A = fakes(gen, gena, c), B = fakes(gen, gena, c), C = fakes(gen, gena, c);
		std::wstring q = L"Find:\n|" + std::to_wstring(a) + L"|";
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	case 8:
	{
		std::uniform_int_distribution<int> gena(0, 2 * diff);
		std::uniform_int_distribution<int> genfake(0, factorial(2 * diff));
		int a = gena(gen);
		int c = factorial(a);
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find:\n" + std::to_wstring(a) + L"!";
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 0 };
	}
	}
}

static question geometric(std::mt19937& gen, int diff, int range) {
	std::uniform_int_distribution<int> ty(1, range);
	int type = ty(gen);

	switch (type) {
	case 1:
	{
		std::uniform_int_distribution<int> genn(3, 9);
		int n = genn(gen), c = 0;
		std::uniform_int_distribution<int> genai(1, pow(12 - n, diff));
		std::uniform_int_distribution<int> genfake(n, n * pow(12 - n, diff));
		std::vector<int> a;
		for (int i = 0; i < n; i++) {
			int ai = genai(gen);
			a.push_back(ai);
			c += ai;
		}
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find the perimiter of a shape with sides of length:\n" + std::to_wstring(a[0]);
		for (int i = 1; i < n; i++) q += L", " + std::to_wstring(a[i]);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 1 };
	}
	case 2:
	{
		std::uniform_int_distribution<int> gena(2, 10);
		std::uniform_int_distribution<int> genb(1, pow(4, diff));
		std::uniform_int_distribution<int> genfake(10, 10 * pow(4, diff));
		int b = genb(gen), a = gena(gen) * b;
		int c = 2 * a / b + 2 * b;
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find the perimiter of a rectangle with:\nArea " + std::to_wstring(a) + L" and height " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 1 };
	}
	case 3:
	{
		std::uniform_int_distribution<int> genab(1, pow(3, diff));
		std::uniform_int_distribution<int> genfake(2 * diff, pow(3, 2 * diff));
		int a = genab(gen), b = genab(gen);
		while (a * b % 2 != 0) a = genab(gen);
		int c = a * b / 2;
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find the area of a triangle with dimensions:\n" + std::to_wstring(a) + L" by " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 1 };
	}
	case 4:
	{
		std::uniform_int_distribution<int> genab(1, pow(3, diff));
		std::uniform_int_distribution<int> genfake(1, pow(3, 2 * diff));
		int a = genab(gen), b = genab(gen);
		int c = a * b;
		int A = fakes(gen, genfake, c), B = fakes(gen, genfake, c), C = fakes(gen, genfake, c);
		std::wstring q = L"Find the area of a rectangle with dimensions:\n" + std::to_wstring(a) + L" by " + std::to_wstring(b);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 1 };
	}
	case 5:
	{
		std::uniform_int_distribution<int> genn(diff, 4 * diff);
		int n = genn(gen);
		std::uniform_int_distribution<int> genc(1, 179 * n - 360);
		std::vector<int> a(n - 1, 1);
		int c = genc(gen);
		int sum = 179 * n - 359 - c;
		while (sum != 0) {
			std::uniform_int_distribution<int> genai(0, sum + 1 / 2);
			int ai = genai(gen);
			a[0] += ai;
			sum -= ai;
			std::sort(a.begin(), a.end());
		}
		std::shuffle(a.begin(), a.end(), gen);
		int A = fakes(gen, genc, c), B = fakes(gen, genc, c), C = fakes(gen, genc, c);
		std::wstring q = L"Find the final interior angle of a " + std::to_wstring(n) + L" sided polygon with angles:\n" + std::to_wstring(a[0]);
		for (int i = 1; i < n - 1; i++) q += L", " + std::to_wstring(a[i]);
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {c}, {A}, {B}, {C}, 1 };
	}
	}
}

static question algebraic(std::mt19937& gen, int diff, int range) {
	std::uniform_int_distribution<int> ty(1, range);
	int type = ty(gen);

	switch (type) {
	case 1:
	{
		std::uniform_int_distribution<int> genax(-pow(3, diff), pow(4, diff));
		int a = genax(gen), x = genax(gen);
		int b = 0 - a * x;
		int A = fakes(gen, genax, x), B = fakes(gen, genax, x), C = fakes(gen, genax, x);
		std::wstring q = L"Solve for x:\n" + std::to_wstring(a) + L"x + " + std::to_wstring(b) + L" = 0";
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		return question{ buffer, {x}, {A}, {B}, {C}, 2 };
	}
	case 2:
	{
		std::uniform_int_distribution<int> genn(2, 2 * diff);
		int n = genn(gen);
		std::uniform_int_distribution<int> genaix(-10 * diff, 10 * diff);
		std::vector<int> x(n);
		for (int i = 0; i < n; i++) x[i] = genaix(gen);
		std::sort(x.begin(), x.end());
		std::vector<int> A = fakes(gen, genaix, x), B = fakes(gen, genaix, x), C = fakes(gen, genaix, x);
		std::shuffle(x.begin(), x.end(), gen);
		std::wstring q = L"Solve for all " + std::to_wstring(n) + L" values of x (including duplicates):\n";
		for (int i = 0; i < n; i++) q += L"(x - " + std::to_wstring(x[i]) + L")";
		std::sort(x.begin(), x.end());
		q += L" = 0";
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		question ret = { buffer, {x[0]}, {A[0]}, {B[0]}, {C[0]}, 2 };
		for (int i = 1; i < n; i++) {
			ret.answer[i] = x[i];
			ret.optionA[i] = A[i];
			ret.optionB[i] = B[i];
			ret.optionC[i] = C[i];
		}
		return ret;
	}
	case 3:
	{
		std::uniform_int_distribution<int> genn(2, 2 * diff);
		int n = genn(gen);
		std::uniform_int_distribution<int> gena(-2 * diff, 2 * diff);
		std::uniform_int_distribution<int> genbx(-2 * diff, 2 * diff);
		std::vector<int> x(1);
		x[0] = genbx(gen);
		int a = gena(gen), b = genbx(gen);
		while (a == 0) a = gena(gen);
		int c = -1 * pow(x[0] - b, n) * a;
		if (n % 2 == 0 && c != 0) x.push_back(2 * b - x[0]);
		std::sort(x.begin(), x.end());
		std::vector<int> A = fakes(gen, genbx, x), B = fakes(gen, genbx, x), C = fakes(gen, genbx, x);
		std::wstring q = L"Solve for ";
		if (x.size() == 2) q += L"both values of ";
		q += L"x:\n" + std::to_wstring(a) + L"(x - " + std::to_wstring(b) + L")^" + std::to_wstring(n) + L" + " + std::to_wstring(c) + L" = 0";
		size_t size = q.size() + 1;
		wchar_t* buffer = new wchar_t[size];
		wcscpy(buffer, q.c_str());
		dump.push(buffer);
		question ret = { buffer, {x[0]}, {A[0]}, {B[0]}, {C[0]}, 2 };
		for (int i = 1; i < x.size(); i++) {
			ret.answer[i] = x[i];
			ret.optionA[i] = A[i];
			ret.optionB[i] = B[i];
			ret.optionC[i] = C[i];
		}
		return ret;
	}
	}
}

question create(int difficulty)
{
	std::random_device seed;
	std::mt19937 generation(seed());
	std::uniform_int_distribution<int> diff(0, std::min(2, difficulty));
	int mode = diff(generation);

	switch (mode) {
	case 0:
	{
		question ret = arithmetic(generation, difficulty, difficulty >= 2 ? 8 : 4);
		return ret;
	}
	case 1:
	{
		question ret = geometric(generation, difficulty, difficulty >= 3 ? 5 : difficulty >= 2 ? 4 : 2);
		return ret;
	}
	case 2:
		question ret = algebraic(generation, difficulty, 3);
		return ret;
	}
}

int clean(int buffer)
{
	while (dump.size() > buffer) {
		delete[] dump.front();
		dump.pop();
	}
	return 0;
}