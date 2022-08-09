#ifndef DANDELION_ENTRYPOINT_H
#define DANDELION_ENTRYPOINT_H

#include "core/Application.h"
#include "core/Engine.h"

extern Dandelion::Application* CreateApplication();

int main() {
    Dandelion::Engine::Instance()->Initialize();
    auto application = CreateApplication();
    application->Run();
    Dandelion::Engine::Instance()->Terminate();
    return 0;
}

#endif