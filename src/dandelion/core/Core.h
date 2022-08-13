#ifndef DANDELION_CORE_H
#define DANDELION_CORE_H

#ifdef DANDELION_WINDOWS
    #ifdef DANDELION_BUILD
        #define DANDELION_API __declspec(dllexport)
        #define EXTERN_TEMPLATE
    #else
        #define DANDELION_API __declspec(dllimport)
        #define EXTERN_TEMPLATE extern
    #endif
#else
    #define DANDELION_API
#endif

#endif