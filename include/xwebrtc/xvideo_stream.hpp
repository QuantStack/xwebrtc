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
#include <utility>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xvideo.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace nl = nlohmann;

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

        using video_type = xw::xholder<xw::xvideo>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(video_type, derived_type, video);
        XPROPERTY(bool, derived_type, playing, true);

    protected:

        xvideo_stream();
        xvideo_stream(xw::xholder<xw::xvideo> video);
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using video_stream = xw::xmaterialize<xvideo_stream>;

    /********************************
     * xvideo_stream implementation *
     ********************************/

    template <class D>
    inline void xvideo_stream<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(video(), state["video"], buffers);
        xwidgets_serialize(playing(), state["playing"], buffers);
    }

    template <class D>
    inline void xvideo_stream<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(video, patch, buffers);
        set_property_from_patch(playing, patch, buffers);
    }

    template <class D>
    inline xvideo_stream<D>::xvideo_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xvideo_stream<D>::xvideo_stream(xw::xholder<xw::xvideo> video)
        : base_type()
    {
        set_defaults();

        this->video() = video;
    }

    template <class D>
    inline void xvideo_stream<D>::set_defaults()
    {
        this->_model_name() = "VideoStreamModel";
        // this->_view_name() = "VideoStreamView";
    }

    inline video_stream video_stream_from_file(const std::string& filename)
    {
        auto vid = xw::video_from_file(filename).autoplay(false).controls(false).finalize();
        return video_stream::initialize().video(std::move(vid));
    }

    inline video_stream video_stream_from_url(const std::string& url)
    {
        auto vid = xw::video_from_url(url).autoplay(false).controls(false).finalize();
        return video_stream::initialize().video(std::move(vid));
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xvideo_stream>;
    extern template xw::xmaterialize<xwebrtc::xvideo_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xvideo_stream>>;
#endif

#endif
