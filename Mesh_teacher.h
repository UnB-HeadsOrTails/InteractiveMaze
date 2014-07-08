/*
 *mesh.h
 */
#ifndef MESH_H_
#define MESH_H_

typedef struct{
    float x,y,z;
}vertex;

typedef struct{
    int v1,v2,v3;
    float xn,yn,zn;
}face;

typedef struct{
    int R,G,B;
}color;

typedef struct{
    vertex *list_vertex;
    face *list_faces;
    color *list_color;
    int nvertex;
    int nface;
    int ncolor;
    float XMax, XMin, YMax, YMin, ZMax, ZMin;
}mesh;

mesh *New_Mesh();
int Del_Mesh(mesh *pmesh);
int Load_Mesh(mesh *pmesh, char *File_Name);
int Render_Mesh(mesh *pmesh);
int Resize_Mesh(mesh *pmesh);
int Render_Room(void);
#endif
