/******************************************************************************
* Copyright (c) 2018, Sylvain Corlay and Johan Mabille, Wolf Vollprecht and   *
* Martin Renou                                                                *
*                                                                             *
* Distributed under the terms of the BSD 3-Clause License.                    *
*                                                                             *
* The full license is in the file LICENSE, distributed with this software.    *
*******************************************************************************/

#ifndef XWEBRTC_ROOM_LOCAL_HPP
#define XWEBRTC_ROOM_LOCAL_HPP

#include "nlohmann/json.hpp"

#include "xtl/xoptional.hpp"

#include "xwidgets/xmaterialize.hpp"
#include "xwidgets/xholder.hpp"

#include "xwebrtc_config.hpp"
#include "xroom.hpp"

namespace nl = nlohmann;

namespace xwebrtc
{
    /***************************
     * xroom_local declaration *
     ***************************/

    template <class D>
    class xroom_local : public xroom<D>
    {
    public:

        using base_type = xroom<D>;
        using derived_type = D;

        void serialize_state(nl::json&, xeus::buffer_sequence&) const;
        void apply_patch(const nl::json&, const xeus::buffer_sequence&);

    protected:

        xroom_local();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using room_local = xw::xmaterialize<xroom_local>;

    /******************************
     * xroom_local implementation *
     ******************************/

    template <class D>
    inline void xroom_local<D>::serialize_state(nl::json& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);
    }

    template <class D>
    inline void xroom_local<D>::apply_patch(const nl::json& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);
    }

    template <class D>
    inline xroom_local<D>::xroom_local()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xroom_local<D>::set_defaults()
    {
        this->_model_name() = "WebRTCRoomLocalModel";
        // this->_view_name() = "WebRTCRoomLocalView";
    }
}

/*********************
 * precompiled types *
 *********************/

    extern template class xw::xmaterialize<xwebrtc::xroom_local>;
    extern template class xw::xtransport<xw::xmaterialize<xwebrtc::xroom_local>>;

#endif
