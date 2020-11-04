/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_RECORDER_HPP
#define XWEBRTC_RECORDER_HPP

#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "nlohmann/json.hpp"

#include "xproperty/xobserved.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xwidget.hpp"

#include "xmedia_stream.hpp"
#include "xwebrtc_config.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*************************
     * xrecorder declaration *
     *************************/

    template <class D>
    class xrecorder : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using media_stream_type = xw::xholder;
        using data_type = std::vector<char>;
        using data_const_iterator = typename data_type::const_iterator;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(media_stream_type, derived_type, stream);
        XPROPERTY(std::string, derived_type, filename, "record");
        XPROPERTY(std::string, derived_type, format, "webm");
        XPROPERTY(bool, derived_type, recording, false);
        XPROPERTY(bool, derived_type, autosave, false);
        XPROPERTY(std::string, derived_type, _data_src);

        const std::vector<xw::xjson_path_type>& buffer_paths() const;
        void download() const;
        void save_file(const std::string& filename, data_const_iterator begin, data_const_iterator end) const;

    protected:

        xrecorder();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using recorder = xw::xmaterialize<xrecorder>;

    /****************************
     * xrecorder implementation *
     ****************************/

    template <class D>
    inline void xrecorder<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(stream(), state["stream"], buffers);
        xwidgets_serialize(filename(), state["filename"], buffers);
        xwidgets_serialize(format(), state["format"], buffers);
        xwidgets_serialize(recording(), state["recording"], buffers);
        xwidgets_serialize(autosave(), state["autosave"], buffers);
        xwidgets_serialize(_data_src(), state["_data_src"], buffers);
    }

    template <class D>
    inline void xrecorder<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(stream, patch, buffers);
        set_property_from_patch(filename, patch, buffers);
        set_property_from_patch(format, patch, buffers);
        set_property_from_patch(recording, patch, buffers);
        set_property_from_patch(autosave, patch, buffers);
        set_property_from_patch(_data_src, patch, buffers);
    }

    template <class D>
    inline const std::vector<xw::xjson_path_type>& xrecorder<D>::buffer_paths() const
    {
        static const std::vector<xw::xjson_path_type> default_buffer_paths = {{"data"}};
        return default_buffer_paths;
    }

    template <class D>
    inline void xrecorder<D>::download() const
    {
        nl::json state;
        xeus::buffer_sequence buffers;
        state["msg"] = "download";
        this->send(std::move(state), std::move(buffers));
    }

    template <class D>
    inline xrecorder<D>::xrecorder()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xrecorder<D>::save_file(const std::string& filename, data_const_iterator begin, data_const_iterator end) const
    {
        std::ofstream file;
        std::string name;
        if (filename.size() == 0)
        {
            name = this->filename();
        }
        else
        {
            name = filename;
        }

        if (name.find('.') != std::string::npos)
        {
            file.open(name, std::ios::binary);
        }
        else
        {
            name.append(1, '.');
            name.append(this->derived_cast().format());
            file.open(name, std::ios::binary);
        }
        std::string data(begin, end);
        file << data;
        file.close();
    }

    template <class D>
    inline void xrecorder<D>::set_defaults()
    {
        this->_model_module() = "jupyter-webrtc";
        this->_view_module() = "jupyter-webrtc";
        this->_model_module_version() = jupyter_webrtc_semver();
        this->_view_module_version() = jupyter_webrtc_semver();
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xwebrtc::xrecorder>;
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xrecorder>>;

#endif
