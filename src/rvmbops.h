#include <Windows.h>
#include <cstdio>
#include <cassert>
#include <string>
#include <cctype>
#include <chrono>
#include <algorithm>

#include "Parser.h"
#include "Tessellator.h"
#include "ExportObj.h"
#include "Store.h"
#include "Flatten.h"
#include "AddStats.h"
#include "DumpNames.h"
#include "ChunkTiny.h"
#include "AddGroupBBox.h"
#include "Colorizer.h"

#include "RVMTriMesh.h"

//#ifdef  __cplusplus

typedef void* cmesh;

extern "C" cmesh get_rvm_mesh(char *rvmfilename);

//#endif