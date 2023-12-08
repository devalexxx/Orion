//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_WINDOWEVENTLISTENER_H
#define ORION_WINDOWEVENTLISTENER_H

#include "WindowEvent.h"
#include "core/event/EventListener.h"

namespace orion {
    class WindowEventListener : public EventListener {
    public:
        explicit WindowEventListener(const std::shared_ptr<EventManager>& e_manager);
        virtual void onPositionChange       (const WindowPositionEvent      &event) {};
        virtual void onSizeChange           (const WindowSizeEvent          &event) {};
        virtual void onClose                (const WindowCloseEvent         &event) {};
        virtual void onRefresh              (const WindowRefreshEvent       &event) {};
        virtual void onFocus                (const WindowFocusEvent         &event) {};
        virtual void onIconify              (const WindowIconifyEvent       &event) {};
        virtual void onMaximize             (const WindowMaximizeEvent      &event) {};
        virtual void onContentScaleChange   (const WindowContentScaleEvent  &event) {};

//        ~WindowEventListener() override;
    };
}


#endif //ORION_WINDOWEVENTLISTENER_H
