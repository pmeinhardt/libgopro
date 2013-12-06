#include "clar.h"
#include "gopro.h"

#ifdef _WIN32
int __cdecl main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
  // Run the test suite
  return clar_test(argc, argv);
}
