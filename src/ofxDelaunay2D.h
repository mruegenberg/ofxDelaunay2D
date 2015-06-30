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
 *  Fixing of memory bugs and a massive API simplification by Marcel Ruegenberg in 2015.
 */

#pragma once

#include "ofMain.h"

class ofxDelaunay2D {

public:

    /// returns a triangle mesh, i.e each 3 set of 3 indices makes up one triangle in the triangulation
    static ofMesh triangulate(vector<ofVec2f> &points);

    /// computes an unidirectional adjacency list for a triangle mesh.
    /// for each edge (i,j) in the mesh, results[i] contains j if i < j
    static vector< set<size_t> > adjacencyForTriMesh(ofMesh &triMesh);
};
