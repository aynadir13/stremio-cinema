"""Native UI invariants. This is a syntax smoke test, NOT a webOS device test."""
import pathlib
import re
import shutil
import subprocess
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
APP = (ROOT / "src/core/app.c").read_text()
BUILD = (ROOT / "tools/build.sh").read_text()

class CinemaNativeTests(unittest.TestCase):
    def test_opt_in_native_renderer(self):
        self.assertEqual(APP.count("/* CINEMA_NATIVE_NAV_V2 */"), 1)
        self.assertEqual(APP.count("if (cinema_nav_draw()) return;"), 1)
        self.assertIn("#ifdef SB_CINEMA_NATIVE", APP)
        self.assertIn("hit_add_nav(", APP)
    def test_existing_screen_routing_preserved(self):
        self.assertIn("app_go(chipScr(i), NULL, 1)", APP)
        self.assertIn("app_is_board(SCR)", APP)
        self.assertIn("void bg_draw(void)", APP)
        self.assertIn("void app_draw(void)", APP)
    def test_build_option_is_opt_in_and_rebuilds(self):
        self.assertIn('CINEMA_UI="${CINEMA_UI:-0}"', BUILD)
        self.assertIn("SB_CINEMA_NATIVE=1", BUILD)
        self.assertIn('CFG="$APPID cinema=$CINEMA_UI"', BUILD)
    @unittest.skipUnless(shutil.which("cc"), "C compiler not installed")
    def test_c_syntax_of_new_navigation(self):
        m = re.search(r"/\* CINEMA_NATIVE_NAV_V2 \*/(.*?)#endif /\* SB_CINEMA_NATIVE \*/", APP, re.S)
        self.assertIsNotNone(m)
        stub = r"""
#include <stdint.h>
#define SB_W 1920
#define ALIGN_LEFT 0
#define SB_CINEMA_NATIVE 1
#define RGB(r,g,b) ((uint32_t)0xff000000u)
#define WHITE_A(a) ((uint32_t)0xffffffffu)
#define ALIGN_CENTER 1
#define NAV_SET 0
#define NAV_SEARCH 1
#define NAV_DISC 2
#define NAV_HOME 3
#define NAV_LIB 4
#define NAV_MOVIES 5
#define SCR_LOGIN 0
int SCR=1;
struct { float chipX[6],chipW[6]; int laidOut; } topNav;
static float revpanel_page_k(void){return 0;}
static void topnav_paint(void){}
static int chipFocused(int n){return n==3;}
static int chipCur(int n){return n==3;}
static const char *chipLabel(int n){(void)n;return "Home";}
static void chip_focus(int n,int b){(void)n;(void)b;}
static void chip_act(int n,int b){(void)n;(void)b;}
static void hit_add_nav(float x,float y,float w,float h,void(*f)(int,int),void(*g)(int,int),int i,int j)
{(void)x;(void)y;(void)w;(void)h;(void)f;(void)g;(void)i;(void)j;}
static void gfx_rrect(float x,float y,float w,float h,float r,uint32_t c)
{(void)x;(void)y;(void)w;(void)h;(void)r;(void)c;}
static void gfx_ring(float x,float y,float w,float h,float r,float t,uint32_t c)
{(void)x;(void)y;(void)w;(void)h;(void)r;(void)t;(void)c;}
static void gfx_ring_out(float x,float y,float w,float h,float r,float t,uint32_t c)
{(void)x;(void)y;(void)w;(void)h;(void)r;(void)t;(void)c;}
static float text_draw(const char *s,float x,float y,int px,int weight,uint32_t c,float tracking,float max,int align)
{(void)s;(void)x;(void)y;(void)px;(void)weight;(void)c;(void)tracking;(void)max;(void)align;return 0;}
static int icon_exists(const char *s){(void)s;return 1;}
static void icon_draw(const char *s,float x,float y,float size,uint32_t c)
{(void)s;(void)x;(void)y;(void)size;(void)c;}
"""
        code = stub + m.group(0) + "\nint main(void){return cinema_nav_draw()==0;}\n"
        r = subprocess.run(["cc","-x","c","-std=c11","-Wall","-Wextra","-Werror","-fsyntax-only","-"],
                           input=code,text=True,capture_output=True)
        self.assertEqual(r.returncode,0,r.stderr)
if __name__=="__main__":unittest.main()
