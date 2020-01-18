/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_AUDIO_RECORDER_HPP
#define XWEBRTC_AUDIO_RECORDER_HPP

#include <string>
#include <utility>

#include "nlohmann/json.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xaudio.hpp"

#include "xrecorder.hpp"
#include "xwebrtc_config.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*******************************
     * xaudio_recorder declaration *
     *******************************/

    template <class D>
    class xaudio_recorder : public xrecorder<D>
    {
    public:

        using base_type = xrecorder<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(xw::audio, derived_type, audio);

        void save(const std::string& filename = "") const;

    protected:

        xaudio_recorder();
        xaudio_recorder(xw::xholder<xmedia_stream> audio);
        using base_type::base_type;

    private:

        void set_defaults();
        void setup_properties();
    };

    using audio_recorder = xw::xmaterialize<xaudio_recorder>;

    /**********************************
     * xaudio_recorder implementation *
     **********************************/

    template <class D>
    inline void xaudio_recorder<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(audio(), state["audio"], buffers);
    }

    template <class D>
    inline void xaudio_recorder<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(audio, patch, buffers);
    }

    template <class D>
    inline void xaudio_recorder<D>::save(const std::string& filename) const
    {
        this->save_file(filename, this->audio().value().cbegin(), this->audio().value().cend());
    }

    template <class D>
    inline xaudio_recorder<D>::xaudio_recorder()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    inline xaudio_recorder<D>::xaudio_recorder(xw::xholder<xmedia_stream> audio)
        : base_type()
    {
        this->stream() = audio;

        set_defaults();

        this->setup_properties();
    }

    // template <class D>
    // template <class T>
    // inline xaudio_recorder<D>::xaudio_recorder(xaudio_recorder<T>&& rhs) noexcept
    //     : base_type(rhs), audio(std::move(rhs.audio())), format(std::move(rhs.format())),
    //       _width(std::move(rhs._width())), _height(std::move(rhs._height()))
    // {
    //     this->setup_properties();
    // }

    template <class D>
    inline void xaudio_recorder<D>::set_defaults()
    {
        this->_model_name() = "AudioRecorderModel";
        this->_view_name() = "AudioRecorderView";

        this->audio() = xw::audio::initialize().format(this->format()).finalize();
    }

    template <class D>
    inline void xaudio_recorder<D>::setup_properties()
    {
        this->observe("format", [](auto& owner) {
            owner.audio().format() = owner.format();
        });
        this->audio().observe("value", [this](auto& owner) {
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
    extern template class xw::xmaterialize<xwebrtc::xaudio_recorder>;
    extern template xw::xmaterialize<xwebrtc::xaudio_recorder>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xaudio_recorder>>;
#endif

#endif
