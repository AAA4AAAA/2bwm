#define MOD  XCB_MOD_MASK_4

static const uint16_t movements[] = {
	20,			/* move step slow */
	40,			/* move step fast */
	15,			/* resize step slow */
	400,			/* resize step fast */
};

static const bool resize_by_line = true;
static const float resize_keep_aspect_ratio = 1.03;

static const uint8_t offsets[] = {
	0,			/* offsetx */
	0,			/* offsety */
	0,			/* maxwidth */
	0,			/* maxheight */
};

static const char *colors[] = {
	"#57c1b3",		/* focuscol */
	"#000000",		/* unfocuscol */
	"#7a8c5c",		/* fixedcol */
	"#ff6666",		/* unkilcol */
	"#cc9933",		/* fixedunkilcol */
	"#000000",		/* outerbordercol */
	"#0d131a",		/* emptycol */
};

static const bool inverted_colors = false;

#define CURSOR_POSITION MIDDLE

static const uint8_t borders[] = {
	6,			/* outer border size */
	8,			/* full borderwidth */
	8,			/* magnet border size */
	2,			/* resize border size */
};

#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};

///--Menus and Programs---///
static const char *menu[]   = { "dmenu_run", NULL };
static const char *term[]   = { "st", NULL };

///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
	maxhalf(&arg2);
	Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
	teleport(&arg3);
}

///---Sloppy focus behavior---///
/*
 * Command to execute when switching from sloppy focus to click to focus
 * The strings "Sloppy" and "Click" will be passed as the last argument
 * If NULL this is ignored
 */
static const char *sloppy_switch_cmd[] = {};
//static const char *sloppy_switch_cmd[] = { "notify-send", "toggle sloppy", NULL };
static void toggle_sloppy(const Arg *arg)
{
	is_sloppy = !is_sloppy;
	if (arg->com != NULL && LENGTH(arg->com) > 0) {
		start(arg);
	}
}

///---Shortcuts---///
#define DESKTOPCHANGE(K,N) \
	{MOD,             K,              changeworkspace, {.i=N}},	\
	{MOD|SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
	/* modifier          key         function         argument */
	{MOD,                XK_Tab,     focusnext,       {.i=TWOBWM_FOCUS_NEXT}},
	{MOD,                XK_h,       focusdir,        {.i=TWOBWM_FOCUSDIR_WEST}},
	{MOD,                XK_j,       focusdir,        {.i=TWOBWM_FOCUSDIR_SOUTH}},
	{MOD,                XK_k,       focusdir,        {.i=TWOBWM_FOCUSDIR_NORTH}},
	{MOD,                XK_l,       focusdir,        {.i=TWOBWM_FOCUSDIR_EAST}},
	{MOD,                XK_q,       deletewin,       {}},
	{MOD|SHIFT|CONTROL,  XK_k,       resizestep,      {.i=TWOBWM_RESIZE_UP}},
	{MOD|SHIFT|CONTROL,  XK_j,       resizestep,      {.i=TWOBWM_RESIZE_DOWN}},
	{MOD|SHIFT|CONTROL,  XK_l,       resizestep,      {.i=TWOBWM_RESIZE_RIGHT}},
	{MOD|SHIFT|CONTROL,  XK_h,       resizestep,      {.i=TWOBWM_RESIZE_LEFT}},
	{MOD|SHIFT,          XK_k,       movestep,        {.i=TWOBWM_MOVE_UP}},
	{MOD|SHIFT,          XK_j,       movestep,        {.i=TWOBWM_MOVE_DOWN}},
	{MOD|SHIFT,          XK_l,       movestep,        {.i=TWOBWM_MOVE_RIGHT}},
	{MOD|SHIFT,          XK_h,       movestep,        {.i=TWOBWM_MOVE_LEFT}},
	{MOD,                XK_g,       teleport,        {.i=TWOBWM_TELEPORT_CENTER}},
	{MOD,                XK_x,       maximize,        {}},
	{MOD,                XK_Up,      maxhalf,         {.i=TWOBWM_MAXHALF_HORIZONTAL_TOP}},
	{MOD,                XK_Down,    maxhalf,         {.i=TWOBWM_MAXHALF_HORIZONTAL_BOTTOM}},
	{MOD,                XK_Left,    maxhalf,         {.i=TWOBWM_MAXHALF_VERTICAL_LEFT}},
	{MOD,                XK_Right,   maxhalf,         {.i=TWOBWM_MAXHALF_VERTICAL_RIGHT}},
	{MOD,                XK_comma,   changescreen,    {.i=TWOBWM_NEXT_SCREEN}},
	{MOD,                XK_period,  changescreen,    {.i=TWOBWM_PREVIOUS_SCREEN}},
	{MOD,                XK_r,       raiseorlower,    {}},
	{MOD,                XK_i,       hide,            {}},
	{MOD,                XK_a,       unkillable,      {}},
	{MOD,                XK_t,       always_on_top,   {}},
	{MOD,                XK_f,       fix,             {}},
	//Start programs
	{MOD,                XK_w,       start,           {.com = menu}},
	{MOD|SHIFT,          XK_Return,  start,           {.com = term}},
	{MOD|CONTROL,        XK_q,       twobwm_exit,     {.i=0}},
	{MOD|CONTROL,        XK_r,       twobwm_restart,  {.i=0}},
	DESKTOPCHANGE(       XK_1,                        0)
	DESKTOPCHANGE(       XK_2,                        1)
	DESKTOPCHANGE(       XK_3,                        2)
	DESKTOPCHANGE(       XK_4,                        3)
	DESKTOPCHANGE(       XK_5,                        4)
	DESKTOPCHANGE(       XK_6,                        5)
	DESKTOPCHANGE(       XK_7,                        6)
	DESKTOPCHANGE(       XK_8,                        7)
	DESKTOPCHANGE(       XK_9,                        8)
	DESKTOPCHANGE(       XK_0,                        9)
};
// the last argument makes it a root window only event
static Button buttons[] = {
	{MOD,        XCB_BUTTON_INDEX_1,     mousemotion,      {.i=TWOBWM_MOVE}, false},
	{MOD,        XCB_BUTTON_INDEX_3,     mousemotion,      {.i=TWOBWM_RESIZE}, false},
	{0,          XCB_BUTTON_INDEX_3,     start,            {.com = menu}, true},
	{MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace,  {.i=0}, false},
	{MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace,  {.i=1}, false},
	{MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,     {.i=1}, false},
	{MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,     {.i=0}, false}
};
