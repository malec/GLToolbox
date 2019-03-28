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
		return { coordinates[0]/(coordinates[2]/d), coordinates[1]/(coordinates[2]/d) };
	}
	static int outcode(std::array<float, 3> coordinates) {
		float x = coordinates[0];
		float y = coordinates[1];
		float z = coordinates[2];
		std::string b0, b1, b2, b3;
		b0 = y > 1 ? "1" : "0";
		b1 = y < 0 ? "1" : "0";
		b2 = x > 1 ? "1" : "0";
		b3 = x < 0 ? "1" : "0";
		return stoi(b0 + b1 + b2 + b3);
	}
	static bool acceptOutcode(std::array<bool, 3> seg0, std::array<bool, 3> seg1) {
		return !((seg0[0] && seg1[0]) || (seg0[1] && seg1[1]) || (seg0[2] && seg1[2]));
	}
};