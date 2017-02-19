#include "testApp.h"
#include "ofxDelaunay2D.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255,250,240);
    
    ofNoFill();
    ofSetColor(0,70,255);
    m_triangulation.drawWireframe();

    ofFill();
    ofSetColor(200,0,50);
    for(size_t i=0; i<m_points.size(); ++i) {
        ofCircle(m_points[i].x, m_points[i].y, 3);
    }
    
    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
    ofDrawBitmapString("Click to add points.", ofPoint(10,40));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'r'){
        m_triangulation.clear();
        m_points.clear();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
    m_points.push_back(ofVec2f(x,y));
    m_triangulation = ofxDelaunay2D::triangulate(m_points);
    // printf("indices %d %d\n", m_triangulation.getNumIndices(), m_triangulation.getNumVertices());
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
