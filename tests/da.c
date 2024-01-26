#define MAZ_IMPLEMENTATION
#include "../maz.h"

// test file for dynamic array

int main()
{
    int *da = NULL;
    
    for (int i = 0; i < 100; ++i){
        maz_daput(da, i);
        // maz_log(MAZ_INFO, "%d", da[i]);
    }
    // for (int i = 0; i < 100; ++i){
    //     maz_log(MAZ_INFO, "%d", da[i]);
    // }
    assert(maz_dalen(da) == 100);
    maz_daputat(da, 5, 100);
    assert(da[5] == 100);
    assert(maz_dalen(da) == 101);
    maz_dadel(da, 5);
    assert(maz_dalen(da) == 100);
    assert(da[5] == 5);
    maz_daset(da, 50, 100);
    assert(da[50] == 100);
    assert(maz_dalen(da) == 100);
    maz_dafree(da);
    assert(da == NULL);

    // test for maz_daputmany
    char *str = "hello world";
    char *arr = NULL; 
    maz_daputmany(arr, str, 11);
    assert(maz_dalen(arr) == 11);
    assert(arr[0] == 'h');
    assert(arr[10] == 'd');
    maz_dafree(arr);
    assert(arr == NULL);

    // test for maz_dacopy
    int *arr1 = NULL;
    int *arr2 = NULL;
    for (int i = 0; i < 100; ++i){
        maz_daput(arr1, i);
    }
    maz_dacpy(arr2, arr1);
    maz_daput(arr2, 100);
    assert(maz_dalen(arr2) == 101);
    assert(arr2[100] == 100);
    maz_dafree(arr1);
    maz_dafree(arr2);


    return EXIT_SUCCESS;
}
