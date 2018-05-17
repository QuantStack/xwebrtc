/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_VIDEO_STREAM_HPP
#define XWEBRTC_VIDEO_STREAM_HPP

#include <string>

#include "xwidgets/xmaterialize.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace xwebrtc
{
    /*****************************
     * xvideo_stream declaration *
     *****************************/

    template <class D>
    class xvideo_stream : public xmedia_stream<D>
    {
    public:

        using base_type = xmedia_stream<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, url, "https://webrtc.github.io/samples/src/video/chrome.mp4");
        XPROPERTY(bool, derived_type, play, true);
        XPROPERTY(bool, derived_type, loop, true);

    protected:

        xvideo_stream();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using video_stream = xw::xmaterialize<xvideo_stream>;

    using video_stream_generator = xw::xgenerator<xvideo_stream>;

    /********************************
     * xvideo_stream implementation *
     ********************************/

    template <class D>
    inline void xvideo_stream<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(url, state, buffers);
        xw::set_patch_from_property(play, state, buffers);
        xw::set_patch_from_property(loop, state, buffers);
    }

    template <class D>
    inline void xvideo_stream<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(url, patch, buffers);
        xw::set_property_from_patch(play, patch, buffers);
        xw::set_property_from_patch(loop, patch, buffers);
    }

    template <class D>
    inline xvideo_stream<D>::xvideo_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xvideo_stream<D>::set_defaults()
    {
        this->_model_name() = "VideoStreamModel";
        // this->_view_name() = "VideoStreamView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xvideo_stream>;
    extern template xw::xmaterialize<xwebrtc::xvideo_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xvideo_stream>>;
    extern template class xw::xgenerator<xwebrtc::xvideo_stream>;
    extern template xw::xgenerator<xwebrtc::xvideo_stream>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xvideo_stream>>;
#endif

#endif
