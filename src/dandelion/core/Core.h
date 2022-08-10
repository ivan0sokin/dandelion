#ifndef DANDELION_CORE_H
#define DANDELION_CORE_H

#ifdef DANDELION_WINDOWS
    #ifdef DANDELION_BUILD
        #define DANDELION_API __declspec(dllexport)
    #else
        #define DANDELION_API __declspec(dllimport)
    #endif
#else
    #define DANDELION_API
#endif

#endif