
#include <iostream>
#include "matgui/application.h"
#include "matgui/window.h"
#include "matgui/texture.h"
#include "matgui/draw.h"
#include "matgui/matgl.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace MatGui;
using namespace std::chrono;

int main(int argc, char **argv) {
   Application app(argc, argv);

   const int texW = 768;
   const int texH = 576;

   int width = texW;
   int height = texH;

   if (argc == 2) {
      if (argv[1] == "--help"s) {
         cout << "usage:" << endl;
         cout << "./testbild" << endl;
         cout << "./testbild [width] [height]" << endl;

         return 0;
      }
   }
   if (argc == 3) {
      width = stoi(argv[1]);
      height = stoi(argv[2]);
   }

   Window window("testbild", width, height);
   window.bordered(false);

   Texture texture("testbild.png");
   Texture indicatorTex("indicator.png");

   Paint paint;
   paint.line.color(1,1,1);

   auto indXMin = 277;
   auto indXMax = 476;
   auto indY = 435;
   auto indW = 6;
   auto indH = 42;

   double phase = 0;

   window.frameUpdate.connect([&] (double t) {
      drawTextureRect(0,0,0,window.width(), window.height(), texture, DrawStyle::OrigoTopLeft);
      auto w = (indXMax - indXMin);
      auto x =  static_cast<int>(indXMin + phase ) % (w * 2);
      if (x > w) {
         x -= w;
         x = indXMax - x;
      }
      else {
         x = indXMin + x;
      }
      drawTextureRect(x * window.width() / texW, indY * window.height() / texH, 0,
                      indW * window.width() / texW, indH * window.height() / texH, indicatorTex,
                      DrawStyle::OrigoTopLeft);

      phase += t * 100;
      window.invalidate();
      this_thread::sleep_for(.05s);
   });

   app.mainLoop();

	return 0;
}

