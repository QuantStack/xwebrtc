#include "xwebrtc/ximage_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::ximage_stream>;
template xw::xmaterialize<xwebrtc::ximage_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::ximage_stream>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::ximage_stream>;
template xw::xgenerator<xwebrtc::ximage_stream>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::ximage_stream>>;
