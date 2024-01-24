#define MAZ_IMPLEMENTATION
#include "../maz.h"

typedef struct {
    int *items;
    size_t count;
    size_t capacity;
}Da;

int main()
{
    Da da = {0};
    
    for(size_t i = 0; i<10; i ++){
        maz_da_append(&da, i);
    }
    maz_da_remove_index(&da, 5);
    for(size_t i = 0; i<da.count; i ++){
        maz_log(MAZ_INFO, "%d", da.items[i]);
    }

    return EXIT_SUCCESS;
}
