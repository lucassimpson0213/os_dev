#ifndef TEST_H

#define TEST_H

#define K_ASSERT(expr) \
if(!(expr)) do { kassert_fail(__FILE__, __LINE__, __func__)}

void kassert_fail() {
    
}
#endif