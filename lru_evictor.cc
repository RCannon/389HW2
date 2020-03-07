#include "lru_evictor.hh"

void
LRU_Evictor::touch_key(const key_type& key)
{
    auto it = map_.find(key);
    if (it == map_.end()) {
        Node * N = new Node({key, nullptr, nullptr});
        N->prev_ = LL_->back_;
        if (LL_->back_ != nullptr) LL_->back_->next_ = N;
        LL_->back_ = N;
        if (LL_->root_ == nullptr) LL_->root_ = N;
        map_[key] = N;
    } else {
        Node* N = it->second;
        if (N->prev_ != nullptr) N->prev_->next_ = N->next_;
        if (N->next_ != nullptr) N->next_->prev_ = N->prev_;
        if ((LL_->root_ == N) && (N->next_ != nullptr)) LL_->root_ = N->next_;
        N->prev_ = LL_->back_;
        if (LL_->back_ != N) LL_->back_->next_ = N;
        N->next_ = nullptr;
        LL_->back_ = N;
    }
}
const key_type
LRU_Evictor::evict()
{
  if (LL_->root_ != nullptr){
    Node* N = LL_->root_;
    N->next_->prev_ = nullptr;
    LL_->root_ = N->next_;
    key_type k = N->key;
    // delete N;
    map_.erase(k);
    return k;
  } else {
    return "";
  }
}

LRU_Evictor::~LRU_Evictor(){
  for (auto it = map_.begin(); it != map_.end(); it++)
  {
    delete it->second;
  }
}
