/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_IMAGE_STREAM_HPP
#define XWEBRTC_IMAGE_STREAM_HPP

#include <string>
#include <stdexcept>

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/ximage.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace xwebrtc
{
    /*****************************
     * ximage_stream declaration *
     *****************************/

    template <class D>
    class ximage_stream : public xmedia_stream<D>
    {
    public:

        using base_type = xmedia_stream<D>;
        using derived_type = D;

        using image_type = xw::xholder<xw::ximage>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        XPROPERTY(image_type, derived_type, image);

    protected:

        ximage_stream();
        ximage_stream(const xw::xholder<xw::ximage>& image);
        ximage_stream(xw::xholder<xw::ximage>&& image);
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using image_stream = xw::xmaterialize<ximage_stream>;

    using image_stream_generator = xw::xgenerator<ximage_stream>;

    /********************************
     * ximage_stream implementation *
     ********************************/

    template <class D>
    inline void ximage_stream<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        using xw::set_patch_from_property;
        base_type::serialize_state(state, buffers);

        set_patch_from_property(image, state, buffers);
    }

    template <class D>
    inline void ximage_stream<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(image, patch, buffers);
    }

    template <class D>
    inline ximage_stream<D>::ximage_stream()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline ximage_stream<D>::ximage_stream(const xw::xholder<xw::ximage>& image)
        : base_type()
    {
        set_defaults();

        this->image() = image;
    }

    template <class D>
    inline ximage_stream<D>::ximage_stream(xw::xholder<xw::ximage>&& image)
        : base_type()
    {
        set_defaults();

        this->image() = std::move(image);
    }

    template <class D>
    inline void ximage_stream<D>::set_defaults()
    {
        this->_model_name() = "ImageStreamModel";
        // this->_view_name() = "ImageStreamView";
    }

    inline image_stream_generator image_stream_from_file(const std::string& filename)
    {
        auto img = xw::image_from_file(filename).finalize();
        return image_stream_generator().image(std::move(img));
    }

    inline image_stream_generator image_stream_from_url(const std::string& url)
    {
        auto img = xw::image_from_url(url).finalize();
        return image_stream_generator().image(std::move(img));
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::ximage_stream>;
    extern template xw::xmaterialize<xwebrtc::ximage_stream>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::ximage_stream>>;
    extern template class xw::xgenerator<xwebrtc::ximage_stream>;
    extern template xw::xgenerator<xwebrtc::ximage_stream>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::ximage_stream>>;
#endif

#endif
