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

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"
#include "xwidgets/xwidget.hpp"

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"
#include "xpeer.hpp"

namespace xwebrtc
{
    /*********************
     * xroom declaration *
     *********************/

    template <class D>
    class xroom : public xw::xwidget<D>
    {
    public:

        using base_type = xw::xwidget<D>;
        using derived_type = D;

        using stream_type = xw::xholder<xmedia_stream>;
        using stream_list_type = std::vector<stream_type>;
        using peer_list_type = std::vector<xw::xholder<xpeer>>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void close() const;

        XPROPERTY(std::string, derived_type, room, "room");
        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream);
        XPROPERTY(std::string, derived_type, id);
        XPROPERTY(std::string, derived_type, nickname, "anonymous");
        XPROPERTY(peer_list_type, derived_type, peers, {});
        XPROPERTY(stream_list_type, derived_type, streams, {});

    protected:

        xroom();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using room = xw::xmaterialize<xroom>;

    using room_generator = xw::xgenerator<xroom>;

    /************************
     * xroom implementation *
     ************************/

    template <class D>
    inline void xroom<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(room, state, buffers);
        xw::set_patch_from_property(stream, state, buffers);
        xw::set_patch_from_property(nickname, state, buffers);
        xw::set_patch_from_property(peers, state, buffers);
        xw::set_patch_from_property(streams, state, buffers);
    }

    template <class D>
    inline void xroom<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(room, patch, buffers);
        xw::set_property_from_patch(stream, patch, buffers);
        xw::set_property_from_patch(id, patch, buffers);
        xw::set_property_from_patch(nickname, patch, buffers);
        xw::set_property_from_patch(peers, patch, buffers);
        xw::set_property_from_patch(streams, patch, buffers);
    }

    template <class D>
    inline void xroom<D>::close() const
    {
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        state["msg"] = "close";
        this->send(std::move(state), std::move(buffers));
    }

    template <class D>
    inline xroom<D>::xroom()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xroom<D>::set_defaults()
    {
        this->_model_module() = "jupyter-webrtc";
        // this->_view_module() = "jupyter-webrtc";
        this->_model_name() = "WebRTCRoomModel";
        // this->_view_name() = "WebRTCRoomView";
        this->_model_module_version() = XJUPYTER_WEBRTC_VERSION;
        // this->_view_module_version() = XJUPYTER_WEBRTC_VERSION;
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xroom>;
    extern template xw::xmaterialize<xwebrtc::xroom>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xroom>>;
    extern template class xw::xgenerator<xwebrtc::xroom>;
    extern template xw::xgenerator<xwebrtc::xroom>::xgenerator();
    extern template class xw::xtransport<xw::xgenerator<xwebrtc::xroom>>;
#endif

#endif
