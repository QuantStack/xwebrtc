#include "xwebrtc/ximage_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::ximage_stream>;
template xw::xmaterialize<xwebrtc::ximage_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::ximage_stream>>;
