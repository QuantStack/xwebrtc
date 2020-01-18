/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_VIDEO_RECORDER_HPP
#define XWEBRTC_VIDEO_RECORDER_HPP

#include <string>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xvideo.hpp"

#include "xrecorder.hpp"
#include "xwebrtc_config.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*******************************
     * xvideo_recorder declaration *
     *******************************/

    template <class D>
    class xvideo_recorder : public xrecorder<D>
    {
    public:

        using base_type = xrecorder<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xw::video, derived_type, video);

        void save(const std::string& filename = "") const;

    protected:

        xvideo_recorder();
        xvideo_recorder(xw::xholder<xmedia_stream> video);
        using base_type::base_type;

    private:

        void set_defaults();
        void setup_properties();
    };

    using video_recorder = xw::xmaterialize<xvideo_recorder>;

    /**********************************
     * xvideo_recorder implementation *
     **********************************/

    template <class D>
    inline void xvideo_recorder<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(video(), state["video"], buffers);
    }

    template <class D>
    inline void xvideo_recorder<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(video, patch, buffers);
    }

    template <class D>
    inline void xvideo_recorder<D>::save(const std::string& filename) const
    {
        this->save_file(filename, this->video().value().cbegin(), this->video().value().cend());
    }

    template <class D>
    inline xvideo_recorder<D>::xvideo_recorder()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    inline xvideo_recorder<D>::xvideo_recorder(xw::xholder<xmedia_stream> video)
        : base_type()
    {
        this->stream() = video;

        set_defaults();

        this->setup_properties();
    }

    template <class D>
    inline void xvideo_recorder<D>::set_defaults()
    {
        this->_model_name() = "VideoRecorderModel";
        this->_view_name() = "VideoRecorderView";

        this->video() = xw::video::initialize().format(this->format()).finalize();
    }

    template <class D>
    inline void xvideo_recorder<D>::setup_properties()
    {
        this->observe("format", [](auto& owner) {
            owner.video().format() = owner.format();
        });
        this->video().observe("value", [this](auto& owner) {
            if (this->autosave() && owner.value().size() != 0)
            {
                this->save_file("", owner.value().cbegin(), owner.value().cend());
            }
        });
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xvideo_recorder>;
    extern template xw::xmaterialize<xwebrtc::xvideo_recorder>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xvideo_recorder>>;
#endif

#endif
