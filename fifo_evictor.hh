#pragma once
#include "evictor.hh"

class Fifo_Evictor : public Evictor {
  private:

  public:

    Fifo_Evictor();
    virtual ~Fifo_Evictor();
    Fifo_Evictor(const Evictor&) = delete;
    Fifo_Evictor& operator=(const Evictor&) = delete;

    virtual void touch_key(const key_type&) override;
    virtual const key_type evict() override;
};
