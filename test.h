#ifndef TEST_H

#define TEST_H

#define K_ASSERT(expr)                                              \
    do {                                                            \
        if (!(expr)) {                                              \
            kassert_fail(#expr, __FILE__, __LINE__, __func__);      \
        }                                                           \
    } while (0)                                                     \

void kassert_fail(const char * expr, const char * file, const char * func) {
     //TODO add print statements when printk is implemented
}
#endif