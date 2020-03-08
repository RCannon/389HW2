#pragma once
#include "evictor.hh"
#include "LList.hh"
#include "cache.hh"

class LRU_Evictor : public Evictor {
  private:
    LList* LL_;
    std::unordered_map<key_type, Node*> map_;
  public:
    LRU_Evictor();
    ~LRU_Evictor();
    LRU_Evictor(const LRU_Evictor&) = delete;
    LRU_Evictor& operator=(const LRU_Evictor&) = delete;

    void touch_key(const key_type&) override;
    const key_type evict() override;
};
