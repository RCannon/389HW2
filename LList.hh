#pragma once
#include "evictor.hh"
#include "cache.hh"
#include <memory>
#include <cassert>
// using npoint = Node *;
struct Node 
{
  key_type key;
  Node *prev_;
  Node *next_;
};

class LList{
  public:
  Node *root_;
  Node *back_;
  LList() { 
      root_ = nullptr;
      back_ = nullptr;
  }
  ~LList() = default;
    // LList(const Cache&) = delete;
    // LList& operator=(const LList&) = delete;

    // void create(key_type key)
    // {
    //     if (back_ == nullptr) 
    //     { 
    //       root_ = std::make_shared(Node({key, nullptr, nullptr}));
    //       back_ = root_;
    //     }
    //     else 
    //     {
    //       npoint nnode = std::make_shared(Node({key, nullptr, nullptr}));
    //       nnode->next_ = root_->next_;
    //       root_->next_->prev_ = nnode;
    //       root_ = nnode;
    //     }
    //     return;
    // }

    // void replace(npoint nnode)
    // {
    //   assert(nnode != nullptr);
    //   if (nnode.prev_ == nullptr) return;
    //   if (nnode->next_ == nullptr)
    //   {
    //     nnode->prev_->next_ = nullptr;
    //     back_ = nnode->prev_;
    //   }
    //   else
    //   {
    //     nnode->prev_->next_ = nnode->next_;
    //     nnode->next_->prev_ = nnode->prev_
    //   }
    //   nnode->prev_ = nullptr;
    //   nnode->next_ = root_->next_;
    //   root_ = nnode;
    //   return;
    // }

    // npoint get()
    // {
    //   npoint nnode = back_;
    //   nnode->prev_next_ = nullptr;
    //   back_ = nnode->prev_;
    //   return nnode; // maybe return just the key instead
};
