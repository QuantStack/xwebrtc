#include "xwebrtc/xroom_local.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xroom_local>;
template xw::xmaterialize<xwebrtc::xroom_local>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xroom_local>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xroom_local>;
template xw::xgenerator<xwebrtc::xroom_local>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xroom_local>>;
