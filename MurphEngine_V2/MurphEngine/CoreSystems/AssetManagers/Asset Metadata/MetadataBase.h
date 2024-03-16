#pragma once

enum class CacheStatus
{
    kUnCached,
    kCached,
    kFlushed,
    kCaching
};

class ResourceMetaData
{
protected:
    size_t m_refCount = 0;
    CacheStatus m_status = CacheStatus::kUnCached;

public:
    //constructor
    ResourceMetaData() = default;
    //destructor
    virtual ~ResourceMetaData() = default;
    //copy constructor
    ResourceMetaData(const ResourceMetaData& other) = delete;
    //move constructor
    ResourceMetaData(ResourceMetaData&& other) = delete;
    //copy assignment
    ResourceMetaData& operator=(const ResourceMetaData& rhs) = delete;
    //move assignment
    ResourceMetaData& operator=(ResourceMetaData&& rhs) = delete;


    size_t GetRefCount() const { return m_refCount; }
    void IncrementRefCount() { ++m_refCount; }
    void DecrementRefCount() { --m_refCount; }

    CacheStatus GetCacheStatus() const { return m_status; }
    void SetCacheStatus(CacheStatus status) { m_status = status; }
};