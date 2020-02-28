#include <utility>
#include <cassert>
#include "cache.hh"
#include "fifo_evictor.hh"

class Cache::Impl 
{
  private:
    const Cache::size_type maxmem_;
    int64_t remmem_;
    const float max_load_factor_;
    Evictor* evictor_;
    const Cache::hash_func hasher_;
    std::unordered_map<key_type, std::pair<Cache::val_type, Cache::size_type>, Cache::hash_func> tbl_;
  public:

    Impl(Cache::size_type maxmem,
        float max_load_factor = 0.75,
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>());
    ~Impl() = default;
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;
    void set(key_type key, Cache::val_type val, Cache::size_type size);
    Cache::val_type get(key_type key, Cache::size_type& val_size) const;
    bool del(key_type key);
    Cache::size_type space_used() const;
    void reset();
};

Cache::Impl::Impl(Cache::size_type maxmem,
        float max_load_factor,
        Evictor* evictor,
        Cache::hash_func hasher)
        : maxmem_(maxmem), remmem_(maxmem), max_load_factor_(max_load_factor), 
          evictor_(evictor), hasher_(hasher), tbl_(5, hasher_)
{
  tbl_.max_load_factor(max_load_factor_);
}

Cache::Cache(Cache::size_type maxmem,
        float max_load_factor,
        Evictor* evictor,
        Cache::hash_func hasher)
        : pImpl_(new Cache::Impl(maxmem, max_load_factor, evictor, hasher))
{}

Cache::~Cache()
{}

void 
Cache::Impl::set(key_type key, Cache::val_type val, Cache::size_type size)
{
  if (size > maxmem_) return; 
  assert(size != 0); /* remove if necessary - and remove assert in del */
  if (remmem_ - size <= 0)
  {
    if (evictor_ == nullptr) return;
    else
    {
      key_type evictKey;
      while (remmem_ - size <= 0) 
      {
        evictKey = evictor_->evict();
        assert(del(evictKey)); 
      }
    }
  }
  tbl_.insert_or_assign(key, std::make_pair(val,size));
  return;
}

Cache::val_type
Cache::Impl::get(key_type key, Cache::size_type& val_size) const
{
  if (tbl_.find(key) == tbl_.end()) return nullptr;
  std::pair res = tbl_.at(key);
  val_size = res.second;
  return res.first;
}

bool 
Cache::Impl::del(key_type key)
{
  Cache::size_type size = tbl_.at(key).second;
  if (tbl_.erase(key))
  {
    auto beforeRemmem = remmem_;
    remmem_ += size;
    assert(beforeRemmem > remmem_);
    assert(remmem_ <= maxmem_);
    return true;
  }
  return false; 
}

Cache::size_type 
Cache::Impl::space_used() const
{
  return maxmem_ - remmem_;
}

void
Cache::Impl::reset()
{
  tbl_.clear();
  remmem_ = maxmem_;
  return;
}

/* here are the cache methods, all they do is call the corresponding Impl methods */
void Cache::set(key_type key, Cache::val_type val, Cache::size_type size)
{
  return pImpl_->set(key, val, size);
}

Cache::val_type Cache::get(key_type key, Cache::size_type& val_size) const
{
  return pImpl_->get(key, val_size);
}

bool Cache::del(key_type key)
{
  return pImpl_->del(key);
}

Cache::size_type Cache::space_used() const
{
  return pImpl_->space_used();
}

void Cache::reset()
{
  return pImpl_->reset();
}

