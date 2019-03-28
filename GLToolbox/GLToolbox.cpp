#include <array>

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
};