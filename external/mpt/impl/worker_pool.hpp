// Software License Agreement (BSD-3-Clause)
//
// Copyright 2018 The University of North Carolina at Chapel Hill
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

//! @author Jeff Ichnowski

#pragma once
#ifndef MPT_IMPL_WORKER_POOL_HPP
#define MPT_IMPL_WORKER_POOL_HPP

#include "../log.hpp"
#include <utility>

namespace unc::robotics::mpt::impl {
    template <typename T, int maxThreads = 0, typename Allocator = std::allocator<T>>
    class WorkerPool;

    // specialization for 1 thread
    template <typename T, typename Allocator>
    class WorkerPool<T, 1, Allocator> {
        T worker_;
    public:
        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;
        
        WorkerPool(WorkerPool&& other)
            : worker_(std::move(other))
        {
        }

        template <typename ... Args>
        WorkerPool(const Args& ... args)
            : worker_(0, args...)
        {
        }

        unsigned size() const {
            return 1;
        }

        T& operator[] (std::size_t i) {
            assert(i == 0);
            return worker_;
        }

        const T& operator[] (std::size_t i) const {
            assert(i == 0);
            return worker_;
        }

        template <typename Context, typename DoneFn>
        void solve(Context& context, const DoneFn& doneFn) {
            // TODO exceptions
            MPT_LOG(INFO) << "solving with 1 thread";
            worker_.solve(context, doneFn);
        }

        auto begin() {
            return &worker_;
        }
        
        auto end() {
            return &worker_ + 1;
        }

        auto begin() const {
            return &worker_;
        }
        
        auto end() const {
            return &worker_ + 1;
        }
    };
}

#if MPT_USE_OPENMP && MPT_USE_STD_THREAD
#  error "MPT_USE_OPENMP and MPT_USE_STD_THREAD are mutually exclusive"
#elif MPT_USE_OPENMP || (defined(_OPENMP) && !MPT_USE_STD_THREAD)
#  include "worker_pool_openmp.hpp"
#else
#  include "worker_pool_std_thread.hpp"
#endif

#endif
