#include "xwebrtc/xmedia_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xmedia_stream>;
template xw::xmaterialize<xwebrtc::xmedia_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xmedia_stream>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xmedia_stream>;
template xw::xgenerator<xwebrtc::xmedia_stream>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xmedia_stream>>;
