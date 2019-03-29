#include "rvmbops.h"

void logger(unsigned level, const char* msg, ...)
{
  switch (level) {
  case 0: fprintf(stderr, "[I] "); break;
  case 1: fprintf(stderr, "[W] "); break;
  case 2: fprintf(stderr, "[E] "); break;
  }

  va_list argptr;
  va_start(argptr, msg);
  vfprintf(stderr, msg, argptr);
  va_end(argptr);
  fprintf(stderr, "\n");
}

template<typename F>
bool
processFile(const std::string& path, F f)
{
  bool rv = false;
  HANDLE h = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (h == INVALID_HANDLE_VALUE) {
    logger(2, "CreateFileA returned INVALID_HANDLE_VALUE");
    rv = false;
  }
  else {
    DWORD hiSize;
    DWORD loSize = GetFileSize(h, &hiSize);
    size_t fileSize = (size_t(hiSize) << 32u) + loSize;

    HANDLE m = CreateFileMappingA(h, 0, PAGE_READONLY, 0, 0, NULL);
    if (m == INVALID_HANDLE_VALUE) {
      logger(2, "CreateFileMappingA returned INVALID_HANDLE_VALUE");
      rv = false;
    }
    else {
      const void * ptr = MapViewOfFile(m, FILE_MAP_READ, 0, 0, 0);
      if (ptr == nullptr) {
        logger(2, "MapViewOfFile returned INVALID_HANDLE_VALUE");
        rv = false;
      }
      else {
        rv = f(ptr, fileSize);
        UnmapViewOfFile(ptr);
      }
      CloseHandle(m);
    }
    CloseHandle(h);
  }
  return rv;

}

cmesh get_rvm_mesh(char *rvmfilename){
  RVMTriMesh* rvm=new RVMTriMesh();
  return reinterpret_cast<void*>(rvm)->get_mesh();
}