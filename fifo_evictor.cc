#include "fifo_evictor.hh"

void
Fifo_Evictor::touch_key(const key_type& key)
{
  keyq_.push(key);
}

const void key_type
Fifo_Evictor::evict()
{
  auto x = keyq_.front();
  keyq_.pop();
  return x;
}
