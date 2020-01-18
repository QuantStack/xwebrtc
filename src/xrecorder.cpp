#include "xwebrtc/xrecorder.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xrecorder>;
template xw::xmaterialize<xwebrtc::xrecorder>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xrecorder>>;
