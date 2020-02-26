#include <utility>
#include "cache.hh"

class Impl 
{
  private:
    const Cache::size_type maxmem_;
    Cache::size_type remmem_;
    const float max_load_factor_;
    const Evictor* evictor_;
    const Cache::hash_func hasher_;
    std::unordered_map<key_type, std::pair<val_type, hasher_> tbl_;
    
  public:
    Impl(Cache::size_type maxmem,
        float max_load_factor = 0.75,
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>());
    ~Impl();
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;
};

Impl::Impl(Cache::size_type maxmem,
        float max_load_factor = 0.75,
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>())
        : maxmem_(maxmem), remmem_(maxmem), max_load_factor_(max_load_factor), 
          evictor_(evictor), hasher_(hasher)
{
  tbl_.max_load_factor(max_load_factor_);
}

Cache::Cache(Cache::size_type maxmem,
        float max_load_factor = 0.75,
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>())
{
  pImpl_ = Impl(maxmem, max_load_factor, evictor, hasher);
}

void 
Cache::set(key_type key, val_type val, size_type size)
{
  if (pImpl_->remmem_ - size > pImpl->maxmem_) return;
  pImpl->remmem_ = pImpl->remmem_ - size;
  auto x = pImpl->tbl_.insert_or_assign(key, std::make_pair(val,size));
  return;
}

Cache::val_type
get(key_type key, size_type& val_size) const
{
  if (pImpl->tabl_.at(key) = ) return nullptr;
  std::pair res = pImpl->tabl_.at(key);
  val_size = res.second;
  return res.first;
}

bool Cache::del(key_type key)
{
  if (pImpl->tabl_.erase(key)) return true;
  return false 
}
