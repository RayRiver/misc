#ifndef GXMacros_h__
#define GXMacros_h__

#ifdef __cplusplus
#define NS_GX_BEGIN                     namespace GX {
#define NS_GX_END                       }
#define USING_NS_GX                     using namespace GX
#else
#define NS_GX_BEGIN
#define NS_GX_END
#define USING_NS_GX
#endif

#ifdef GX_DISABLE_ASSERT
#define GX_ASSERT(expr) ((void)0)
#else
#define GX_ASSERT(expr) assert(expr)
#endif

#endif // GXMacros_h__
