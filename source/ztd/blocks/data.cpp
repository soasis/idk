/*
 * data.c
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

/********************
NSBlock support

We allocate space and export a symbol to be used as the Class for the on-stack and malloc'ed copies until ObjC arrives
on the scene.  These data areas are set up by Foundation to link in as real classes post facto.

We keep these in a separate file so that we can include the runtime code in test subprojects but not include the data so
that compiled code that sees the data in libSystem doesn't get confused by a second copy.  Somehow these don't get
unified in a common block.
**********************/

// modifications made to be packaged in C++ and be cross-platform between MacOS, Windows, and typical *nix installations
// taken from: https://github.com/llvm/llvm-project

#include <ztd/version/version.h>

ZTD_USE(ZTD_EXTERN_C_OPEN)

ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteStackBlock[32]        = { 0 };
ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteMallocBlock[32]       = { 0 };
ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteAutoBlock[32]         = { 0 };
ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteFinalizingBlock[32]   = { 0 };
ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteGlobalBlock[32]       = { 0 };
ZTD_USE(ZTD_ATTR_WEAK_VAR) void* _NSConcreteWeakBlockVariable[32] = { 0 };

ZTD_USE(ZTD_ATTR_WEAK_FUNC_DEF) void _Block_copy_error(void) {
}

ZTD_USE(ZTD_EXTERN_C_CLOSE)
