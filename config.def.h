/**
 * dwmconfig.h
 * Hardware multimedia keys
 */
/* Somewhere at the beginning of config.h include: */

/*
 You obviously need the X11 development package installed, but here is the upstream copy
 of this header if you can't bother using the contents of your own hard drive. ;-P
 https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h
*/

#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 32;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NFM:style=Bold:pixelsize=15:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono NFM:style=Bold:pixelsize=15:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_gold[]        = "#ffae00";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gold,  col_gold  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance  title           			tags mask  isfloating  isterminal  noswallow  monitor */
	{ "ViberPC",   NULL,     NULL,           			1 << 0,    0,          0,          -1,        -1 },
	{ "discord",   NULL,     NULL,           			1 << 0,    0,          0,          -1,        -1 },
	{ "KeePassXC", NULL,     NULL,           			1 << 8,    0,          0,          -1,        -1 },
//	{ "Bochs",     NULL,     NULL,           			0,         0,          0,          -1,        -1 },
	{ "IDA",       NULL,     NULL,           			0,         0,          0,          -1,        -1 },
	{ "St",        NULL,     NULL,           			0,         0,          1,           0,        -1 },
	{ NULL,        NULL,     "Event Tester",			0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,        NULL,     "zaklopachess",			0,         0,          0,           1,        -1 }, /* marko */
	{ NULL,        NULL,     "Directional Audio Visualizer",	0,         0,          0,           1,        -1 }, /* marko */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gold, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ 0, XF86XK_AudioLowerVolume,   spawn, SHCMD("/usr/bin/pamixer --allow-boost --set-limit 150 -d 5;kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMute,          spawn, SHCMD("/usr/bin/pamixer --allow-boost --set-limit 150 -t;kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn, SHCMD("/usr/bin/pamixer --allow-boost --set-limit 150 -i 5;kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,    spawn, SHCMD("/usr/bin/xbacklight -inc 5;kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessDown,  spawn, SHCMD("/usr/bin/xbacklight -dec 5;kill -40 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		spawn, SHCMD("/usr/bin/mpc prev") },
	{ 0, XF86XK_AudioPlay,		spawn, SHCMD("/usr/bin/mpc toggle") },
	{ 0, XF86XK_AudioNext,		spawn, SHCMD("/usr/bin/mpc next") },
	{ 0, XF86XK_Search, 		spawn, SHCMD("$BROWSER") },
	{ 0, XK_Print,                  spawn, SHCMD("/usr/bin/maim -u | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/Screenshots/$(date '+%F-%H-%M-%S').png")},
	{ ShiftMask, XK_Print,          spawn, SHCMD("/usr/bin/maim -su | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/Screenshots/$(date '+%F-%H-%M-%S').png")}
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

