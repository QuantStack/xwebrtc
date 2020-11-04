/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_AUDIO_STREAM_HPP
#define XWEBRTC_AUDIO_STREAM_HPP

#include <string>
#include <utility>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xaudio.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*****************************
     * xaudio_stream declaration *
     *****************************/

    template <class D>
    class xaudio_stream : public xmedia_stream<D>
    {
    public:

        using base_type = xmedia_stream<D>;
        using derived_type = D;

        using audio_type = xw::xholder;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(audio_type, derived_type, audio);
        XPROPERTY(bool, derived_type, playing, true);

    protected:

        xaudio_stream();
        xaudio_stream(xw::xholder audio);
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using audio_stream = xw::xmaterialize<xaudio_stream>;

    /********************************
     * xaudio_stream implementation *
     ********************************/

    template <class D>
    inline void xaudio_stream<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(audio(), state["audio"], buffers);
        xwidgets_serialize(playing(), state["playing"], buffers);
    }

    template <class D>
    inline void xaudio_stream<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(audio, patch, buffers);
        set_property_from_patch(playing, patch, buffers);
    }

    template <class D>
    inline xaudio_stream<D>::xaudio_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline xaudio_stream<D>::xaudio_stream(xw::xholder audio)
    : base_type()
    {
        set_defaults();

        this->audio() = audio;
    }

    template <class D>
    inline void xaudio_stream<D>::set_defaults()
    {
        this->_model_name() = "AudioStreamModel";
        this->_view_name() = "AudioStreamView";
    }

    inline audio_stream audio_stream_from_file(const std::string& filename)
    {
        auto vid = xw::audio_from_file(filename).autoplay(false).controls(false).finalize();
        return audio_stream::initialize().audio(std::move(vid));
    }

    inline audio_stream audio_stream_from_url(const std::string& url)
    {
        auto vid = xw::audio_from_url(url).autoplay(false).controls(false).finalize();
        return audio_stream::initialize().audio(std::move(vid));
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xwebrtc::xaudio_stream>;
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xaudio_stream>>;

#endif
