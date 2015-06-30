/*
 *  ofxDelaunay.h
 *
 *  Created by Pat Long on 29/10/09.
 *  Copyright 2009 Tangible Interaction. All rights reserved.
 *
 *  Some parts based on demo code by Gilles Dumoulin.
 *  Source: http://local.wasp.uwa.edu.au/~pbourke/papers/triangulate/cpp.zip
 *
 *	Cleaned up by Lukasz Karluk, 19/05/2010
 *
 *  Refactored for 0071 + ofMesh by James George on 21/06/2012
 *
 *  Fixing of memory bugs and massive API simplification by Marcel Ruegenberg in 2015.
 */

#include "ofxDelaunay2D.h"
#include "Delaunay.h"
#include <cassert>

struct XYI{
    double x, y;
    int i; // index
};

int XYICompare(const void *v1, const void *v2){
    XYI *p1, *p2;

    p1 = (XYI*)v1;
    p2 = (XYI*)v2;
    if(p1->x < p2->x)
        return(-1);
    else if(p1->x > p2->x)
        return(1);
    else
        return(0);
}

ofMesh ofxDelaunay2D::triangulate(vector<ofVec2f> &points) {
    ofMesh result;
    
    if(points.size() < 3){
        return result;
    }

    int nv = points.size();

    // make clone not to destroy vertices
    vector<XYI> verticesTemp; verticesTemp.reserve(points.size());
    for(int i=0; i<nv; ++i) {
        XYI v;
        v.x = points[i].x;
        v.y = points[i].y;
        v.i = i;
        verticesTemp.push_back(v);
    }
    qsort( &verticesTemp[0], verticesTemp.size(), sizeof( XYI ), XYICompare );

    //vertices required for Triangulate
    vector<XY> verticesXY;

    //copy XYZIs to XYZ
    for (int i = 0; i < nv; i++) {
        XY v;
        v.x = verticesTemp.at(i).x;
        v.y = verticesTemp.at(i).y;
        verticesXY.push_back(v);
    }

    //add 3 emptly slots, required by the Triangulate call
    verticesXY.push_back(XY());
    verticesXY.push_back(XY());
    verticesXY.push_back(XY());

    int ntri;
    vector<ITRIANGLE> triangles;
    
    //allocate space for triangle indices
    triangles.resize(4*nv); // be sure that Triangulate never uses more triangles than this!

    Triangulate( nv, &verticesXY[0], &triangles[0], ntri );

    //copy triangle data to ofxDelaunay2DTriangle.
    result.setMode(OF_PRIMITIVE_TRIANGLES);

    //copy vertices
    for (int i = 0; i < nv; i++){
        result.addVertex(ofVec3f(points[i].x,points[i].y,0.0));
    }

    //copy triangles
    for(int i = 0; i < ntri; i++) {
        //if(triangles[i].p1 > nv)
        //    printf("Tri %d %d | %d %d %d", i, ntri, triangles[ i ].p1, triangles[ i ].p2, triangles[ i ].p3);
        assert(triangles[i].p1 <= nv);
        result.addIndex(verticesTemp.at(triangles[ i ].p1).i);
        assert(triangles[i].p2 <= nv);
        result.addIndex(verticesTemp.at(triangles[ i ].p2).i);
        assert(triangles[i].p3 <= nv);
        result.addIndex(verticesTemp.at(triangles[ i ].p3).i);
    }

    return result;
}

// adjacency list of triangulation
vector< set<size_t> > ofxDelaunay2D::adjacencyForTriMesh(ofMesh &triMesh) {
    vector< set<size_t> > adjacency; adjacency.reserve(triMesh.getNumVertices());

    for(size_t i=0; i<(size_t)(triMesh.getNumVertices()); ++i) {
        adjacency.push_back(set<size_t>());
    }

    for(int i0=0; i0<(int)triMesh.getIndices().size() - 2; i0+=3) {
        size_t i = triMesh.getIndex(i0);
        size_t j = triMesh.getIndex(i0 + 1);
        size_t k = triMesh.getIndex(i0 + 2);

        adjacency[i].insert(j);
        adjacency[j].insert(i);
        adjacency[i].insert(k);
        adjacency[k].insert(i);
        adjacency[j].insert(k);
        adjacency[k].insert(j);
    }

    return adjacency;
}
