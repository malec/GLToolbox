#include <array>
#include <string>
#include <iostream>

class GLToolbox {
public:
	int main() {
		auto testCoordinates0 = randCoord(-1, 1);
		auto testCoordinates1 = randCoord(0, 1);
		printArray(translate(testCoordinates0, testCoordinates1));
		printArray(rotateX(testCoordinates0, 90));
		printArray(rotateY(testCoordinates0, 90));
		printArray(rotateZ(testCoordinates0, 90));
		printArray(scale(testCoordinates0, testCoordinates1));
		printCoords(projectPoint(testCoordinates0, myrand(0, 1)));
		std::cout << outcode({ 3,3 }) << std::endl;;
		std::cout << acceptSegment({ 0,0 }, { 3,3 }) << std::endl;
		std::cout << discardSegment({ 3,3 }, { 4,4 }) << std::endl;
		std::cout << clipSegemnt({ -2,-2 }, { 3,3 }) << std::endl;
		printArray(normalize({ 4,4,4 }));
		std::cout << dotProduct(testCoordinates0, testCoordinates1) << std::endl;
		printArray(crossProduct(testCoordinates0, testCoordinates1));
		std::cout << diffuseTerm(testCoordinates0, testCoordinates1) << std::endl;
		printArray(idealReflection(testCoordinates0, testCoordinates1));
		std::cout << specularTerm(testCoordinates0, testCoordinates1, .5) << std::endl;
	}
	static float myrand(float min, float max)
	{
		return rand() * (max - min) / RAND_MAX + min;
	}
	static std::array<float, 3> randCoord(float min, float max) {
		return { myrand(min, max), myrand(min, max), myrand(min, max) };
	}
	static std::array<float, 3> translate(std::array<float, 3> coordinates, std::array<float, 3> dCoordinates) {
		return { coordinates[0] + dCoordinates[0], coordinates[1] + dCoordinates[1], coordinates[2] + dCoordinates[2] };
	}
	static std::array<float, 3> rotateX(std::array<float, 3> coordinates, float theta) {
		float x = coordinates[0];
		float y = coordinates[1];
		float z = coordinates[2];
		return { x, y*cos(theta) - z * sin(theta), y*sin(theta) + z * cos(theta) };
	}
	static std::array<float, 3> rotateY(std::array<float, 3> coordinates, float theta) {
		float x = coordinates[0];
		float y = coordinates[1];
		float z = coordinates[2];
		return { x*cos(theta) + z * sin(theta), y, -x * sin(theta) + z * cos(theta) };
	}
	static std::array<float, 3> rotateZ(std::array<float, 3> coordinates, float theta) {
		float x = coordinates[0];
		float y = coordinates[1];
		float z = coordinates[2];
		return { x*cos(theta) - y * sin(theta), x*sin(theta) + y * cos(theta), z };
	}
	static std::array<float, 3> scale(std::array<float, 3> coordinates, std::array<float, 3> diff) {
		float x = coordinates[0];
		float y = coordinates[1];
		float z = coordinates[2];
		float dx = diff[0];
		float dy = diff[1];
		float dz = diff[2];
		return { x*dx, y*dy, z*dz };
	}
	static std::array<float, 2> projectPoint(std::array<float, 3> coordinates, float d) {
		return { coordinates[0] / (coordinates[2] / d), coordinates[1] / (coordinates[2] / d) };
	}
	const static int INSIDE = 0;
	const static int LEFT = 1;
	const static int RIGHT = 2;
	const static int BOTTOM = 4;
	const static int TOP = 8;
	static int outcode(std::array<float, 2> coordinates) {
		float x = coordinates[0];
		float y = coordinates[1];
		int b0, b1, b2, b3;
		b0 = y > 1 ? 8 : 0;
		b1 = y < -1 ? 4 : 0;
		b2 = x > 1 ? 2 : 0;
		b3 = x < -1 ? 1 : 0;
		return (b0 + b1 + b2 + b3);
	}
	static bool acceptSegment(std::array<float, 2> seg0, std::array<float, 2> seg1) {
		int code0 = outcode(seg0);
		int code1 = outcode(seg1);
		return !(code0 | code1);
	}
	static bool discardSegment(std::array< float, 2> seg0, std::array<float, 2> seg1) {
		int outcode0 = outcode(seg0);
		int outcode1 = outcode(seg1);
		return outcode0 & outcode1;
	}
	static bool clipSegemnt(std::array< float, 2> seg0, std::array<float, 2> seg1) {
		int outcode0 = outcode(seg0);
		int outcode1 = outcode(seg1);
		if (acceptSegment(seg0, seg1)) {
			return false;
		}
		else if (outcode0 & outcode1) {
			return false;
		}
		else {
			return true;
		}
	}
	static std::array<float, 3> normalize(std::array<float, 3> vector) {
		float length = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
		return { vector[0] / length, vector[1] / length, vector[2] / length };
	}
	static float dotProduct(std::array<float, 3> vectorA, std::array<float, 3> vectorB) {
		float count = 0;
		for (int i = 0; i < vectorA.size(); i++)
			count += vectorA[i] * vectorB[i];
		return count;
	}
	static std::array<float, 3> crossProduct(std::array<float, 3> a, std::array<float, 3> b) {
		float cx = a[1] * b[2] - a[2] * b[1];
		float cy = a[2] * b[0] - a[0] * b[2];
		float cz = a[0] * b[1] - a[1] * b[0];
		return { cx, cy, cz };
	}
	static float diffuseTerm(std::array<float, 3> L, std::array<float, 3> N) {
		return dotProduct(L, N);
	}
	static std::array<float, 3> idealReflection(std::array<float, 3> L, std::array<float, 3> N) {
		float d = 2 * dotProduct(L, normalize(N));
		float Rx = d * N[0];
		float Ry = d * N[1];
		float Rz = d * N[2];
		return { Rx - L[0], Ry - L[1], Rz - L[2] };
	}
	static float specularTerm(std::array<float, 3> V, std::array<float, 3> R, float P) {
		float spec = dotProduct(V, R);
		if (spec > 0) {
			return pow(spec, P);
		}
		else {
			return 0;
		}
	}
private:
	void printCoords(std::array<float, 2> c) {
		std::cout << c[0] << ", " << c[1] << std::endl;
	}
	void printArray(std::array<float, 3> a) {
		std::cout << a[0] << ", " << a[1] << ", " << a[2] << std::endl;
	}
};