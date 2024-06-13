/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int centerbar          = 1;	/* 0 means default left aligned window name text */
static const char *fonts[]          = {"DejaVu Sans Mono for Powerline:size=11", "agave Nerd Font Mono:size=20"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_gray5[]       = "#282828";
static const char col_green[]       = "#98971a";
static const char col_pink[]        = "#f59090";
static const char col_brown[]       = "#993300";
static const char col_white[]       = "#ffffff";
static const char col_black[]       = "#191919";
static const char col_beige[]       = "#ebdbb2";
static const char col_orange[]      = "#fe8019";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_beige, col_gray5, col_gray5 },
	[SchemeSel]  = { col_gray5, col_beige,  col_orange},
};

/* tagging */
static const char *tags[] = { "󰚄", "", "", "", "󰈙", "", "", "󰌳", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                         instance    title       tags mask     isfloating   monitor */
	{ "Gimp",                        NULL,       NULL,       0,            1,           -1 },
	{ "firefox",                     NULL,       NULL,       1 << 1,       0,           -1 },
	{ "zoom",                        NULL,       NULL,       1 << 8,       1,           -1 },
	{ "Skype",                       NULL,       NULL,       1 << 8,       1,           -1 },
	{ "Evince",                      NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Zathura",                     NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Zotero",                      NULL,       NULL,       1 << 3,       0,           -1 },
	{ "okular",                      NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Emacs",                       NULL,       NULL,       1,            0,           -1 },
	{ "Inkscape",                    NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Evolution",                   NULL,       NULL,       1 << 6,       0,           -1 },
	{ "R_x11",                       NULL,       NULL,       1,            1,           -1 },
	{ "MEGAsync",                    NULL,       NULL,       0,            1,           -1 },
	{ "Evolution-alarm-notify",      NULL,       NULL,       0,            1,           -1 },
	//{ "URxvt",         NULL,       NULL,       1 << 2,       0,           -1 },

};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static char dmenulines[3] = "15";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray5, "-nf", col_beige, "-sb", col_beige, "-sf", col_gray5, "-l", dmenulines, "-i", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };
static const char *toggledisplay[] = {"$HOME/.scripts/toggleDisplay", NULL};

static const Key keys[] = {
	/* modifier                     key                function        argument */
	{ MODKEY,                       XK_space,          spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_p,              spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,              togglebar,      {0} },
	{ MODKEY,                       XK_j,              focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,              focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,              incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,              incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,         zoom,           {0} },
	{ MODKEY,                       XK_Tab,            view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,              killclient,     {0} },
	{ MODKEY,                       XK_t,              setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,              setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,              setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,          setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
	{ MODKEY,                       XK_0,              view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,              tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,          focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,         focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,          tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,         tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,          setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,          setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,          setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_equal,          setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_s,                spawn,         SHCMD("systemctl suspend") },
	{ 0,                            XK_Print,            spawn,         SHCMD("gnome-screenshot -i") },
	{ MODKEY|ShiftMask,             XK_p,            spawn,         SHCMD("/home/etka/.scripts/kblang") },
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

