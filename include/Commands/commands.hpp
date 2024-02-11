#ifndef COMMANDS_HPP
#define COMMANDS_HPP

/* Applications */
#define VLC                                 "vlc"
#define VSCODE                              "code"
#define TERMINAL                            "gnome-terminal"
#define FIREFOX                             "firefox"
#define WIRESHARK                           "wireshark"
#define TILIX                               "tilix"

/* volume control up/down mute */
#define VOLUME_UP                           "amixer -D pulse sset Master 10%+"     // Increase master volume by 10%
#define VOLUME_DOWN                         "amixer -D pulse sset Master 10%-"     // Decrease master volume by 10%
#define VOLUME_MUTE                         "amixer set Master 0"               // Mute master volume 
#define VOLUME_MAX                          "amixer set Master 100"             // Unmute master volume


#endif