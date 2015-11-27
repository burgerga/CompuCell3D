
#ifndef SAVECOM_EXPORT_H
#define SAVECOM_EXPORT_H

    #if defined(_WIN32)
      #ifdef SaveCOMShared_EXPORTS
          #define SAVECOM_EXPORT __declspec(dllexport)
          #define SAVECOM_EXPIMP_TEMPLATE
      #else
          #define SAVECOM_EXPORT __declspec(dllimport)
          #define SAVECOM_EXPIMP_TEMPLATE extern
      #endif
    #else
         #define SAVECOM_EXPORT
         #define SAVECOM_EXPIMP_TEMPLATE
    #endif

#endif
