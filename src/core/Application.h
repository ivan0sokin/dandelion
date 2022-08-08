#ifndef DANDELION_APPLICATION_H
#define DANDELION_APPLICATION_H

#include "Core.h"

namespace Dandelion {

    class DANDELION_API Application {
    public:
        Application() noexcept = default;

        virtual ~Application() noexcept = default;

        virtual void Run() noexcept = 0;
    };

}

#endif