//
// Created by Alex on 20/01/2024.
//

#include "orion/graphics/gui/Widget.h"

namespace orion {

    Widget::Widget(PtrMut<Widget> parent) : m_parent(std::make_unique<Widget>(parent)) {}

    Ptr<Widget> orion::Widget::get_parent() const {
        return m_parent.get();
    }

    Ref<Widget> Widget::get_child(size_t index) const {
        return m_childs[index];
    }

    void Widget::draw(Ref<RenderTarget> target, Ref<RenderContext> context) const {

        // @TODO Draw vao like target.draw(vao, some context)

        for(auto& child: m_childs) {
            child.draw(target, context);
        }
    }

} // orion