#ifndef CONFRAME_H
#define CONFRAME_H

#include <iostream>
extern "C" {
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stropts.h>
#include <fcntl.h>
#include <errno.h>
}

class ConFrame
{
	public:
		ConFrame();

		void pixel(const uint32_t x, const uint32_t y, const uint32_t color);

		uint32_t xRes() const;
		uint32_t yRes() const;
	private:
		fb_var_screeninfo screeninfo;
		uint32_t *buffer;
		uint32_t bufferLen;
		int fb;
};

#endif // CONFRAME_H
