//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_WINDOWEVENTLISTENER_H
#define ORION_WINDOWEVENTLISTENER_H

#include "WindowEvent.h"
#include "orion/core/event/EventListener.h"

namespace orion {
    class WindowEventListener : public EventListener {
    public:
        explicit WindowEventListener(Ref<std::shared_ptr<EventManager>> event_manager);
        virtual void on_position_change     (Ref<WindowPositionEvent>     event) {};
        virtual void on_size_change         (Ref<WindowSizeEvent>         event) {};
        virtual void on_close               (Ref<WindowCloseEvent>        event) {};
        virtual void on_refresh             (Ref<WindowRefreshEvent>      event) {};
        virtual void on_focus               (Ref<WindowFocusEvent>        event) {};
        virtual void on_iconify             (Ref<WindowIconifyEvent>      event) {};
        virtual void on_maximize            (Ref<WindowMaximizeEvent>     event) {};
        virtual void on_content_scale_change(Ref<WindowContentScaleEvent> event) {};

//        ~WindowEventListener() override;
    };
}


#endif //ORION_WINDOWEVENTLISTENER_H
