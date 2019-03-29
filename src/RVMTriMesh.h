#pragma once
#include <cstdio>
#include <cstring>
#include <assert.h>

#include "Common.h"
#include "StoreVisitor.h"
#include "Store.h"
#include "cork.h"

class RVMTriMesh: public StoreVisitor{
public:
  ~RVMTriMesh();
  void geometry(struct Geometry* geometry) override;
  void beginModel(Group* group) override;
  void endModel() override;
  CorkTriMesh* get_mesh();
private:
  CorkTriMesh* m_mesh;
  CorkTriMesh* tri2CorkTriMesh(Geometry* geometry);
};

