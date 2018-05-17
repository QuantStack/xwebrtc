#include "xwebrtc/xvideo_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xvideo_stream>;
template xw::xmaterialize<xwebrtc::xvideo_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xvideo_stream>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xvideo_stream>;
template xw::xgenerator<xwebrtc::xvideo_stream>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xvideo_stream>>;
