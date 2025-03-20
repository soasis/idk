// =============================================================================
//
// ztd.idk
// Copyright © JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.idk licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License") for non-commercial use; you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#include <ztd/idk/version.h>

#if ZTD_IS_ON(ZTD_PLATFORM_PTHREADS)

#include <ztd/idk/threads.h>

#include <ztd/idk/detail/threads.pthreads.implementation.h>

#include <ztd/idk/static_assert.h>
#include <ztd/idk/null.h>
#include <ztd/idk/size.h>

#include <pthread.h>
#if ZTD_IS_ON(ZTD_HEADER_PTHREAD_NP_H)
#include <pthread_np.h>
#endif

#if ZTD_IS_ON(ZTD_HEADER_SCHED_H)
#include <sched.h>
#endif

#if ZTD_IS_ON(ZTD_CXX)
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdbool>
#include <ctime>
#else
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#endif

#include <errno.h>

#if ZTD_IS_ON(ZTD_PLATFORM_AIX) || ZTD_IS_ON(ZTD_PLATFORM_SOLARIS)
#define ZTD_IDK_THREADS_NAME_SET_INSIDE_I_ ZTD_OFF
#else
#define ZTD_IDK_THREADS_NAME_SET_INSIDE_I_ ZTD_ON
#endif

typedef struct __ztdc_pthread_trampoline_t {
	thrd_start_t* __func;
	void* __func_arg;
#if ZTD_IS_ON(ZTD_IDK_THREADS_NAME_SET_INSIDE)
	bool __name_set;
	char __name[2048];
#endif
} __ztdc_pthread_trampoline_t;

inline static void __ztdc_pthread_prepare_name_trampoline(
     __ztdc_pthread_trampoline_t* __trampoline_userdata, size_t __name_size, const void* __name) {
#if ZTD_IS_ON(ZTD_IDK_THREADS_NAME_SET_INSIDE)
	const size_t __trampoline_name_size = sizeof(__trampoline_userdata->__name) - 1;
	const size_t __copy_size            = __trampoline_name_size < __name_size ? __trampoline_name_size : __name_size;
	memcpy(__trampoline_userdata->__name, __name, __copy_size);
	__trampoline_userdata->__name[__copy_size] = '\0'; // ensure the necessary null termination
	__trampoline_userdata->__name_set          = true;
#endif
}

inline static void* __ztdc_pthread_trampoline(void* __userdata) {
	thrd_start_t* __func = NULL;
	void* __func_arg     = NULL;
	{
		__ztdc_pthread_trampoline_t* __trampoline_userdata = (__ztdc_pthread_trampoline_t*)__userdata;
		__func                                             = __trampoline_userdata->__func;
		__func_arg                                         = __trampoline_userdata->__func_arg;
#if ZTD_IS_ON(ZTD_IDK_THREADS_NAME_SET_INSIDE)
		if (__trampoline_userdata->__name_set) {
#if ZTD_IS_ON(ZTD_PLATFORM_MAC_OS)
			// The setname uses the "current thread" on MacOS, so it has to be set here
			pthread_setname_np(__trampoline_userdata->__name);
#else
			// In other APIs, you have to produce the thread first.
			// In some parts of pthread you can create a thread but in the "stopped" mode;
			// you can "start" it up against later. But this isn't portable. Unfortunately.
			// So we set it in here, too.
			// Only on IBM-ish systems can you set the name ahead-of-time with `attr_setname_np`.
			pthread_t __self_thread = pthread_self();
#if ZTD_IS_ON(ZTD_PLATFORM_NETBSD)
			pthread_setname_np(__self_thread, __trampoline_userdata->__name, 0); // name + void* arg -- huh??
#elif ZTD_IS_ON(ZTD_PLATFORM_FREEBSD) || ZTD_IS_ON(ZTD_PLATFORM_OPENBSD)
			pthread_set_name_np(__self_thread, __trampoline_userdata->__name);
#else
			// everyone else is mildly normal about this.
			pthread_set_namenp(__self_thread, __trampoline_userdata->__name);
#endif
#endif
		}
#endif
		free(__trampoline_userdata);
	}
	if (!__func) {
		return NULL;
	}
	ztdc_static_assert(
	     sizeof(void*) >= sizeof(int), "size of `int` is too large for a `void*`: trampoline will not work");
	void* __pthread_res = 0;
	memset(&__pthread_res, 0, sizeof(void*)); // nullptr rep does not have to be "all bits zero" on all platforms, lol.
	int __std_res = __func(__func_arg);
	memcpy(__pthread_res, &__std_res, sizeof(__std_res));
	return __pthread_res;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_INTERNAL_LINKAGE)
