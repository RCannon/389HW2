#pragma once
#include "evictor.hh"
#include "LinkedList.hh"
#include "cache.hh"

class LRU_Evictor : public Evictor {
  private:
    LinkedList* LL_;
    std::unordered_map<key_type, Node*, Cache::hash_func> map_;
  public:
    Fifo_Evictor() = default;
    virtual ~Fifo_Evictor() = default;
    Fifo_Evictor(const Fifo_Evictor&) = delete;
    Fifo_Evictor& operator=(const Fifo_Evictor&) = delete;

    virtual void touch_key(const key_type&) override;
    virtual const key_type evict() override;
};
