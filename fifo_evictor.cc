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
  key_type x = "";
  if (keyq_.empty()) return x;
  x = keyq_.front();
  keyq_.pop();
  return x;
}
