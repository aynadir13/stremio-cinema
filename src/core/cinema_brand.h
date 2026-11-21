/* User-supplied N/crossbones mark from preview v0.3. A tiny 24x36
 * alpha-mask is decoded once into an RGBA GPU texture. No WebView. */
#ifndef SB_CINEMA_BRAND_H
#define SB_CINEMA_BRAND_H
#include <stdint.h>
#include "ui/gfx.h"
static void cinema_brand_draw(float x, float y, float w, float h) {
  static GLuint tex;
  if (!tex) {
    static const char a[] =
      "00000344441000333330000000000dffff9001efffd0000000000cffffe101efffd00000"
      "00000dfffff501efffd0000000000dfffffa01efffd0000000000dfffffe11efffd00000"
      "00000dffffff60efffd0000000000dffffffb0efffd0000000000dffffffe3dfffd00000"
      "00000dfffffff7dfffd0000000000cfffffffddfffd0000000000cffffffffffffd00000"
      "00000dffffffffffffd0000000000dffffffffffffd0000000000dfffeefffffffd00000"
      "00000cfffd8fffffffd0000000000dfffd3fffffffd0000000000dfffe0bffffffd00000"
      "00000cfffe06ffffffd0000000000dfffe11efffffd0000000000dfffe10afffffd00000"
      "00000dfffe104fffffd1000000000cfffe101dffffd0000003dc2dfffe1008ffffe2bc30"
      "07ff9565420001345668ff802dffe70000000000006effd24fffffe9300000039efffff4"
      "06846afffb5104afffb6486000000027cffdcffd93000000000000004cffffd400000000"
      "0372026cffe98effb51017401efeceffc610017dffdbeff21dffffa4000000004affffe2"
      "03ffe30000000000003dff4001cf6000000000000005fe10001300000000000000003200";
    unsigned char pix[24 * 36 * 4];
    for (int i = 0; i < 24 * 36; i++) {
      char c = a[i];
      unsigned v = (unsigned)(c <= '9' ? c - '0' : c - 'a' + 10) * 17;
      pix[i*4] = 245; pix[i*4+1] = 0; pix[i*4+2] = 15; pix[i*4+3] = (unsigned char)v;
    }
    tex = gfx_tex_create(pix, 24, 36, 4, 1);
  }
  if (tex) gfx_image(tex, x, y, w, h, 0, WHITE_A(255), 0, 0, 1, 1);
}
#endif
