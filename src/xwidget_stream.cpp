#include "xwebrtc/xwidget_stream.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xwidget_stream>;
template xw::xmaterialize<xwebrtc::xwidget_stream>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xwidget_stream>>;
