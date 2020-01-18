/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_ROOM_MQTT_HPP
#define XWEBRTC_ROOM_MQTT_HPP

#include <string>

#include "nlohmann/json.hpp"

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"

#include "xwebrtc_config.hpp"
#include "xroom.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /**************************
     * xroom_mqtt declaration *
     **************************/

    template <class D>
    class xroom_mqtt : public xroom<D>
    {
    public:

        using base_type = xroom<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

        XPROPERTY(std::string, derived_type, server, "wss://iot.eclipse.org:443/ws");

    protected:

        xroom_mqtt();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using room_mqtt = xw::xmaterialize<xroom_mqtt>;

    /*****************************
     * xroom_mqtt implementation *
     *****************************/

    template <class D>
    inline void xroom_mqtt<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        using xw::xwidgets_serialize;
        base_type::serialize_state(state, buffers);

        xwidgets_serialize(server(), state["server"], buffers);
    }

    template <class D>
    inline void xroom_mqtt<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        using xw::set_property_from_patch;
        base_type::apply_patch(patch, buffers);

        set_property_from_patch(server, patch, buffers);
    }

    template <class D>
    inline xroom_mqtt<D>::xroom_mqtt()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xroom_mqtt<D>::set_defaults()
    {
        this->_model_name() = "WebRTCRoomMqttModel";
        // this->_view_name() = "WebRTCRoomMqttView";
    }
}

/*********************
 * precompiled types *
 *********************/

#ifndef _WIN32
    extern template class xw::xmaterialize<xwebrtc::xroom_mqtt>;
    extern template xw::xmaterialize<xwebrtc::xroom_mqtt>::xmaterialize();
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xroom_mqtt>>;
#endif

#endif
