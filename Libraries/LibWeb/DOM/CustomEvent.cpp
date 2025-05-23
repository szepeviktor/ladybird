/*
 * Copyright (c) 2021, Luke Wilde <lukew@serenityos.org>
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Runtime/Realm.h>
#include <LibWeb/Bindings/CustomEventPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/DOM/CustomEvent.h>

namespace Web::DOM {

GC_DEFINE_ALLOCATOR(CustomEvent);

GC::Ref<CustomEvent> CustomEvent::create(JS::Realm& realm, FlyString const& event_name, CustomEventInit const& event_init)
{
    return realm.create<CustomEvent>(realm, event_name, event_init);
}

WebIDL::ExceptionOr<GC::Ref<CustomEvent>> CustomEvent::construct_impl(JS::Realm& realm, FlyString const& event_name, CustomEventInit const& event_init)
{
    return create(realm, event_name, event_init);
}

CustomEvent::CustomEvent(JS::Realm& realm, FlyString const& event_name, CustomEventInit const& event_init)
    : Event(realm, event_name, event_init)
    , m_detail(event_init.detail)
{
}

CustomEvent::~CustomEvent() = default;

void CustomEvent::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(CustomEvent);
    Base::initialize(realm);
}

void CustomEvent::visit_edges(JS::Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_detail);
}

// https://dom.spec.whatwg.org/#dom-customevent-initcustomevent
void CustomEvent::init_custom_event(String const& type, bool bubbles, bool cancelable, JS::Value detail)
{
    // 1. If this’s dispatch flag is set, then return.
    if (dispatched())
        return;

    // 2. Initialize this with type, bubbles, and cancelable.
    initialize_event(type, bubbles, cancelable);

    // 3. Set this’s detail attribute to detail.
    m_detail = detail;
}

}
