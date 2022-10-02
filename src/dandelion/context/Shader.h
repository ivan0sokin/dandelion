#ifndef DANDELION_SHADER_H
#define DANDELION_SHADER_H

#include "../core/Core.h"

#include <string>

namespace Dandelion {

    class DANDELION_API Shader {
    public:
        virtual ~Shader() noexcept = default;

    protected:
        Shader() noexcept = default;
    };

}

#endif