/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_WIDGET_STREAM_HPP
#define XWEBRTC_WIDGET_STREAM_HPP

#include <stdexcept>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /******************************
     * xwidget_stream declaration *
     ******************************/

    template <class D>
    class xwidget_stream : public xmedia_stream<D>
    {
    public:

        using base_type = xmedia_stream<D>;
        using derived_type = D;

        using widget_type = xw::xholder;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(widget_type, derived_type, widget);
        XPROPERTY(xtl::xoptional<int>, derived_type, max_fps);

    protected:

        xwidget_stream();
        xwidget_stream(xw::xholder widget);
        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    using widget_stream = xw::xmaterialize<xwidget_stream>;

    /********************************
     * xwidget_stream implementation *
     ********************************/

    template <class D>
    inline void xwidget_stream<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(widget(), state["widget"], buffers);
        xwidgets_serialize(max_fps(), state["max_fps"], buffers);
    }

    template <class D>
    inline void xwidget_stream<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(widget, patch, buffers);
        set_property_from_patch(max_fps, patch, buffers);
    }

    template <class D>
    inline xwidget_stream<D>::xwidget_stream()
        : base_type()
    {
        set_defaults();

        setup_properties();
    }

    template <class D>
    inline xwidget_stream<D>::xwidget_stream(xw::xholder widget)
        : base_type()
    {
        set_defaults();

        setup_properties();

        this->widget() = widget;
    }

    template <class D>
    inline void xwidget_stream<D>::set_defaults()
    {
        this->_model_name() = "WidgetStreamModel";
        this->_view_name() = "WidgetStreamView";
    }

    template <class D>
    inline void xwidget_stream<D>::setup_properties()
    {
        this->template validate<typename decltype(this->max_fps)::value_type>("max_fps", [](auto& /*owner*/, auto& proposal) {
            if (proposal.has_value() && proposal.value() < 0)
            {
                throw std::runtime_error("max_fps attribute must be a positive integer");
            }
        });
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xwidget_stream>;
    extern template xw::xmaterialize<xwebrtc::xwidget_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xwidget_stream>>;
#endif

#endif
