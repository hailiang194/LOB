
#ifndef LOB_EXPORT_H
#define LOB_EXPORT_H

#ifdef LOB_STATIC_DEFINE
#  define LOB_EXPORT
#  define LOB_NO_EXPORT
#else
#  ifndef LOB_EXPORT
#    ifdef lob_EXPORTS
        /* We are building this library */
#      define LOB_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LOB_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LOB_NO_EXPORT
#    define LOB_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LOB_DEPRECATED
#  define LOB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LOB_DEPRECATED_EXPORT
#  define LOB_DEPRECATED_EXPORT LOB_EXPORT LOB_DEPRECATED
#endif

#ifndef LOB_DEPRECATED_NO_EXPORT
#  define LOB_DEPRECATED_NO_EXPORT LOB_NO_EXPORT LOB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LOB_NO_DEPRECATED
#    define LOB_NO_DEPRECATED
#  endif
#endif

#endif /* LOB_EXPORT_H */
