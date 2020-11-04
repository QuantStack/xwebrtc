/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_ROOM_HPP
#define XWEBRTC_ROOM_HPP

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xobject.hpp"
#include "xwidgets/xmaker.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"
#include "xpeer.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /*********************
     * xroom declaration *
     *********************/

    template <class D>
    class xroom : public xw::xobject<D>
    {
    public:

        using base_type = xw::xobject<D>;
        using derived_type = D;

        using stream_type = xw::xholder;
        using stream_list_type = std::vector<stream_type>;
        using peer_list_type = std::vector<xw::xholder>;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, room, "room");
        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream);
        XPROPERTY(std::string, derived_type, room_id);
        XPROPERTY(std::string, derived_type, nickname, "anonymous");
        XPROPERTY(peer_list_type, derived_type, peers, {});
        XPROPERTY(stream_list_type, derived_type, streams, {});

    protected:

        xroom();
        using base_type::base_type;

    private:

        void set_defaults();

        static int register_peers();
    };

    using room = xw::xmaterialize<xroom>;

    /************************
     * xroom implementation *
     ************************/

    template <class D>
    inline void xroom<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(room(), state["room"], buffers);
        xwidgets_serialize(stream(), state["stream"], buffers);
        xwidgets_serialize(nickname(), state["nickname"], buffers);
        xwidgets_serialize(peers(), state["peers"], buffers);
        xwidgets_serialize(streams(), state["streams"], buffers);
    }

    template <class D>
    inline void xroom<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(room, patch, buffers);
        set_property_from_patch(stream, patch, buffers);
        set_property_from_patch(room_id, patch, buffers);
        set_property_from_patch(nickname, patch, buffers);
        set_property_from_patch(peers, patch, buffers);
        set_property_from_patch(streams, patch, buffers);
    }

    template <class D>
    inline xroom<D>::xroom()
        : base_type()
    {
        static int init = register_peers();
        set_defaults();
    }

    template <class D>
    inline void xroom<D>::set_defaults()
    {
        this->_model_module() = "jupyter-webrtc";
        this->_view_module() = "jupyter-webrtc";
        this->_model_name() = "WebRTCRoomModel";
        // this->_view_name() = "WebRTCRoomView";
        this->_model_module_version() = jupyter_webrtc_semver();
        this->_view_module_version() = jupyter_webrtc_semver();
    }

    template <class D>
    inline int xroom<D>::register_peers()
    {
        xw::get_xfactory().register_maker(
            "jupyter-webrtc",
            "WebRTCPeerModel",
            "jupyter-webrtc",
            "WebRTCPeerView",
            xw::xmaker<xpeer>
        );

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
    extern template class xw::xmaterialize<xwebrtc::xroom>;
    extern template xw::xmaterialize<xwebrtc::xroom>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xroom>>;
#endif

#endif
