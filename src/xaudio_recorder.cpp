#include "xwebrtc/xaudio_recorder.hpp"

template class XWEBRTC_API xw::xmaterialize<xwebrtc::xaudio_recorder>;
template xw::xmaterialize<xwebrtc::xaudio_recorder>::xmaterialize();
template class XWEBRTC_API xw::xtransport<xw::xmaterialize<xwebrtc::xaudio_recorder>>;
