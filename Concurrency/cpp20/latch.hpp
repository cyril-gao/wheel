#ifndef EXPERIMENTAL_LATCH_H_434A50A9_28ED_43AA_9E0C_4262B266D437
#define EXPERIMENTAL_LATCH_H_434A50A9_28ED_43AA_9E0C_4262B266D437

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#undef max
#endif

#include <limits>
#include <atomic>
#if 1 // CXX_STANDARD_VERSION < 20
#include <mutex>
#include <condition_variable>
#endif

//#include <stdexcept>
//#include <system_error>

namespace experimental
{
#if 1 // CXX_STANDARD_VERSION < 20
    class latch
    {
        mutable std::atomic<std::ptrdiff_t> m_count;
        mutable std::mutex m_mutex;
        mutable std::condition_variable m_cv;
    public:
        static constexpr std::ptrdiff_t max() noexcept
        {
            return std::numeric_limits<std::ptrdiff_t>::max();
        }

        explicit latch(std::ptrdiff_t expected) : m_count(expected)
        {
        }
        latch(const latch &) = delete;
        latch& operator=(const latch &) = delete;
        latch(latch &&) = default;
        latch& operator=(latch &&) = default;

        void count_down(std::ptrdiff_t n = 1)
        {
            if (m_count.fetch_sub(n, std::memory_order_acq_rel) <= n) {
                m_cv.notify_all();
            }
        }

        bool try_wait() const noexcept
        {
            return (m_count.load(std::memory_order_acquire) <= 0);
        }

        void wait() const
        {
            std::unique_lock<std::mutex> guard(m_mutex);
            m_cv.wait(guard, [this]() { return m_count.load(std::memory_order_acquire) <= 0; });
        }

        void arrive_and_wait(std::ptrdiff_t n = 1)
        {
            if (m_count.fetch_sub(n, std::memory_order_acq_rel) > n) {
                wait();
            } else {
                m_cv.notify_all();
            }
        }
    };
#else
    class latch
    {
        mutable std::atomic<std::ptrdiff_t> m_count;
    public:
        static constexpr std::ptrdiff_t max() noexcept
        {
            return std::numeric_limits<std::ptrdiff_t>::max();
        }

        constexpr explicit latch(std::ptrdiff_t expected) : m_count(expected)
        {
        }
        latch(const latch &) = delete;
        latch& operator=(const latch &) = delete;
        latch(latch &&) = default;
        latch& operator=(latch &&) = default;

        void count_down(std::ptrdiff_t n = 1)
        {
            if (m_count.fetch_sub(n, std::memory_order_acq_rel) <= n) {
                m_count.notify_all();
            }
        }

        bool try_wait() const noexcept
        {
            return (m_count.load(std::memory_order_acquire) <= 0);
        }

        void wait() const
        {
            //while (m_count.load(std::memory_order_acquire) > 0) {
            for (
                std::ptrdiff_t old = m_count.load(std::memory_order_acquire);
                old > 0;
                old = m_count.load(std::memory_order_acquire)
            ) {
                m_count.wait(old, std::memory_order_acquire);
            }
        }

        void arrive_and_wait(std::ptrdiff_t n = 1)
        {
            if (m_count.fetch_sub(n, std::memory_order_acq_rel) > n) {
                wait();
            } else {
                m_count.notify_all();
            }
        }
    };
#endif
}

#endif //EXPERIMENTAL_LATCH_H_434A50A9_28ED_43AA_9E0C_4262B266D437