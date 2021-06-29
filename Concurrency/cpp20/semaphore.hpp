#ifndef EXPERIMENTAL_SEMAPHORE_H_434A50A9_28ED_43AA_9E0C_4262B266D437
#define EXPERIMENTAL_SEMAPHORE_H_434A50A9_28ED_43AA_9E0C_4262B266D437

#include <cstddef>

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
#define SEM_VALUE_MAX INT_MAX
using Error=DWORD;
#undef max
#else
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
using Error=int;
#endif

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <chrono>

namespace experimental
{
    namespace details
    {
        std::string get_error_message(Error code)
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            HLOCAL hLocal = nullptr;
            FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                nullptr,
                code, 
                0, //LANG_USER_DEFAULT,
                (char *)&hLocal, 
                0,
                nullptr
            );
            std::string msg((char *)hLocal);
            LocalFree(hLocal);
            return msg;
        #else
            return strerror(code);
        #endif
        }
    }

    template <std::ptrdiff_t least_max_value = SEM_VALUE_MAX>
    class counting_semaphore
    {
    public:
        static constexpr std::ptrdiff_t max() noexcept
        {
            return SEM_VALUE_MAX;
        }

        constexpr explicit counting_semaphore(std::ptrdiff_t desired)
        {
            assert(desired <= least_max_value);
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            LONG lMaximumCount = static_cast<LONG>(desired);
            m_handle = CreateSemaphoreW(NULL, lMaximumCount, lMaximumCount, NULL);
            if (m_handle == nullptr) {
                throw std::runtime_error(details::get_error_message(GetLastError()));
            }
        #else
            int code = sem_init(&m_handle, 0, static_cast<unsigned int>(desired));
            if (code != 0) {
                throw std::runtime_error(details::get_error_message(errno));
            }
        #endif
        }
        ~counting_semaphore()
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            if (m_handle != nullptr) {
                CloseHandle(m_handle);
            }
        #else
            sem_destroy(&m_handle);
        #endif
        }

        counting_semaphore(counting_semaphore&&) = default;
        counting_semaphore& operator=(counting_semaphore&&) = default;
        counting_semaphore(const counting_semaphore&) = delete;
        counting_semaphore& operator=(const counting_semaphore&) = delete;

        void release(std::ptrdiff_t update = 1)
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            LONG previous_count = 0;
            if (!ReleaseSemaphore(m_handle, static_cast<LONG>(update), &previous_count)) {
                throw std::runtime_error(details::get_error_message(GetLastError()));
            }
        #else
            if (update >= 1) {
                post();
                int times = static_cast<int>(update) - 1;
                while (times > 0) {
                    post();
                    --times;
                }
            }
        #endif
        }
        void acquire()
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            DWORD code = WaitForSingleObject(m_handle, INFINITE);
            switch (code) {
            case WAIT_OBJECT_0:
                break;
            case WAIT_FAILED:
                code = GetLastError();
                break;
            default:
                break;
            }
            if (code != WAIT_OBJECT_0) {
                throw std::runtime_error(details::get_error_message(code));
            }
        #else
            int code = sem_wait(&m_handle);
            if (code != 0) {
                throw std::runtime_error(details::get_error_message(errno));
            }
        #endif
        }

        bool try_acquire() noexcept
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            return try_acquire(0);
        #else
            return sem_trywait(&m_handle) == 0;
        #endif
        }

        template<class Rep, class Period>
        bool try_acquire_for(const std::chrono::duration<Rep, Period>& rel_time)
        {
            size_t m = std::chrono::duration_cast<std::chrono::milliseconds>(rel_time).count();
            return try_acquire(m);
        }

        template<class Clock, class Duration>
        bool try_acquire_until(const std::chrono::time_point<Clock, Duration>& abs_time)
        {
            bool retval = true;
            auto now = std::chrono::steady_clock::now();
            if (now < abs_time) {
                auto diff = abs_time - now;
                auto m = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
                retval = try_acquire(static_cast<size_t>(m));
            }
            return retval;
        }
    private:
        bool try_acquire(size_t milliseconds) noexcept
        {
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            bool retval = false;
            DWORD code = WaitForSingleObject(m_handle, static_cast<DWORD>(milliseconds));
            if (code == WAIT_OBJECT_0) {
                retval = true;
            }
            return retval;
        #else
            struct timespec timeout;
            memset(&timeout, 0, sizeof(timeout));
            timeout.tv_sec = milliseconds / 1000;
            timeout.tv_nsec = (milliseconds % 1000) * 1000;
            return sem_timedwait(&m_handle, &timeout) == 0;
        #endif
        }
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        HANDLE m_handle;
    #else
        sem_t m_handle;
        void post()
        {
            int code = sem_post(&m_handle);
            if (code != 0) {
                throw std::runtime_error(details::get_error_message(errno));
            }
        }
    #endif
    };

    using binary_semaphore = counting_semaphore<1>;
}

#endif
