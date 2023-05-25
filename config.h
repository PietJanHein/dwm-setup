/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;
static const int swallowfloating    = 0;
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "jetbrains:size=20" };
static const char dmenufont[]       = "jetbrains:size=20";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#70327e"; //color of the titlepart of the panel
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging, add or remove tags in this array, name those whatever you want including emoticons, hotkeys for it are defined below the bottom of this file */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/*In this array you can set how programs should open: on which workspace (tags mask), on which monitor, floating or not, swallow it or not */
	/* class      instance    title       tags mask     isfloating	   isterminal	noswallow   	monitor */
	{ "Gimp",       NULL,       NULL,       0,            1,           0,		0,		-1 },
        { "steam",      NULL,       NULL,       1 << 8,	      0,           0,		0,		-1 }, // the update window for steam is not included, it has a different name for the class. Find the name of that window with xprop (and then clicking on it) if you wish to send that to another workspace to get out of your way while you open it and have to wait 
	{ "Lutris",     NULL,       NULL,       1 << 8,	      0,           0,		0,		-1 },
	{ "Kotatogram", NULL,	    NULL,       1 << 2,       0,           0,		0,		-1 },
	{ "Telegram",   NULL,	    NULL,       1 << 2,       0,           0,		0,		-1 },
        { "Deadbeef",   NULL,       NULL,       1 << 9,       0,           0,		0,		-1 },
	{ "Alacritty",  NULL,       "Alacritty",0,	      0,           1,           0,		-1 }, /* this is to enable swallowing in Alacritty */
	{ "Kitty",      NULL,       "Kitty",    0,            0,           1,           0,              -1 }, /* Kitty was not tested, this line is only provided as a service. Use xprop to find othe correct names if this would not work, if this does not work try to uncapitalize it and/or try t remove one of the two, that most likely would make it work. 
							
	{ NULL,         NULL,       "Event Tester", 0,        0,           0,           1,              -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size vs stack size [0.05..0.95] */
