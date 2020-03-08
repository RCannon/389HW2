#include "lru_evictor.hh"
#include <cassert>
#include <iostream>

LRU_Evictor::LRU_Evictor()
  : LL_(new LList())
{}

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
        assert(N->next_ == nullptr);
    } else {
        assert(LL_->back_ != nullptr);
        assert(LL_->root_ != nullptr);
        Node* N = it->second;
        if (LL_->back_ != N){
            if (LL_->root_ == N) {
                LL_->root_ = N->next_;
            } else {
                N->prev_->next_ = N->next_;
            }
            N->next_->prev_ = N->prev_;
            LL_->back_->next_ = N;
            N->prev_ = LL_->back_;
            LL_->back_ = N;
            N->next_ = nullptr;
        }
    }
    /* testing code: prints the LL structure after each touch*/
    
    // std::cout << "Forward pass: " << std::endl;
    // Node* fp = LL_->root_;
    // while (fp != nullptr) {
    //     std::cout << fp->key;
    //     fp = fp->next_;
    //     if (fp != nullptr){
    //         std::cout << "->";
    //     }
    // }
    // int ctr = 0;
    // std::cout << std::endl;
    // std::cout << "Backwards pass: " << std::endl;
    // Node* rp = LL_->back_;
    // while (rp != nullptr && ctr < 12) {
    //     std::cout << rp->key;
    //     rp = rp->prev_;
    //     if (rp != nullptr){
    //         std::cout << "->";
    //     }
    //     ctr++;
    // }
    // std::cout << std::endl;
}
const key_type
LRU_Evictor::evict()
{
  if (LL_->root_ != nullptr){
    Node* N = LL_->root_;
    if (N->next_ !=nullptr) N->next_->prev_ = nullptr;
    LL_->root_ = N->next_;
    if (LL_->back_ == N) LL_->back_ = nullptr;
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
  delete LL_;
}
