#pragma once

#include <memory>

#include <boost/assert.hpp>

#include "pool.hpp"

namespace elasticsearch {

namespace balancing {

template<class Pool>
class strategy {
public:
    typedef Pool pool_type;
    typedef typename Pool::connection_type connection_type;

    virtual std::shared_ptr<connection_type> next(pool_type& pool) = 0;
};

template<class Pool>
class round_robin : public strategy<Pool> {
public:
    typedef typename strategy<Pool>::pool_type pool_type;
    typedef typename pool_type::connection_type connection_type;
    typedef typename pool_type::size_type size_type;

private:
    size_type current;

public:
    round_robin() :
        current(0)
    {}

    std::shared_ptr<connection_type> next(pool_type& pool) {
        pool_lock_t<pool_type> lock(pool);
        BOOST_ASSERT(!pool.empty(lock));

        if (current >= pool.size(lock) - 1) {
            current = 0;
        }

        auto it = std::next(pool.begin(lock), current++);
        std::shared_ptr<connection_type> connection = it->second;
//!@todo: Move this line into transport just after balancing:
//!       LOG(log(), level::debug, "balancing at %s", connection->endpoint());
        return connection;
    }
};

} // namespace balancing

} // namespace elasticsearch
