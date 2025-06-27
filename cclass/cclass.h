/* * * * * * * * * * * * * * * * * * * * * * * * *
 * cclass.h
 *
 * Library Name: cclasss
 *
 * Date: 04-05-2025
 * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CCLASS_H_
#define _CCLASS_H_

#ifdef __cplusplus
    extern "C" {
#endif
/**
* @brief Macro structure definitions
*/
#define class(name, block) \
struct name block; \
typedef struct name name;

/**
* @brief Macro definition for class constructor of specif
*/
#define class_construct(name, params, ctor_type, dtor_type) \
name* name##_new params { \
    name* self = malloc(sizeof(name)); \
    if (self == NULL) return NULL; \
    do ctor_type while(0); \
    return self; \
} \
void name##_delete(name* ptr) { \
    if (ptr) { \
        do dtor_type while(0); \
        free(ptr); \
    } \
}
/**
* @brief Macro Definition for class function / method
*/
#define class_function(class_name, class_method) \
    class_name##_##method_name(class_name *self)

/**
* @brief Macros definitions for shorthand class initialisation and deleting
*/
#define new(class_name, ...) class_name##_new(__VA_ARGS__)
#define destruct(class_name, ...) class_name##_delete(__VA_ARGS__)

#ifdef __cplusplus
}
#endif /* __CPLUSPLUS */
#endif /* _CCLASS_H_ */