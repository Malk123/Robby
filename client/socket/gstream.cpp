#include "gstream.h"

/**
 * @brief Gstream::Gstream
 * @param parent
 */
Gstream::Gstream(QObject *parent) : QObject(parent)
{
    pipeline = gst_parse_launch ("udpsrc port=5000 caps = \"application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96\" ! rtph264depay ! decodebin ! xvimagesink name=robbysink", NULL);
}

/**
 * @brief Gstream::startGstreamer
 */
void Gstream::startGstreamer(){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    sink = gst_bin_get_by_name( GST_BIN( pipeline ), "robbysink" );
    gst_video_overlay_set_window_handle( GST_VIDEO_OVERLAY( sink ), xwinid );
    gst_object_unref( sink );
}

/**
 * @brief Gstream::stopGstreamer
 */
void Gstream::stopGstreamer(){
    gst_element_set_state (pipeline, GST_STATE_PAUSED);
}
