/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "Monospace 10";
static const char normbordercolor[] = "#333333";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#888888";
static const char selbordercolor[]  = "#4C7899";
static const char selbgcolor[]      = "#285577";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	/*{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },*/
};

/* layout(s) */
static const float mfact      = 0.60; /* factor of master area size [0.05..0.95] */
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", "Monospace-10", "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-b", NULL };
static const char *termcmd[]  = { "xterm", NULL };
static const char *firefoxcmd[] = { "firefox", NULL};
static const char *thunderbirdcmd[] = { "thunderbird", NULL};
static const char *virtmanagercmd[] = { "virt-manager", NULL};
static const char *chromiumcmd[] = { "google-chrome", NULL};
static const char *sndinc[] = { "amixer", "-q", "set", "Master", "5+", "unmute", NULL};
static const char *snddec[] = { "amixer", "-q", "set", "Master", "5-", "unmute", NULL};
static const char *sndmute[] = { "amixer", "-q", "set", "Master", "toggle", NULL};
static const char *lock[] = { "slock", NULL};


static Key keys[] = {
	/* modifier             key 		         function        argument */
	{ MODKEY,               XK_p,      		 spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return, 		 spawn,          {.v = termcmd } },
	{ MODKEY,               XK_b,      		 togglebar,      {0} },
	{ MODKEY,               XK_j,      		 focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,      		 focusstack,     {.i = -1 } },
	{ MODKEY,               XK_h,      		 setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,      		 setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_Tab,    		 zoom,      	 {0} },
	{ MODKEY|ShiftMask,	XK_c,      		 killclient,     {0} },
  	{ 0,                    XF86XK_AudioLowerVolume, spawn,   	 {.v = snddec} },
	{ 0,                    XF86XK_AudioRaiseVolume, spawn,   	 {.v = sndinc} },
	{ 0,                    XF86XK_AudioMute,        spawn,   	 {.v = sndmute} },
	{ MODKEY,               XK_c,      		 spawn,          {.v = chromiumcmd} },
	{ MODKEY,               XK_t,      		 spawn,          {.v = thunderbirdcmd} },
	{ MODKEY,               XK_v,      		 spawn,          {.v = virtmanagercmd} },
	{ MODKEY,               XK_f,      		 spawn,          {.v = firefoxcmd} },
	{ MODKEY,               XK_BackSpace,  	         spawn,          {.v = lock} },
	{ MODKEY,               XK_bracketleft,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               XK_bracketright,  	 setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               XK_backslash,     	 setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               XK_space,  		 setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,  		 togglefloating, {0} },
	{ MODKEY,               XK_0,      		 view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      		 tag,            {.ui = ~0 } },
	{ MODKEY,               XK_comma,  		 focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period, 		 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,  		 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period, 		 tagmon,         {.i = +1 } },
	TAGKEYS(                XK_1,                      0)
	TAGKEYS(                XK_2,                      1)
	TAGKEYS(                XK_3,                      2)
	TAGKEYS(                XK_4,                      3)
	TAGKEYS(                XK_5,                      4)
	TAGKEYS(                XK_6,                      5)
	TAGKEYS(                XK_7,                      6)
	TAGKEYS(                XK_8,                      7)
	TAGKEYS(                XK_9,                      8)
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

