#include "rtl_out/Vnes_top.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  Vnes_top top;

  while (true) {
    top.wire_in = !top.wire_in;
    top.eval();

    std::cout << "Input wire: " << !!top.wire_in << "\nOutput wire: " << !!top.wire_out << "\n\033[2A";

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}
