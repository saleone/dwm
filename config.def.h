#include <X11/XF86keysym.h>

static const char col_fg[]          = "#555555";
static const char col_bg[]          = "#fafafa";
static const char col_hl[]          = "#f24c27";
static const unsigned int borderpx  = 3;
static const unsigned int snap      = 32;
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char *colors[][3]      = {
	/*                fg         bg         border   */
	[SchemeNorm]  = { col_fg,    col_bg,    col_bg },
	[SchemeSel]   = { col_bg,    col_fg,    col_hl },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "0"};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            False,       -1 }
};

static const float mfact     = 0.55;
static const int nmaster     = 1;
static const int resizehints = 1;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "=",      tile },
	{ "~",      NULL },
	{ "-",      monocle },
};

static const char *upvol[]      = { "/usr/bin/pactl", "set-sink-volume", "0",   "+5%",     NULL };
static const char *downvol[]    = { "/usr/bin/pactl", "set-sink-volume", "0",   "-5%",     NULL };
static const char *mutevol[]    = { "/usr/bin/pactl", "set-sink-mute",   "0",   "toggle",  NULL };
static const char *upbright[]   = { "brightnessctl",  "set",             "+5%",            NULL };
static const char *downbright[] = { "brightnessctl",  "set",             "5%-",            NULL };

static const char *statuscmd[] = {
	"/bin/sh",
	"-c",
	"/home/saleone/.local/bin/controls notify status",
	NULL
};


#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define XK_voldec XF86XK_AudioLowerVolume
#define XK_volinc XF86XK_AudioRaiseVolume
#define XK_volmut XF86XK_AudioMute
#define XK_briinc XF86XK_MonBrightnessUp
#define XK_bridec XF86XK_MonBrightnessDown

static char dmenumon[2] = "0";
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m",
	dmenumon,
	"-fn",
	dmenufont,
	"-nb",
	col_bg,
	"-nf",
	col_fg,
	"-sb",
	col_hl,
	"-sf",
	col_fg,
	NULL
};

static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_space,     spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,    spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_s,         spawn,          {.v = statuscmd } },

	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_g,         incngaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,         incngaps,       {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.01} },

	{ MODKEY,                       XK_Return,    zoom,           {0} },
	{ MODKEY          ,             XK_c,         killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_f,         togglefloating, {0} },

	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,       view,           {.ui = ~0 } },

	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,         setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },

	{ 0,                            XK_voldec,    spawn,          {.v = downvol } },
	{ 0,                            XK_volmut,    spawn,          {.v = mutevol } },
	{ 0,                            XK_volinc,    spawn,          {.v = upvol   } },

	{ 0,                            XK_bridec,    spawn,          {.v = downbright } },
	{ 0,                            XK_briinc,    spawn,          {.v = upbright   } },

	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_0,                         5)

	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
};

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

