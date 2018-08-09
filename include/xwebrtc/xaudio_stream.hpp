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
#include <vector>
#include <iostream>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xaudio.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

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

        using audio_type = xw::xholder<xw::xaudio>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(audio_type, derived_type, audio);
        XPROPERTY(bool, derived_type, playing, true);

    protected:

        xaudio_stream();
        template <class T>
        xaudio_stream(const xw::xaudio<T>& audio);
        template <class T>
        xaudio_stream(xw::xaudio<T>&& audio);
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using audio_stream = xw::xmaterialize<xaudio_stream>;

    using audio_stream_generator = xw::xgenerator<xaudio_stream>;

    /********************************
     * xaudio_stream implementation *
     ********************************/

    template <class D>
    inline void xaudio_stream<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(audio, state, buffers);
        xw::set_patch_from_property(playing, state, buffers);
    }

    template <class D>
    inline void xaudio_stream<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(audio, patch, buffers);
        xw::set_property_from_patch(playing, patch, buffers);
    }

    template <class D>
    inline xaudio_stream<D>::xaudio_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    template <class T>
    inline xaudio_stream<D>::xaudio_stream(const xw::xaudio<T>& audio)
    : base_type()
    {
        set_defaults();

        this->audio() = audio;
    }

    template <class D>
    template <class T>
    inline xaudio_stream<D>::xaudio_stream(xw::xaudio<T>&& audio)
        : base_type()
    {
        set_defaults();

        this->audio() = std::move(audio);
    }

    template <class D>
    inline void xaudio_stream<D>::set_defaults()
    {
        this->_model_name() = "AudioStreamModel";
        this->_view_name() = "AudioStreamView";
    }

    inline audio_stream_generator audio_stream_from_file(const std::string& filename)
    {
        auto vid = xw::audio_from_file(filename).autoplay(false).controls(false).finalize();
        return audio_stream_generator().audio(std::move(vid));
    }

    inline audio_stream_generator audio_stream_from_url(const std::string& url)
    {
        auto vid = xw::audio_from_url(url).autoplay(false).controls(false).finalize();
        return audio_stream_generator().audio(std::move(vid));
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xaudio_stream>;
    extern template xw::xmaterialize<xwebrtc::xaudio_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xaudio_stream>>;
    extern template class xw::xgenerator<xwebrtc::xaudio_stream>;
    extern template xw::xgenerator<xwebrtc::xaudio_stream>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xaudio_stream>>;
#endif

#endif