__thrd_error_code __ztdc_to_thread_error(int __code) {
	switch (__code) {
	case 0:
		return thrd_success;
	case EDEADLK:
	case EBUSY:
		return thrd_busy;
	case EAGAIN:
	case ENOMEM:
		return thrd_nomem;
	case ETIME:
	case ETIMEDOUT:
		return thrd_timedout;
	default:
		return thrd_error;
	}
}


ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_create(thrd_t* __thr, thrd_start_t __func, void* __func_arg) {
	return ztdc_thrd_create_attrs(__thr, __func, __func_arg, 0, NULL);
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_join(thrd_t __thr, int* __res) {
	void* __impl_res;
	int __join_res = pthread_join(__thr, &__impl_res);
	if (__join_res == 0) {
		*__res = (int)(intptr_t)__impl_res;
	}
	return __ztdc_to_thread_error(__join_res);
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
ZTD_USE(ZTD_ATTR_NO_RETURN)
void thrd_exit(int __res) {
	pthread_exit((void*)(intptr_t)(__res));
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_detach(thrd_t __thr) {
	int __res = pthread_detach(__thr);
	return __res == 0 ? thrd_success : thrd_error;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_equal(thrd_t __left, thrd_t __right) {
	return memcmp(&__left, &__right, sizeof(thrd_t)) == 0;
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
thrd_t thrd_current() {
	return (thrd_t)pthread_self();
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
void thrd_yield() {
#if ZTD_IS_ON(ZTD_HEADER_SCHED_H)
	// it's implementation-defiend if it yields anyways:
	// not really our problem if the scehduler/OS doesn't want its time slice back.
	(void)sched_yield();
#elif ZTD_IS_ON(ZTD_PLATFORM_MAC_OS)
	pthread_yield_np();
#elif defined(_GNU_SOURCE)
	// might be deprecated: if this ever builds like this, silence the warning
	// it's implementation-defiend if it yields anyways:
	// not really our problem if the scehduler/OS doesn't want its time slice back.
	(void)pthread_yield();
#else
#error "unknown platform"
#endif
}

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int thrd_sleep(const struct timespec* __duration, struct timespec* __remaining) {
	return nanosleep(__duration, __remaining);
}

#endif

ZTD_USE(ZTD_C_LANGUAGE_LINKAGE)
ZTD_USE(ZTD_IDK_API_LINKAGE)
int ztdc_thrd_create_attrs(
     thrd_t* __thr, thrd_start_t __func, void* __func_arg, size_t __attrs_size, ztdc_thrd_attr_kind** __attrs) {
#if ZTD_IS_ON(ZTD_HEADER_THREADS_H)
	ztdc_static_assert(sizeof(thrd_t) >= sizeof(pthread_t), "thrd_t is not the same size as pthread_t");
#endif
	__ztdc_pthread_trampoline_t* __trampoline_userdata
	     = (__ztdc_pthread_trampoline_t*)malloc(sizeof(__ztdc_pthread_trampoline_t));
	pthread_attr_t __impl_attrs = { 0 };
	if (pthread_attr_init(&__impl_attrs) != 0) {
		return thrd_error;
	}
	for (size_t __attr_index = 0; __attr_index < __attrs_size; ++__attr_index) {
		ztdc_thrd_attr_kind* __attr_kind = __attrs[__attr_index];
		switch (*__attr_kind) {
		case ztdc_thrd_attr_kind_name: {
			ztdc_thrd_attr_name* __attr = (ztdc_thrd_attr_name*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_name_sized: {
			ztdc_thrd_attr_name_sized* __attr = (ztdc_thrd_attr_name_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_mcname: {
			ztdc_thrd_attr_mcname* __attr = (ztdc_thrd_attr_mcname*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				// TODO: convert from execution character set to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_mcname_sized: {
			ztdc_thrd_attr_mcname_sized* __attr = (ztdc_thrd_attr_mcname_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				// TODO: convert from execution character set to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_mwcname: {
			ztdc_thrd_attr_mwcname* __attr = (ztdc_thrd_attr_mwcname*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				// TODO: convert from wide execution character set to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_mwcname_sized: {
			ztdc_thrd_attr_mwcname_sized* __attr = (ztdc_thrd_attr_mwcname_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				// TODO: convert from wide execution character set to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c8name: {
			ztdc_thrd_attr_c8name* __attr = (ztdc_thrd_attr_c8name*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				// TODO: convert from wide execution character set to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c8name_sized: {
			ztdc_thrd_attr_c8name_sized* __attr = (ztdc_thrd_attr_c8name_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c16name: {
			ztdc_thrd_attr_c16name* __attr = (ztdc_thrd_attr_c16name*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				// TODO: convert from UTF-16 to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c16name_sized: {
			ztdc_thrd_attr_c16name_sized* __attr = (ztdc_thrd_attr_c16name_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				// TODO: convert from UTF-16 to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c32name: {
			ztdc_thrd_attr_c32name* __attr = (ztdc_thrd_attr_c32name*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = ztdc_c_string_ptr_size(__attr->name);
				// TODO: convert from UTF-43 to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_c32name_sized: {
			ztdc_thrd_attr_c32name_sized* __attr = (ztdc_thrd_attr_c32name_sized*)__attr_kind;
			if (__attr->name) {
				const size_t __name_size = __attr->size;
				// TODO: convert from UTF-43 to UTF-8
				__ztdc_pthread_prepare_name_trampoline(__trampoline_userdata, __name_size, __attr->name);
			}
		} break;
		case ztdc_thrd_attr_kind_stack_size: {
			ztdc_thrd_attr_stack_size* __attr = (ztdc_thrd_attr_stack_size*)__attr_kind;
			pthread_attr_setstacksize(&__impl_attrs, __attr->size);
		} break;
		case ztdc_thrd_attr_kind_stack_storage: {
			ztdc_thrd_attr_stack_storage* __attr = (ztdc_thrd_attr_stack_storage*)__attr_kind;
			pthread_attr_setstack(&__impl_attrs, __attr->buffer, __attr->size);
		} break;
		case ztdc_thrd_attr_kind_detached: {
			ztdc_thrd_attr_detached* __attr = (ztdc_thrd_attr_detached*)__attr_kind;
			pthread_attr_setdetachstate(&__impl_attrs, __attr->detached ? 1 : 0);
		} break;
		default:
			break;
		}
	}
#if ZTD_IS_ON(ZTD_HEADER_THREADS_H)
	pthread_t __raw_thr = { 0 };
	int __result        = pthread_create(&__raw_thr, &__impl_attrs, __ztdc_pthread_trampoline, arg);
	if (__result == 0) {
		*__thr = (thrd_t)__raw_thr;
	}
	return __result ? thrd_success : thrd_error;
#else
	__trampoline_userdata->__func     = __func;
	__trampoline_userdata->__func_arg = __func_arg;
	int __res      = pthread_create(__thr, &__impl_attrs, __ztdc_pthread_trampoline, __trampoline_userdata);
	int __attr_res = pthread_attr_destroy(&__impl_attrs);
	(void)__attr_res;
	if (__res != 0) {
		return __ztdc_to_thread_error(__res);
	}
	return thrd_success;
#endif
}
