/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_CHAT_HPP
#define XWEBRTC_CHAT_HPP

#include <string>

#include "xcpp/xdisplay.hpp"

#include "xwidgets/xbox.hpp"
#include "xwidgets/xlink.hpp"

#include "xwebrtc_config.hpp"
#include "xroom_mqtt.hpp"
#include "xmedia_stream.hpp"
#include "xcamera_stream.hpp"

namespace xwebrtc
{
    namespace detail
    {
        template <class CT>
        struct xchat_room
        {
        public:

            template <class T>
            inline xchat_room(const std::string& room_name, T&& input_stream)
            : room_name(room_name), stream(std::forward<T>(input_stream)),
            room(room_mqtt_generator().stream(std::forward<T>(input_stream)).room(room_name).finalize()),
            box(xw::hbox()),
            link(xw::link(room, "streams", box, "children"))
            {
            }

            const std::string& room_name;
            CT stream;
            room_mqtt room;
            xw::hbox box;
            xw::link link;
        };
    }

    template <class T>
    inline auto chat(const std::string& room_name, T&& stream)
    {
        auto room = detail::xchat_room<T>(room_name, std::forward<T>(stream));
        xcpp::display(room.box);
        return room;
    }
}

#endif
