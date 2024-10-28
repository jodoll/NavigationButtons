#include "HardwareSerial.h"
#include "BleKeyboard.h"

#ifndef MEDIA_KEY
#define MEDIA_KEY

static const std::map<const MediaKeyReport *, const std::string> mediaKeyToTextValue = {
    {&KEY_MEDIA_NEXT_TRACK, "mk_next_track"},
    {&KEY_MEDIA_PREVIOUS_TRACK, "mk_prev_track"},
    {&KEY_MEDIA_STOP, "mk_stop"},
    {&KEY_MEDIA_PLAY_PAUSE, "mk_play_pause"},
    {&KEY_MEDIA_MUTE, "mk_mute"},
    {&KEY_MEDIA_VOLUME_UP, "mk_vol_up"},
    {&KEY_MEDIA_VOLUME_DOWN, "mk_vol_down"},
    {&KEY_MEDIA_WWW_HOME, "mk_www_home"},
    {&KEY_MEDIA_LOCAL_MACHINE_BROWSER, "mk_local_machine_browser"},
    {&KEY_MEDIA_CALCULATOR, "mk_calculator"},
    {&KEY_MEDIA_WWW_BOOKMARKS, "mk_www_bookmarks"},
    {&KEY_MEDIA_WWW_SEARCH, "mk_www_search"},
    {&KEY_MEDIA_WWW_STOP, "mk_www_stop"},
    {&KEY_MEDIA_WWW_BACK, "mk_www_back"},
    {&KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION, "mk_consumer_control_config"},
    {&KEY_MEDIA_POWER, "mk_power"}};

static std::string mediaKeyReportToText(const MediaKeyReport *mediaKeyReport)
{
    auto entry = mediaKeyToTextValue.find(mediaKeyReport);
    if (entry != mediaKeyToTextValue.end())
    {
        return entry->second;
    }
    else
    {
        if (DEBUG)
            Serial.println("Failed to match mediaKeyReport to text representation");
        return "unknown";
    }
}

#endif