#ifndef DANDELION_PROGRAM_H
#define DANDELION_PROGRAM_H

#include "Shader.h"

#include <vector>
#include <memory>

namespace Dandelion {

    class DANDELION_API Program {
    public:
        inline Program(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept : mShaders(shaders) {}

        virtual ~Program() noexcept = default;

        virtual void Enable() noexcept = 0;

        virtual void Disable() noexcept = 0;

    protected:
        std::vector<std::shared_ptr<Shader>> mShaders;
    };

}

#endif