#include <iostream>

using namespace std;

template <typename T>
struct Vector2 {
	T x, y;
};

template <typename T>
struct Vector3 {
	T x, y, z;
};

template <typename T>
int Solve2E1D(Vector3<T> p, Vector3<T> q, Vector2<T>* res)
{
	T abc = p.x * p.y * p.z;
	T def = q.x * q.y * q.z;

	if (abc != 0 && def != 0) {
		T ar = p.x / q.x;
		T br = p.y / q.y;
		T cr = p.z / q.z;

		if (ar == br)
			return br != cr ? 0 : 1;

		(*res).x = (p.y * q.z - q.y * p.z) / (p.y * q.x - q.y * p.x);
		(*res).y = (p.x * -(*res).x + p.z) / p.y;

		return 2;
	}

	return 0;
}

int main()
{
	int m_case = 0;
	Vector2<float> res;
	Vector3<float> e1, e2;

	cout << "(a, b, c) = ";
	cin >> e1.x >> e1.y >> e1.z;

	cout << "(d, e, f) = ";
	cin >> e2.x >> e2.y >> e2.z;

	m_case = Solve2E1D(e1, e2, &res);

	switch (m_case) {
		case 0:
			cout << "Vo nghiem" << endl;
			break;

		case 1:
			cout << "Vo so nghiem" << endl;
			break;

		case 2:
			cout << "(x, y) = (" << res.x << "," << res.y << ")" << endl;
			break;
	}

	return 0;
}