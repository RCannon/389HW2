#include <utility>
#include "cache.hh"

class Cache::Impl 
{
  public:
    Impl(Cache::size_type maxmem,
        float max_load_factor = 0.75,
        Evictor* evictor = nullptr,
        Cache::hash_func hasher = std::hash<key_type>());
    ~Impl();
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;

    const Cache::size_type maxmem_;
    Cache::size_type remmem_;
    const float max_load_factor_;
    const Evictor* evictor_;
    const Cache::hash_func hasher_;
    std::unordered_map<key_type, std::pair<Cache::val_type, Cache::size_type>, Cache::hash_func> tbl_;
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

void 
Cache::set(key_type key, Cache::val_type val, Cache::size_type size)
{
  if (pImpl_->remmem_ - size > pImpl_->maxmem_) return;
  pImpl_->remmem_ = pImpl_->remmem_ - size;
  pImpl_->tbl_.insert_or_assign(key, std::make_pair(val,size));
  return;
}

Cache::val_type
Cache::get(key_type key, Cache::size_type& val_size) const
{
  if (pImpl_->tbl_.find(key) == pImpl_->tbl_.end()) return nullptr;
  std::pair res = pImpl_->tbl_.at(key);
  val_size = res.second;
  return res.first;
}

bool 
Cache::del(key_type key)
{
  if (pImpl_->tbl_.erase(key)) return true;
  return false; 
}

Cache::size_type 
Cache::space_used() const
{
  return pImpl_->remmem_;
}

void
Cache::reset()
{
  pImpl_->tbl_.clear();
  pImpl_->remmem_ = pImpl_->maxmem_;
  return;
}

