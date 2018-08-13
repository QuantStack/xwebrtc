#include "xwebrtc/xvideo_recorder.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xvideo_recorder>;
template xw::xmaterialize<xwebrtc::xvideo_recorder>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xvideo_recorder>>;
template class XWEBRTC_API xw::xgenerator<xwebrtc::xvideo_recorder>;
template xw::xgenerator<xwebrtc::xvideo_recorder>::xgenerator();
template class XWEBRTC_API xw::xtransport<xw::xgenerator<xwebrtc::xvideo_recorder>>;
