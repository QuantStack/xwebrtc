/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_MEDIA_STREAM_HPP
#define XWEBRTC_MEDIA_STREAM_HPP

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xwebrtc_config.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*****************************
     * xmedia_stream declaration *
     *****************************/

    template <class D>
    class xmedia_stream : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xmedia_stream();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using media_stream = xw::xmaterialize<xmedia_stream>;

    /********************************
     * xmedia_stream implementation *
     ********************************/

    template <class D>
    inline void xmedia_stream<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xmedia_stream<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xmedia_stream<D>::xmedia_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xmedia_stream<D>::set_defaults()
    {
        this->_model_module() = "jupyter-webrtc";
        this->_view_module() = "jupyter-webrtc";
        this->_model_name() = "MediaStreamModel";
        this->_view_name() = "MediaStreamView";
        this->_model_module_version() = jupyter_webrtc_semver();
        this->_view_module_version() = jupyter_webrtc_semver();
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xmedia_stream>;
    extern template xw::xmaterialize<xwebrtc::xmedia_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xmedia_stream>>;
#endif

#endif
