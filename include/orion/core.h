//
// Created by Alex on 07/11/2023.
//

#ifndef ORION_CORE_H
#define ORION_CORE_H

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define ORION_IMPORT __declspec(dllimport)
    #define ORION_EXPORT __declspec(dllexport)
#else
    #define ORION_IMPORT __attribute__ ((visibility("default")))
    #define ORION_EXPORT __attribute__ ((visibility("default")))
#endif

#ifdef ORION_SHARED
    #ifdef ORION_BUILD
        #define ORION_API ORION_EXPORT
    #else
        #define ORION_API ORION_IMPORT
    #endif
#else
    #define ORION_API
#endif

#include "orion/core/type.h"
#include "orion/core/Assert.h"
#include "orion/core/Indexer.h"
#include "orion/core/DeferredRegistry.h"
#include "orion/core/resource.h"

#include "orion/core/event/Event.h"
#include "orion/core/event/EventManager.h"
#include "orion/core/event/EventListener.h"

#include "orion/core/ecs/Component.h"
#include "orion/core/ecs/ComponentStorage.h"
#include "orion/core/ecs/Entity.h"
#include "orion/core/ecs/EntityManager.h"
#include "orion/core/ecs/StorageManager.h"
#include "orion/core/ecs/World.h"
#include "orion/core/ecs/Query.h"
#include "orion/core/ecs/System.h"

#include "orion/core/Application.h"

#endif //ORION_CORE_H
