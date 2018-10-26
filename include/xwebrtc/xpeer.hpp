/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_PEER_HPP
#define XWEBRTC_PEER_HPP

#include <string>

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xobject.hpp"
#include "xwidgets/xmaker.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace xwebrtc
{
    /*********************
     * xpeer declaration *
     *********************/

    template <class D>
    class xpeer : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        using stream_type = xw::xholder<xmedia_stream>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void connect() const;

        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream_local);
        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream_remote);
        XPROPERTY(std::string, derived_type, id_local);
        XPROPERTY(std::string, derived_type, id_remote);
        XPROPERTY(bool, derived_type, connected, false);
        XPROPERTY(bool, derived_type, failed, false);

    protected:

        xpeer();
        using base_type::base_type;

    private:

        void set_defaults();

        static int register_media_streams();
    };

    using peer = xw::xmaterialize<xpeer>;

    using peer_generator = xw::xgenerator<xpeer>;

    /************************
     * xpeer implementation *
     ************************/

    template <class D>
    inline void xpeer<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        using xw::set_patch_from_property;
        base_type::serialize_state(state, buffers);

        set_patch_from_property(stream_local, state, buffers);
        set_patch_from_property(stream_remote, state, buffers);
        set_patch_from_property(id_local, state, buffers);
        set_patch_from_property(id_remote, state, buffers);
    }

    template <class D>
    inline void xpeer<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(stream_local, patch, buffers);
        set_property_from_patch(stream_remote, patch, buffers);
        set_property_from_patch(id_local, patch, buffers);
        set_property_from_patch(id_remote, patch, buffers);
        set_property_from_patch(connected, patch, buffers);
        set_property_from_patch(failed, patch, buffers);
    }

    template <class D>
    inline void xpeer<D>::connect() const
    {
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        state["msg"] = "connect";
        this->send(std::move(state), std::move(buffers));
    }

    template <class D>
    inline xpeer<D>::xpeer()
        : base_type()
    {
        static int init = register_media_streams();
        set_defaults();
    }

    template <class D>
    inline void xpeer<D>::set_defaults()
    {
        this->_model_module() = "jupyter-webrtc";
        this->_view_module() = "jupyter-webrtc";
        this->_model_name() = "WebRTCPeerModel";
        this->_view_name() = "WebRTCPeerView";
        this->_model_module_version() = ipywebrtc_semver();
        this->_view_module_version() = ipywebrtc_semver();
    }

    template <class D>
    inline int xpeer<D>::register_media_streams()
    {
        xw::get_xfactory().register_maker(
            "jupyter-webrtc",
            "MediaStreamModel",
            "jupyter-webrtc",
            "MediaStreamView",
            xw::xmaker<xmedia_stream>
        );

        return 0;
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xpeer>;
    extern template xw::xmaterialize<xwebrtc::xpeer>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xpeer>>;
    extern template class xw::xgenerator<xwebrtc::xpeer>;
    extern template xw::xgenerator<xwebrtc::xpeer>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xpeer>>;
#endif

#endif
