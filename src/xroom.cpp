#include "xwebrtc/xroom.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xroom>;
template xw::xmaterialize<xwebrtc::xroom>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xroom>>;
