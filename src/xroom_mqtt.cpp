#include "xwebrtc/xroom_mqtt.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xroom_mqtt>;
template xw::xmaterialize<xwebrtc::xroom_mqtt>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xroom_mqtt>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xroom_mqtt>;
template xw::xgenerator<xwebrtc::xroom_mqtt>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xroom_mqtt>>;
