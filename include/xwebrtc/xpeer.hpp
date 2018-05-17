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

#include "xwebrtc_config.hpp"
#include "xmedia_stream.hpp"

namespace xwebrtc
{
    /*********************
     * xpeer declaration *
     *********************/

    template <class D>
    class xpeer : public xwebrtc::xmedia_stream<D>
    {
    public:

        using base_type = xwebrtc::xmedia_stream<D>;
        using derived_type = D;

        using stream_type = xw::xholder<xwebrtc::xmedia_stream>;

        void serialize_state(xeus::xjson&, xeus::buffer_sequence&) const;
        void apply_patch(const xeus::xjson&, const xeus::buffer_sequence&);

        void connect() const;
        void close() const;

        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream_local);
        XPROPERTY(xtl::xoptional<stream_type>, derived_type, stream_remote);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, id_local);
        XPROPERTY(xtl::xoptional<std::string>, derived_type, id_remote);
        XPROPERTY(bool, derived_type, connected, false);
        XPROPERTY(bool, derived_type, failed, false);

    protected:

        xpeer();
        using base_type::base_type;

    private:

        void set_defaults();
    };

    using peer = xw::xmaterialize<xpeer>;

    using peer_generator = xw::xgenerator<xpeer>;

    /************************
     * xpeer implementation *
     ************************/

    template <class D>
    inline void xpeer<D>::serialize_state(xeus::xjson& state, xeus::buffer_sequence& buffers) const
    {
        base_type::serialize_state(state, buffers);

        xw::set_patch_from_property(stream_local, state, buffers);
        xw::set_patch_from_property(stream_remote, state, buffers);
        xw::set_patch_from_property(id_local, state, buffers);
        xw::set_patch_from_property(id_remote, state, buffers);
    }

    template <class D>
    inline void xpeer<D>::apply_patch(const xeus::xjson& patch, const xeus::buffer_sequence& buffers)
    {
        base_type::apply_patch(patch, buffers);

        xw::set_property_from_patch(stream_local, patch, buffers);
        xw::set_property_from_patch(stream_remote, patch, buffers);
        xw::set_property_from_patch(id_local, patch, buffers);
        xw::set_property_from_patch(id_remote, patch, buffers);
        xw::set_property_from_patch(connected, patch, buffers);
        xw::set_property_from_patch(failed, patch, buffers);
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
    inline void xpeer<D>::close() const
    {
        xeus::xjson state;
        xeus::buffer_sequence buffers;
        state["msg"] = "close";
        this->send(std::move(state), std::move(buffers));
    }

    template <class D>
    inline xpeer<D>::xpeer()
        : base_type()
    {
        set_defaults();
    }

    template <class D>
    inline void xpeer<D>::set_defaults()
    {
        this->_model_name() = "WebRTCPeerModel";
        this->_view_name() = "WebRTCPeerView";
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
