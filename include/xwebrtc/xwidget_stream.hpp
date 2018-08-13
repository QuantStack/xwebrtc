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

#include <string>
#include <stdexcept>

#include "xwidgets/xmaterialize.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

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

        using widget_type = xw::xholder<xw::xwidget>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(widget_type, derived_type, widget);
        XPROPERTY(xtl::xoptional<int>, derived_type, max_fps);

    protected:

        xwidget_stream();
        using base_type::base_type;

    private:

        void set_defaults();

        void setup_properties();
    };

    using widget_stream = xw::xmaterialize<xwidget_stream>;

    using widget_stream_generator = xw::xgenerator<xwidget_stream>;

    /********************************
     * xwidget_stream implementation *
     ********************************/

    template <class D>
    inline void xwidget_stream<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        using xw::set_patch_from_property;
        base_type::serialize_state(state, buffers);

        set_patch_from_property(widget, state, buffers);
        set_patch_from_property(max_fps, state, buffers);
    }

    template <class D>
    inline void xwidget_stream<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
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
    inline void xwidget_stream<D>::set_defaults()
    {
        this->_model_name() = "WidgetStreamModel";
        this->_view_name() = "WidgetStreamView";
    }

    template <class D>
    inline void xwidget_stream<D>::setup_properties()
    {
        auto self = this->self();
        self->template validate<decltype(self->max_fps)>([](auto& /*owner*/, auto& proposal) {
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
    extern template class xw::xgenerator<xwebrtc::xwidget_stream>;
    extern template xw::xgenerator<xwebrtc::xwidget_stream>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xwidget_stream>>;
#endif

#endif
