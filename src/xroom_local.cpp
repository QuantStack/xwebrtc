#include "xwebrtc/xroom_local.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xroom_local>;
template xw::xmaterialize<xwebrtc::xroom_local>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xroom_local>>;
