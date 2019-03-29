#include <array>
#include <string>

static class GLToolbox {
public:
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
	const static int INSIDE = 0; // 0000
	const static int LEFT = 1;   // 0001
	const static int RIGHT = 2;  // 0010
	const static int BOTTOM = 4; // 0100
	const static int TOP = 8;    // 1000
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
};