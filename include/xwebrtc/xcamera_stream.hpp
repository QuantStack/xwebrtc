/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_CAMERA_STREAM_HPP
#define XWEBRTC_CAMERA_STREAM_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace xwebrtc
{
    /******************************
     * xcamera_stream declaration *
     ******************************/

    template <class D>
    class xcamera_stream : public xwebrtc::xmedia_stream<D>
    {
    public:

        using base_type = xwebrtc::xmedia_stream<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(bool, derived_type, audio, true);
        XPROPERTY(bool, derived_type, video, true);

    protected:

        xcamera_stream();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using camera_stream = xw::xmaterialize<xcamera_stream>;

    using camera_stream_generator = xw::xgenerator<xcamera_stream>;

    /*********************************
     * xcamera_stream implementation *
     *********************************/

    template <class D>
    inline void xcamera_stream<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(audio, state, buffers);
        xw::set_patch_from_property(video, state, buffers);
    }

    template <class D>
    inline void xcamera_stream<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(audio, patch, buffers);
        xw::set_property_from_patch(video, patch, buffers);
    }

    template <class D>
    inline xcamera_stream<D>::xcamera_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xcamera_stream<D>::set_defaults()
    {
        this->_model_name() = "CameraStreamModel";
        // this->_view_name() = "CameraStreamView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xcamera_stream>;
    extern template xw::xmaterialize<xwebrtc::xcamera_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xcamera_stream>>;
    extern template class xw::xgenerator<xwebrtc::xcamera_stream>;
    extern template xw::xgenerator<xwebrtc::xcamera_stream>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xcamera_stream>>;
#endif

#endif
