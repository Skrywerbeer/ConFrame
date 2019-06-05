#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <vector>

#include <conpoint.h>

const uint32_t TRANS_DIM = 3;

template<typename T>
struct Transform {
		Transform(const T (&mat)[TRANS_DIM][TRANS_DIM]) {
			for (uint32_t i = 0; i < TRANS_DIM; ++i)
				for (uint32_t j = 0; j < TRANS_DIM; ++j)
					matrix[i][j] = mat[i][j];
		}

		inline ConPoint operator*(const ConPoint point) {
			const T vector[TRANS_DIM] = {static_cast<T>(point.x()),
			                             static_cast<T>(point.y()),
			                             static_cast<T>(point.z())};
			uint32_t retVector[TRANS_DIM] = {0,
			                                 0,
			                                 0};
			for (uint32_t row = 0; row < TRANS_DIM; ++row)
				for (uint32_t column = 0; column < TRANS_DIM; ++column)
					retVector[row] += matrix[row][column]*
					                  static_cast<T>(vector[row]);
			return ConPoint(retVector[0], retVector[1], retVector[2]);
		}

		T matrix[TRANS_DIM][TRANS_DIM];
};

inline ConPoint operator*(const uint32_t trans[TRANS_DIM][TRANS_DIM],
                          const ConPoint point) {
	const uint32_t vector[TRANS_DIM] = {point.x(),
	                                     point.y(),
	                                     point.z()};
	uint32_t retVector[TRANS_DIM] = {0,
	                                     0,
	                                     0};
	for (uint32_t row = 0; row < TRANS_DIM; ++row)
		for (uint32_t column = 0; column < TRANS_DIM; ++column)
			retVector[row] += trans[row][column]*vector[row];

	return (ConPoint(retVector[0], retVector[1], retVector[2]));
}


#endif // MATRIX_H
