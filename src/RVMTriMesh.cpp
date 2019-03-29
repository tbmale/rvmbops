#include "RVMTriMesh.h"

void RVMTriMesh::beginModel(Group* group){
  m_mesh=new CorkTriMesh();
}
void RVMTriMesh::endModel(){
}

void RVMTriMesh::geometry(struct Geometry* geometry){
  assert(geometry->triangulation);
  if(m_mesh->n_vertices==0){
    m_mesh=RVMTriMesh::tri2CorkTriMesh(geometry);
    return;
  }
  CorkTriMesh* current_geom = RVMTriMesh::tri2CorkTriMesh(geometry);
  CorkTriMesh* out=new CorkTriMesh();
  computeUnion(*m_mesh,*current_geom,out);
  m_mesh=out;
  freeCorkTriMesh(current_geom);
}

CorkTriMesh* RVMTriMesh::get_mesh(){
  return m_mesh;
}

CorkTriMesh* RVMTriMesh::tri2CorkTriMesh(Geometry* geometry){
  CorkTriMesh* mesh=new CorkTriMesh();
  auto * tri = geometry->triangulation;
  auto out = stdout;
  if (tri->indices != 0) {
    if (geometry->triangulation->error != 0.f) {
      fprintf(out, "# error=%f\n", geometry->triangulation->error);
    }
    mesh->n_triangles=tri->triangles_n;
    mesh->n_vertices=tri->vertices_n;
    mesh->triangles = new uint[mesh->n_triangles];
    mesh->vertices  = new float[mesh->n_vertices];
    memcpy(tri->vertices,mesh->vertices,mesh->n_vertices);
    memcpy(tri->indices,mesh->triangles,mesh->n_triangles);
  }
  return mesh;
}
