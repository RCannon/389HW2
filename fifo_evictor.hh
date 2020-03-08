#pragma once
#include "evictor.hh"
#include <queue>

class Fifo_Evictor : public Evictor {
  private:
    std::queue<key_type> keyq_;
  public:

    Fifo_Evictor() = default;
    ~Fifo_Evictor() = default;
    Fifo_Evictor(const Fifo_Evictor&) = delete;
    Fifo_Evictor& operator=(const Fifo_Evictor&) = delete;

    void touch_key(const key_type&) override;
    const key_type evict() override;
};
