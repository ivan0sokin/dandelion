#ifndef DANDELION_ENTRYPOINT_H
#define DANDELION_ENTRYPOINT_H

#include "core/Application.h"

extern Dandelion::Application* CreateApplication();

int main() {
    auto application = CreateApplication();
    application->Run();
    return 0;
}

#endif