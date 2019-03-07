/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappx     = 12;
static const char *fonts[]          = { "mono:size=11:antialias=true:autohint=true" };
static const char dmenufont[]       = "mono:size=11:antialias=true:autohint=true";
static const char prim_bg[]         = "#ffffff";
static const char prim_hl[]         = "#1faaaa";
static const char secd_bg[]         = "#e0e0e0";
static const char prim_tx[]         = "#151515";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { prim_tx,   prim_bg,   secd_bg },
	[SchemeSel]  = { prim_tx,   secd_bg,   prim_hl },
};

/* tagging */
static const char *tags[] = { " jen", " dva", " tri", " cet", " pet", " null"};

static const Rule rules[] = {
/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=",      tile },    /* first entry is default */
	{ "~",      NULL },    /* no layout function means floating behavior */
	{ "-",      monocle },
};

/* key definitions */
#define XF86MonBrightnessDown       0x1008ff03
#define XF86MonBrightnessUp         0x1008ff02
#define XF86AudioMute               0x1008ff12
#define XF86AudioLowerVolume        0x1008ff11
#define XF86AudioRaiseVolume        0x1008ff13

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-i", "-m", dmenumon, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *lockcmd[]    = { "slock", NULL };
static const char *brightup[]   = { "brightnessctl", "s", "5%+", NULL };
static const char *brightdown[] = { "brightnessctl", "s", "5%-", NULL };
static const char *audiomute[] =  { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *audioup[] =    { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *audiodown[] =  { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };

static Key keys[] = {
	/* modifier                     key                        function        argument */
    { 0,                            XF86MonBrightnessDown,     spawn,         {.v = brightdown } },
    { 0,                            XF86MonBrightnessUp,       spawn,         {.v = brightup   } },
    { 0,                            XF86AudioMute,             spawn,         {.v = audiomute  } },
    { 0,                            XF86AudioLowerVolume,      spawn,         {.v = audiodown  } },
    { 0,                            XF86AudioRaiseVolume,      spawn,         {.v = audioup    } },
    { MODKEY,                       XK_o,                      spawn,         {.v = lockcmd    } },

	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.025} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.025} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_Left,  focusmon,        {.i = -1 } },
	{ MODKEY,                       XK_Right, focusmon,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,  tagmon,          {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right, tagmon,          {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_0,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
