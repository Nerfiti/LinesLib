#include "MyGeneralFunctions.h"
#include "assert.h"

///If the pointer value matches this value, then the memory allocated to this pointer had been freed
const void * JUST_FREE_PTR = "JUST_FREE";

void MG_qsort(void *arr, size_t arr_size, size_t item_size, comp_t comp)
{
    assert(arr != nullptr);

    if (arr_size <= item_size)
    {
        return;
    }
    int last = 1;
    char *array = (char *)arr;
    for (int i = 1; i < arr_size/item_size; i += 1)
    {
        if (comp(array, array + i*item_size) > 0)
        {
            MG_swap(arr, item_size, i, last);
            last++;
        }
    }
    MG_swap(array, item_size, 0, (last-1));
    MG_qsort(array, (last-1)*item_size, item_size, comp);
    MG_qsort(array + last*item_size, arr_size - last*item_size, item_size, comp);
}

void MG_swap(void *arr, size_t item_size, int fIndex, int sIndex)
{
    char *array = (char *)arr;
    for (int i = 0; i < item_size; ++i)
    {
        char temp = array[fIndex*item_size+i];
        array[fIndex*item_size+i] = array[sIndex*item_size+i];
        array[sIndex*item_size+i] = temp;
    }

}