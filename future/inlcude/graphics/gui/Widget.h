//
// Created by Alex on 20/01/2024.
//

#ifndef ORION_WIDGET_H
#define ORION_WIDGET_H

#include "orion/core/type.h"
#include "orion/graphics/Drawable.h"

#include <optional>

namespace orion {

    class Widget : public Drawable {
    public:
        Widget(PtrMut<Widget> parent = nullptr);

        Ptr<Widget> get_parent()             const;
        Ref<Widget> get_child (size_t index) const;

        void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const override;

    private:
        std::unique_ptr<Widget> m_parent;
        std::vector    <Widget> m_childs;
    };

} // orion

#endif //ORION_WIDGET_H
