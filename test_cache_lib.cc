#include "cache.hh"
#include <cassert>
#include <iostream>

void
fn1()
{
  Cache c = {5};
  std::cout << c.space_used() << std::endl;
  return;
}

int
main()
{
  fn1();
  return 0;
}
