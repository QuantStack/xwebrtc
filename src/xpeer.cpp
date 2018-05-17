#include "xwebrtc/xpeer.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xpeer>;
template xw::xmaterialize<xwebrtc::xpeer>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xpeer>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xpeer>;
template xw::xgenerator<xwebrtc::xpeer>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xpeer>>;
