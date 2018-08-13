/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_IMAGE_RECORDER_HPP
#define XWEBRTC_IMAGE_RECORDER_HPP

#include <string>
#include <vector>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/ximage.hpp"

#include "xrecorder.hpp"
#include "xwebrtc_config.hpp"

namespace xwebrtc
{
    /*******************************
     * ximage_recorder declaration *
     *******************************/

    template <class D>
    class ximage_recorder : public xrecorder<D>
    {
    public:

        using base_type = xrecorder<D>;
        using derived_type = D;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(xw::image, derived_type, image);
        XPROPERTY(std::string, derived_type, format, "png");
        XPROPERTY(std::string, derived_type, _width, "");
        XPROPERTY(std::string, derived_type, _height, "");

        void save(const std::string& filename = "") const;

    protected:

        ximage_recorder();
        template <class T>
        ximage_recorder(const xmedia_stream<T>& video);
        template <class T>
        ximage_recorder(xmedia_stream<T>&& video);
        // template <class T>
        // ximage_recorder(ximage_recorder<T>&& rhs) noexcept;
        using base_type::base_type;

    private:

        void set_defaults();
        void setup_properties();
    };

    using image_recorder = xw::xmaterialize<ximage_recorder>;

    using image_recorder_generator = xw::xgenerator<ximage_recorder>;

    /**********************************
     * ximage_recorder implementation *
     **********************************/

    template <class D>
    inline void ximage_recorder<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        using xw::set_patch_from_property;
        base_type::serialize_state(state, buffers);

        set_patch_from_property(image, state, buffers);
        set_patch_from_property(format, state, buffers);
        set_patch_from_property(_width, state, buffers);
        set_patch_from_property(_height, state, buffers);
    }

    template <class D>
    inline void ximage_recorder<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(image, patch, buffers);
        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(_width, patch, buffers);
        set_property_from_patch(_height, patch, buffers);
    }

    template <class D>
    inline void ximage_recorder<D>::save(const std::string& filename) const
    {
        this->save_file(filename, this->image().value().cbegin(), this->image().value().cend());
    }

    template <class D>
    inline ximage_recorder<D>::ximage_recorder()
        : base_type()
    {
        set_defaults();

        this->setup_properties();
    }

    template <class D>
    template <class T>
    inline ximage_recorder<D>::ximage_recorder(xmedia_stream<T>&& video)
        : base_type()
    {
        this->stream() = std::move(video);

        set_defaults();

        this->setup_properties();
    }

    template <class D>
    template <class T>
    inline ximage_recorder<D>::ximage_recorder(const xmedia_stream<T>& video)
        : base_type()
    {
        this->stream() = video;

        set_defaults();

        this->setup_properties();
    }

    // template <class D>
    // template <class T>
    // inline ximage_recorder<D>::ximage_recorder(ximage_recorder<T>&& rhs) noexcept
    //     : base_type(rhs), image(std::move(rhs.image())), format(std::move(rhs.format())),
    //       _width(std::move(rhs._width())), _height(std::move(rhs._height()))
    // {
    //     this->setup_properties();
    // }

    template <class D>
    inline void ximage_recorder<D>::set_defaults()
    {
        this->_model_name() = "ImageRecorderModel";
        this->_view_name() = "ImageRecorderView";

        this->image() = xw::image_generator()
            .format(this->format())
            .height(this->_height())
            .width(this->_width())
            .finalize();
    }

    template <class D>
    inline void ximage_recorder<D>::setup_properties()
    {
        auto self = this->self();
        self->template observe<decltype(self->_width)>([](auto& owner) {
            owner.image().width() = owner._width();
        });
        self->template observe<decltype(self->_height)>([](auto& owner) {
            owner.image().height() = owner._height();
        });
        self->template observe<decltype(self->format)>([](auto& owner) {
            owner.image().format() = owner.format();
        });
        self->image().template observe<decltype(self->image().value)>([self](auto& owner) {
            if (self->autosave() && owner.value().size() != 0)
            {
                self->save_file("", owner.value().cbegin(), owner.value().cend());
            }
        });
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::ximage_recorder>;
    extern template xw::xmaterialize<xwebrtc::ximage_recorder>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::ximage_recorder>>;
    extern template class xw::xgenerator<xwebrtc::ximage_recorder>;
    extern template xw::xgenerator<xwebrtc::ximage_recorder>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::ximage_recorder>>;
#endif

#endif
