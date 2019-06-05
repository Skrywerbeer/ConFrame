#include "conframe.h"

ConFrame::ConFrame() {
	fb = open("/dev/fb0", O_RDWR);
	if (fb == 0)
		throw "Could not open file \"/dev/fb0\".\n";
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

ConFrame::~ConFrame() {
	close(fb);
}

void ConFrame::pixel(const uint32_t x, const uint32_t y, const uint32_t color) {
	if (x > screeninfo.xres || y > screeninfo.yres) {
		std::cerr << x << ':' << y << '\t';
		throw "Pixel out of bounds\n";
	}

	buffer[((y*screeninfo.xres) + x)] = color;
}

void ConFrame::line(const uint32_t x0, const uint32_t y0,
                    const uint32_t x1, const uint32_t y1,
                    const uint32_t color) {
	// octant 1.

	switch (octant(x0, y0, x1, y1)) {
		case (1):
			linePosShallow(x0, y0, x1, y1, color);
			break;
		case (2):
			linePosSteep(x0, y0, x1, y1, color);
			break;
		case (3):
			lineNegSteep(x1, y1, x0, y0, color);
			break;
		case (4):
			lineNegShallow(x1, y1, x0, y0, color);
			break;
		case (5):
			linePosShallow(x1, y1, x0, y0, color);
			break;
		case (6):
			linePosSteep(x1, y1, x0, y0, color);
			break;
		case (7):
			lineNegSteep(x0, y0, x1, y1, color);
			break;
		case (8):
			lineNegShallow(x0, y0, x1, y1, color);
			break;
			// TODO: handle vertical and horizontal lines.
		default:
			std::cerr << "Not in any octant!!!\n";
			break;
	}
}

void ConFrame::line(const ConPoint p0, const ConPoint p1, const uint32_t color) {
	line(p0.x(), p0.y(), p1.x(), p1.y(), color);
}

void ConFrame::fill(const uint32_t color) {
	for (uint32_t i = 0; i <= bufferLen; ++i)
		buffer[i] = color;
}

uint32_t ConFrame::xRes() const {
	return screeninfo.xres;
}

uint32_t ConFrame::yRes() const {
	return screeninfo.yres;
}

uint8_t ConFrame::octant(const uint32_t x0, const uint32_t y0,
                         const uint32_t x1, const uint32_t y1) const {
	if (x0 == x1)
		return 9;
	else if (y0 == y1)
		return 10;
	const int32_t dx = static_cast<int32_t>(x1) - static_cast<int32_t>(x0);
	const int32_t dy = static_cast<int32_t>(y1) - static_cast<int32_t>(y0);

	double m = static_cast<double>(dy)/static_cast<double>(dx)	;
	if ((m > 0) && (m < 1)) {
		if (dx > 0)
			return 1;
		else
			return 5;
	    }
	else if (m > 1) {
		if (dx > 0)
			return 2;
		else
			return 6;
	}
	else if ((m < 0) && (m > -1)) {
		if (dy > 0)
			return 4;
		else
			return 8;
	}
	else if (m < -1) {
		if (dy > 0)
			return 3;
		else
			return 7;
	}
	return 0;
}

void ConFrame::linePosShallow(const uint32_t x0, const uint32_t y0,
                       const uint32_t x1, const uint32_t y1,
                       const uint32_t color) {
	int32_t dx = static_cast<int32_t>(x1) - static_cast<int32_t>(x0);
	int32_t dy = static_cast<int32_t>(y1) - static_cast<int32_t>(y0);
	uint32_t x = x0;
	uint32_t y = y0;
	int32_t error = 0;
	for (; x < x1; ++x) {
		pixel(x, y, color);
		error += dy;
		if ((2*error) > dx) {
			++y;
			error -= dx;
		}
	}
}

void ConFrame::linePosSteep(const uint32_t x0, const uint32_t y0,
                            const uint32_t x1, const uint32_t y1,
                            const uint32_t color) {
	int32_t dx = static_cast<int32_t>(x1) - static_cast<int32_t>(x0);
	int32_t dy = static_cast<int32_t>(y1) - static_cast<int32_t>(y0);
	uint32_t x = x0;
	uint32_t y = y0;
	int32_t error = 0;
	for (; y < y1; ++y) {
		pixel(x, y, color);
		error += dx;
		if ((2*error) > dy) {
			++x;
			error -= dy;
		}
	}
}

void ConFrame::lineNegShallow(const uint32_t x0, const uint32_t y0,
                       const uint32_t x1, const uint32_t y1,
                       const uint32_t color) {
	int32_t dx = static_cast<int32_t>(x1) - static_cast<int32_t>(x0);
	int32_t dy = static_cast<int32_t>(y1) - static_cast<int32_t>(y0);
	uint32_t x = x0;
	uint32_t y = y0;
	int32_t error = 0;
	for (; x < x1; ++x) {
		pixel(x, y, color);
		error += dy;
		if ((2*error) < -dx) {
			--y;
			error += dx;
		}
	}
}

void ConFrame::lineNegSteep(const uint32_t x0, const uint32_t y0,
                            const uint32_t x1, const uint32_t y1,
                            const uint32_t color) {
	int32_t dx = static_cast<int32_t>(x1) - static_cast<int32_t>(x0);
	int32_t dy = static_cast<int32_t>(y1) - static_cast<int32_t>(y0);
	uint32_t x = x0;
	uint32_t y = y0;
	int32_t error = 0;
	for (; y > y1; --y) {
		pixel(x, y, color);
		error += dx;
		if ((2*error) > -dy) {
			++x;
			error += dy;
		}
	}
}
