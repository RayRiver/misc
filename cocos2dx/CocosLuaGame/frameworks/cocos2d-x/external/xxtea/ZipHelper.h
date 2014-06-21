/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_ZIP_HELPER_H_
#define __CC_ZIP_HELPER_H_

#include <string>
#include "base/CCRef.h"

NS_CC_BEGIN

class CC_DLL ZipHelper : public Ref
{
public:
    static ZipHelper *create(const char *zipFilename);
    static ZipHelper *createWithBuffer(const void* buffer, unsigned long size);
    ~ZipHelper(void);
    
    const std::string getFirstFilename(void);
    const std::string getNextFilename(void);
    
    unsigned char* getFileData(const char *filename, unsigned long *filesize);
    void close(void);
    
private:
    ZipHelper();
    bool initWithFilename(const char *zipFilename);
    bool initWithBuffer(const void *buffer, unsigned long size);

	struct IMP_T;
	IMP_T *m;
};

NS_CC_END

#endif /* defined(__CC_ZIP_HELPER_H_) */
