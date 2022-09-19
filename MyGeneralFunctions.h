#ifndef MYGENERALFUNCTIONS_H
#define MYGENERALFUNCTIONS_H

#include "stdint.h"

extern const void *JUST_FREE_PTR;

typedef int (*comp_t)(const void *item1, const void *item2);

//-----------------------------------------------------------
//! Sort array
//!
//! \param [in, out] arr array of the lines
//! \param [in] arr_size size of the array in bytes
//! \param [in] item_size size of the arra item in bytes
//! \param [in] comp function-comparator
//-----------------------------------------------------------
void MG_qsort(void *arr, size_t arr_size, size_t item_size, comp_t comp);

//-----------------------------------------------------------
//! Swap 2 array elements
//!
//! \param [in, out] lines array
//! \param [in] item_size size of the array item in bytes
//! \param [in] fIndex index of the first element
//! \param [in] sIndex index of the second element
//-----------------------------------------------------------
void MG_swap(void *arr, size_t item_size, int fIndex, int sIndex);

#endif //MYGENERALFUNCTIONS_H