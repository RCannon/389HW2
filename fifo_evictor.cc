#include "fifo_evictor.hh"
#include <cassert>

void
Fifo_Evictor::touch_key(const key_type& key)
{
  keyq_.push(key);
}

const key_type
Fifo_Evictor::evict()
{
  auto x = keyq_.front();
  keyq_.pop();
  assert(x);
  return x;
}
