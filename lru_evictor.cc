#include "lru_evictor.hh"
#include "LinkedList.hh"

void
LRU_evictor::touch_key(const key_type& key)
{
    auto it = map_.find(key);
    if (it == map_.end()) {
        node * N = new node(key);
        N->prev_ = LL_->back_;
        if (LL_->back_ != nullptr) LL_->back_->next_ = N;
        LL_->back_ = N;
        if (LL_->hd == nullptr) LL_->hd = N;
        map_[key] = N;
    } else {
        node* N = it->second;
        if (N->prev_ != nullptr) N->prev_->next_ = N->next_;
        if (N->next_ != nullptr) N->next_->prev_ = N->prev_;
        if ((LL_->root_ == N) && (N->next_ != nullptr)) LL_->root_ = N->next_;
        N->prev_ = LL_->tl;
        if (LL_->back_ != N) LL_->back_->next_ = N;
        N->next_ = nullptr;
        LL_->back_ = N;
    }
}
const key_type
Fifo_Evictor::evict()
{
  if (LL->hd != nullptr){
    node* N = LL->hd;
    N->child.parent = nullptr;
    LL->hd = N->child;
    key_type k = N->key;
    delete N;
    map_.erase(k);
    return k;
  } else {
    return "";
  }
}
