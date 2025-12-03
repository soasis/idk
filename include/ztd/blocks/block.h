/*
 * Block.h
 *
 * Copyright 2008-2010 Apple, Inc. Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

// modifications made to be packaged in C++ and be cross-platform between MacOS, Windows, and typical *nix installations
// taken from: https://github.com/llvm/llvm-project

#include <ztd/version.h>

#include <ztd/idk/typeof.h>

#ifndef ZTD_IDK_BLOCKS_BLOCK_H
#define ZTD_IDK_BLOCKS_BLOCK_H

#define ZTD_IDK_VERSION_MAJOR 1
#define ZTD_IDK_VERSION_MINOR 0
#define ZTD_IDK_VERSION_PATCH 0
#define ZTD_IDK_VERSION_STRING ZTD_MAKE_VERSION_STR(ZTD_IDK_VERSION_MAJOR, ZTD_IDK_VERSION_MINOR, ZTD_IDK_VERSION_PATCH)
#define ZTD_IDK_VERSION ZTD_MAKE_VERSION_INT(ZTD_IDK_VERSION_MAJOR, ZTD_IDK_VERSION_MINOR, ZTD_IDK_VERSION_PATCH)

#include <ztd/blocks/detail/api.h>

ZTD_USE(ZTD_EXTERN_C_OPEN)

/* Create a heap based copy of a Block or simply add a reference to an existing one.
 * This must be paired with Block_release to recover memory, even when running
 * under Objective-C Garbage Collection.
 */
ZTD_USE(ZTD_BLOCKS_API_LINKAGE) ZTD_USE(ZTD_EXTERN_C) void* _Block_copy(const void* aBlock) ZTD_USE(ZTD_ATTR_WEAK_FUNC);

/* Lose the reference, and if heap based and last reference, recover the memory. */
ZTD_USE(ZTD_BLOCKS_API_LINKAGE)
ZTD_USE(ZTD_EXTERN_C) void _Block_release(const void* aBlock) ZTD_USE(ZTD_ATTR_WEAK_FUNC);

ZTD_USE(ZTD_EXTERN_C_CLOSE)

/* Type correct macros. */

#define Block_copy(...) ((ztd_typeof(__VA_ARGS__))_Block_copy((const void*)(__VA_ARGS__)))
#define Block_release(...) _Block_release((const void*)(__VA_ARGS__))


#endif