static const float smfact    = 0.00; /* horizontal split between two windows in the stack area */
static const int nmaster     = 1;    /* default number of clients in master area, can be increased on the fly with windows+d/i */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = { /* here you choose the symbols to point out the chosen layout in the panel, more layouts can be added with patches and those patches also point out how to modify this file  */
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions, here the hotkeys for the basic workspaces-associated functions are defined, respectively select workspace,  add another worksapce, send program to another workspace and show the program(s) on the current workspace on the selected workspace(s) */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* Thanks to defining here with a shorthand notation how to execute a command in the shell lower in the file you have to write less and it makes the code more easily readable */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
/* if you would want to use rofi or another terminal then you can change it here */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c" /*extra included file which contains the code  to swap two programs between two workspaces (opposite to rotating all the programs over all the windows) */

/* Here all the extra hotkeys, just copy based on examples with the spawn-function which you see here if you want to add hotkeys for extra programs. */ 
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask|ShiftMask,        XK_d,      spawn,          {.v = dmenucmd } }, // open dmenu, by default on the top of the screen (this hotkey was chosen because it is more erconomical if you use the d-key 
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } }, // open terminal, terminal is chosen higher in the file
	{ MODKEY,                       XK_b,      togglebar,      {0} }, // toggle show/hide panel
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } }, // rotate programs over windows
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, // change focus to another window on that workspace
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      movestack,      {.i = +1 } }, // switch programs between only two windows on that workspace
	{ MODKEY|ShiftMask,             XK_u,      movestack,      {.i = -1 } }, 
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, // increase number of windows in the master-area
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, // change vertical split-ratio between master and stack
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setsmfact,      {.f = +0.05} }, //change horizontal split-ratio between programs in the stack-area (not functional for master-area)
	{ MODKEY|ShiftMask,             XK_l,      setsmfact,      {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} }, // switch to last used workspace
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, // kill program, window gets removed
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tiled master/stack layout
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // only show selected window on that workspace
	{ MODKEY,                       XK_space,  setlayout,      {0} }, // switch between two layouts
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /*select other monitor*/
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /*select other monitor in the other direction */
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /*move program to another monitor*/
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
    // you can use both XK_* or a hexadecmial code to define a key in the second column, find the hexadecmial code with xev (X11 only)
    { Mod1Mask|ControlMask,              XK_f,      spawn,          SHCMD("pcmanfm") },
    { Mod1Mask|ControlMask|ShiftMask,    XK_f,      spawn,          SHCMD("firefox") },
    { Mod1Mask|ControlMask|ShiftMask,    XK_t,      spawn,          SHCMD("~/Other/Kotatogram/Kotatogram") },
    { Mod1Mask|ControlMask,              XK_t,      spawn,          SHCMD("thunderbird") },
    { Mod1Mask|ControlMask,              XK_n,      spawn,          SHCMD("notepadqq") },
    { Mod1Mask|ControlMask,              XK_q,      spawn,          SHCMD("qpdfview") },
    { Mod1Mask|ControlMask,              XK_c,      spawn,          SHCMD("chromium") },
    { ControlMask|Mod1Mask,              XK_b,      spawn,          SHCMD("brave") },
    { ControlMask|ShiftMask|Mod1Mask,    XK_b,      spawn,	    SHCMD("brave --incognito") }, //open private windows in the Brave browser
    { Mod1Mask|ControlMask,              0xff52,    spawn,          SHCMD("amixer -D pulse set Master 3%+") }, //increase audio volume, you muse use PulseAudio for this to work
    { Mod1Mask|ControlMask,              0xff54,    spawn,          SHCMD("amixer -D pulse set Master 3%-") }, //decrease audio-volume
    { Mod1Mask|ControlMask|ShiftMask,    0xffff,    spawn,          SHCMD("systemctl suspend") },     
    { Mod1Mask|ControlMask|ShiftMask,    0xff56,    spawn,          SHCMD("shutdown now")},
    { Mod1Mask|ControlMask|ShiftMask,    0xff50,    spawn,          SHCMD("reboot") },
    {ControlMask|ShiftMask,              XK_l,      spawn,          SHCMD("lutris") },
    {ControlMask|Mod1Mask,               XK_d,      spawn,          SHCMD("deadbeef")}, //in the next 4 lines hotkeys for making (and storing) screenshots
    {MODKEY,                             XK_p,      spawn,          SHCMD("scrot -fs 'temp.png' -e 'xclip -selection clipboard -target image/png -i $f ; rm $f'")}, 
    {MODKEY|ShiftMask,                   XK_p,      spawn,          SHCMD("scrot -fs '~/Pictures/%d-%m-%y-%H%M%S.png'")},
    {MODKEY,                             XK_o,      spawn,          SHCMD("scrot 'temp.png' -e 'xclip -selection clipboard -target image/png -i $f ; rm $f'")},
    {MODKEY|ShiftMask,                   XK_o,      spawn,          SHCMD("scrot '~/Pictures/%d-%m-%y-%H%M%S.png'")},
    {ControlMask|Mod1Mask,               XK_s,      spawn,          SHCMD("steam")},
    {ControlMask|Mod1Mask|ShiftMask,     XK_l,      spawn,          SHCMD("libreoffice")},
    {ControlMask|Mod1Mask|ShiftMask,     XK_k,      spawn,          SHCMD("firefox --private-window https://knmi.nl/nederland-nu/weer/waarnemingen")},
    {ControlMask|Mod1Mask|ShiftMask,     XK_m,      spawn,          SHCMD("pactl set-source-mute alsa_input.usb-MICE_MICROPHONE_USB_MICROPHONE_201308-00.mono-fallback 1")}, 
    {ControlMask|Mod1Mask|ShiftMask,     XK_u,      spawn,          SHCMD("pactl set-source-mute alsa_input.usb-MICE_MICROPHONE_USB_MICROPHONE_201308-00.mono-fallback 0")},
	
    // here the keyboard-keys for the workspaces are defined, if you don't have a numpad-block then you could for example replace the hexadecimal codes with XK_0 to XK_9, take into account that in the C-language the first element in an array is indexed with a 0, so the 0 here corresponds to workspace 1 etcetera
    TAGKEYS(                  0xff9c,          0)
    TAGKEYS(                  0xff99,          1)
    TAGKEYS(                  0xff9b,          2)
    TAGKEYS(                  0xff96,          3)
    TAGKEYS(                  0xff98,          5)
    TAGKEYS(                  0xff9d,          4)
    TAGKEYS(                  0xff95,          6)
    TAGKEYS(                  0xff97,          7)
    TAGKEYS(                  0xff9a,          8)
    TAGKEYS(		      0xff9e,	       9)	
    {MODKEY|ShiftMask,        XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
// Here it is defined what happens when you click with te mouse-buttons on the panel and windows (like windows+mouse-button)
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

