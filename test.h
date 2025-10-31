#ifndef TEST_H

#define TEST_H

#define KASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            printk("ASSERT FAILED: %s at %s:%d\n", msg, __FILE__, __LINE__); \
            for (;;) ; /* halt */ \
        } \
    } while (0)                                                   \

void kassert_fail(const char * expr, const char * file, const char * func) {
     //TODO add print statements when printk is implemented
}
#endif