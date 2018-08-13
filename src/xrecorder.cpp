#include "xwebrtc/xrecorder.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xrecorder>;
template xw::xmaterialize<xwebrtc::xrecorder>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xrecorder>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xrecorder>;
template xw::xgenerator<xwebrtc::xrecorder>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xrecorder>>;
