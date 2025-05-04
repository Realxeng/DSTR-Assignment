//#pragma once
//#include <sys/resource.h>
//#include <cstddef>
//
//// Returns the peak resident set size in KB on Linux, bytes on macOS (we normalize to KB)
//inline std::size_t peakMemoryKB() {
//    struct rusage usage;
//    getrusage(RUSAGE_SELF, &usage);
//  #ifdef __APPLE__
//    // On macOS, ru_maxrss is in bytes
//    return usage.ru_maxrss / 1024;
//  #else
//    // On Linux, ru_maxrss is in kilobytes
//    return usage.ru_maxrss;
//  #endif
//}