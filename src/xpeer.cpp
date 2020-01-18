#include "xwebrtc/xpeer.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xpeer>;
template xw::xmaterialize<xwebrtc::xpeer>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xpeer>>;
