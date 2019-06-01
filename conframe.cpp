#include "conframe.h"

ConFrame::ConFrame() {
	fb = open("/dev/fb0", O_RDWR);
	if (fb == 0)
		throw "Could not open file \"/dev/fb0\".\n";
	screeninfo;
	if (ioctl(fb, FBIOGET_VSCREENINFO, &screeninfo) == -1) {
		std::cerr << "errno: " << errno << '\n';
		throw "Could not get screen info.\n";
	}

	bufferLen = screeninfo.xres*screeninfo.yres;
	buffer = static_cast<uint32_t*>(mmap(NULL, 4*bufferLen,
	                                     PROT_READ | PROT_WRITE, MAP_SHARED,
	                                     fb, 0));
	if (buffer == MAP_FAILED) {
		std::cerr << "errno: " << errno << '\n';
		throw "Could not map file to address space.\n";
	}
}

void ConFrame::pixel(const uint32_t x, const uint32_t y, const uint32_t color) {
	if (x > screeninfo.xres || y > screeninfo.yres) {
		std::cerr << x << ':' << y << '\t';
		throw "Pixel out of bounds\n";
	}

	buffer[((y*screeninfo.xres) + x)] = color;
}

uint32_t ConFrame::xRes() const {
	return screeninfo.xres;
}

uint32_t ConFrame::yRes() const {
	return screeninfo.yres;
}
