#include "HardwareSerial.h"
#include <map>

#ifndef MEDIA_KEY
#define MEDIA_KEY

enum MediaKeyCode
{
    NEXT_TRACK,
    PREVIOUS_TRACK,
    STOP,
    PLAY_PAUSE,
    MUTE,
    VOLUME_UP,
    VOLUME_DOWN,
    WWW_HOME,
    LOCAL_MACHINE_BROWSER,
    CALCULATOR,
    WWW_BOOKMARKS,
    WWW_SEARCH,
    WWW_STOP,
    WWW_BACK,
    CONSUMER_CONTROL_CONFIGURATION,
    POWER
};

static const std::map<const MediaKeyCode, const std::string> mediaKeyToTextValue = {
    {NEXT_TRACK, "mk_next_track"},
    {PREVIOUS_TRACK, "mk_prev_track"},
    {STOP, "mk_stop"},
    {PLAY_PAUSE, "mk_play_pause"},
    {MUTE, "mk_mute"},
    {VOLUME_UP, "mk_vol_up"},
    {VOLUME_DOWN, "mk_vol_down"},
    {WWW_HOME, "mk_www_home"},
    {LOCAL_MACHINE_BROWSER, "mk_local_machine_browser"},
    {CALCULATOR, "mk_calculator"},
    {WWW_BOOKMARKS, "mk_www_bookmarks"},
    {WWW_SEARCH, "mk_www_search"},
    {WWW_STOP, "mk_www_stop"},
    {WWW_BACK, "mk_www_back"},
    {CONSUMER_CONTROL_CONFIGURATION, "mk_consumer_control_config"},
    {POWER, "mk_power"}};

static std::string mediaKeyReportToText(const MediaKeyCode mediaKeyCode)
{
    auto entry = mediaKeyToTextValue.find(mediaKeyCode);
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