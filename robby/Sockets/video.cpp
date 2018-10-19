#include "video.h"

video::video()
{


}

void video::videoStart(){

    qDebug() << "video started";

    loop = g_main_loop_new (NULL, FALSE);

    // setup pipeline
    pipeline = gst_pipeline_new ("pipeline");

    videosrc = gst_element_factory_make ("v4l2src", "source");

    conv = gst_element_factory_make ("videoconvert", "conv");

    enc = gst_element_factory_make("x264enc", "enc");

    pay = gst_element_factory_make("rtph264pay", "pay");

    udp = gst_element_factory_make("udpsink", "udp");

    cap = gst_caps_from_string("video/x-raw,framerate=30/1,height=700,width=1200");

    filter = gst_element_factory_make("capsfilter","filter");

    videoparse = gst_element_factory_make ("h264parse", "videoparse");

    if (!pipeline || !videosrc || !conv || !enc || !pay || !udp || !cap || !filter) {
        g_printerr ("Not all elements could be created.\n");
        qDebug() << pipeline;
        qDebug() << videosrc;
        qDebug() << conv;
        qDebug() << enc;
        qDebug() << pay;
        qDebug() << udp;
        qDebug() << cap;
        qDebug() << filter;

    }

    g_object_set(enc, "bitrate", 4000, NULL);
    g_object_set(enc, "tune", 0x00000004, NULL);
    g_object_set(enc, "speed-preset", 2, NULL);


    g_object_set(G_OBJECT(pay), "config-interval", 1, NULL);

    g_object_set (videosrc, "device", "/dev/video0", NULL);

    g_object_set(G_OBJECT(udp), "host", ip.toString().toLatin1().data(), NULL);

    g_object_set(G_OBJECT(udp), "port", 5000, NULL);

    g_object_set(filter,"caps",cap,NULL);

    gst_bin_add_many (GST_BIN (pipeline), videosrc, filter, conv, enc, videoparse, pay, udp, NULL);

    if (gst_element_link_many (videosrc,filter, conv, enc, videoparse, pay, udp, NULL) != TRUE)
    {
        qDebug() << "error";

    }
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    g_main_loop_run (loop);

    qDebug() << "clean";
    // clean up
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT (pipeline));
    g_main_loop_unref (loop);

}

void video::videoStop(){
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT (pipeline));
    g_main_loop_unref (loop);
}
