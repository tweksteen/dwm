/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Dejavu Sans Mono:medium:size=10.5";
#define NUMCOLORS 9 
static const char colors[NUMCOLORS][ColLast][9] = {
// border foreground background
{ "#212121", "#696969", "#121212" }, // 0 = normal
{ "#696969", "#E0E0E0", "#121212" }, // 1 = selected
{ "#212121", "#CF4F88", "#121212" }, // 2 = red
{ "#212121", "#53A6A6", "#121212" }, // 3 = green
{ "#212121", "#914E89", "#121212" }, // 4 = yellow
{ "#212121", "#4779B3", "#121212" }, // 5 = blue
{ "#212121", "#47959E", "#121212" }, // 6 = cyan
{ "#212121", "#7E62B3", "#121212" }, // 7 = magenta
{ "#212121", "#899CA1", "#121212" }, // 8 = grey
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "α", "β", "γ", "δ", "ε", "ζ" };

static const Rule rules[] =  {
  { NULL,       NULL,       NULL,       0,            False,       -1 },
	//  class      instance    title       tags mask     isfloating   monitor 
	// { "Gimp",     NULL,       NULL,       0,            True,        -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", "Monospace-10", "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], "-b", NULL };
static const char *termcmd[]  = { "xterm", NULL };
static const char *firefoxcmd[] = { "firefox", NULL};
static const char *thunderbirdcmd[] = { "thunderbird", NULL};
static const char *virtmanagercmd[] = { "virt-manager", NULL};
static const char *chromiumcmd[] = { "google-chrome", NULL};
static const char *sndinc[] = { "amixer", "-q", "set", "Master", "5+", "unmute", NULL};
static const char *snddec[] = { "amixer", "-q", "set", "Master", "5-", "unmute", NULL};
static const char *sndmute[] = { "amixer", "-q", "set", "Master", "toggle", NULL};
static const char *backlightinc[] = { "xbacklight", "-inc", "10"};
static const char *backlightdec[] = { "xbacklight", "-dec", "10"};
static const char *lock[] = { "slock", NULL};


static Key keys[] = {
	/* modifier             key                  function        argument */
	{ MODKEY,               XK_p,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,               XK_b,                    togglebar,      {0} },
	{ MODKEY,               XK_w,                    focusstack,     {.i = +1 } },
	{ MODKEY,               XK_q,                    focusstack,     {.i = -1 } },
	{ MODKEY,               XK_Left,                 setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_Right,                setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_Tab,                  zoom,      	   {0} },
	{ MODKEY|ShiftMask,	    XK_c,                    killclient,     {0} },
  { 0,                    XF86XK_MonBrightnessDown, spawn,   	     {.v = backlightdec} },
	{ 0,                    XF86XK_MonBrightnessUp,  spawn,   	     {.v = backlightinc} },
  { 0,                    XF86XK_AudioLowerVolume, spawn,   	     {.v = snddec} },
	{ 0,                    XF86XK_AudioRaiseVolume, spawn,   	     {.v = sndinc} },
	{ 0,                    XF86XK_AudioMute,        spawn,   	     {.v = sndmute} },
	{ MODKEY,               XK_c,                    spawn,          {.v = chromiumcmd} },
	{ MODKEY,               XK_t,                    spawn,          {.v = thunderbirdcmd} },
	{ MODKEY,               XK_v,                    spawn,          {.v = virtmanagercmd} },
	{ MODKEY,               XK_f,                    spawn,          {.v = firefoxcmd} },
	{ MODKEY,               XK_BackSpace,            spawn,          {.v = lock} },
	{ MODKEY,               XK_a,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_s,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_d,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,                togglefloating, {0} },
	{ MODKEY,               XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,               XK_z,                focusmon,       {.i = -1 } },
	{ MODKEY,               XK_x,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_z,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_x,               tagmon,         {.i = +1 } },
	TAGKEYS(                XK_1,                      0)
	TAGKEYS(                XK_2,                      1)
	TAGKEYS(                XK_3,                      2)
	TAGKEYS(                XK_4,                      3)
	TAGKEYS(                XK_5,                      4)
	TAGKEYS(                XK_6,                      5)
	{ MODKEY|ShiftMask,     XK_q,      		 quit,           {0} },
};	

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

