#ifndef CONFRAME_H
#define CONFRAME_H

#include <iostream>
extern "C" {
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stropts.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
}

#include "conpoint.h"

class ConFrame
{
	public:
		ConFrame();
		~ConFrame();

		void pixel(const uint32_t x, const uint32_t y, const uint32_t color);

		void line(const uint32_t x0, const uint32_t y0,
		          const uint32_t x1, const uint32_t y1,
		          const uint32_t color);
		void line(const ConPoint p0,
		          const ConPoint p1,
		          const uint32_t color);
		void line(const ConPoint p0,
		          const uint32_t x1, const uint32_t y1,
		          const uint32_t color);
		void line (const uint32_t x0, const uint32_t y0,
		           const ConPoint p1,
		           const uint32_t color);

		void fill(const uint32_t color);

		uint32_t xRes() const;
		uint32_t yRes() const;
	private:
		fb_var_screeninfo screeninfo;
		uint32_t *buffer;
		uint32_t bufferLen;
		int fb;
		uint8_t octant(const uint32_t x0, const uint32_t y0,
		               const uint32_t x1, const uint32_t y1) const;

		void lineHorizontal(const uint32_t x0, const uint32_t y,
		                    const uint32_t x1, const uint32_t color);
		void lineVertical(const uint32_t x, const uint32_t y0,
		                  const uint32_t y1, const uint32_t color);
		void lineDiagonal(const uint32_t x0, const uint32_t y0,
		                     const uint32_t x1, const uint32_t y1,
		                     const uint32_t color);

		void linePosShallow(const uint32_t x0, const uint32_t y0,
		             const uint32_t x1, const uint32_t y1,
		             const uint32_t color);
		void linePosSteep(const uint32_t x0, const uint32_t y0,
		             const uint32_t x1, const uint32_t y1,
		             const uint32_t color);


		void lineNegShallow(const uint32_t x0, const uint32_t y0,
		             const uint32_t x1, const uint32_t y1,
		             const uint32_t color);
		void lineNegSteep(const uint32_t x0, const uint32_t y0,
		             const uint32_t x1, const uint32_t y1,
		             const uint32_t color);

};

#endif // CONFRAME_H
