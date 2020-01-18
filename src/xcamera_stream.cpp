#include "xwebrtc/xcamera_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xcamera_stream>;
template xw::xmaterialize<xwebrtc::xcamera_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xcamera_stream>>;
