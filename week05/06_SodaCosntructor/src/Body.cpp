//
//  Body.cpp
//
//  Created by Patricio Gonzalez Vivo on 11/13/12.
//
//

#include "Body.h"

Body::Body(){
    bEdit           = false;
    bRightClick     = false;
    nVertexSelected = -1;
    nVertexHover    = -1;
    nVertexSelected = -1;
    nSpringHover    = -1;
    imageFile       = "none";
    origin          = ofPoint(-1,-1);
    imageCenter     = ofPoint(-1,-1);
}

Body::~Body(){
    clear();
}

// ----------------------------------------------------- SETUP
bool Body::init(string _file, ofPoint _initPos){
    if ( image.loadImage(_file) ){
        imageFile = _file;
        imageCenter.set(image.getWidth()*0.5, image.getHeight()*0.5);

        origin = _initPos;
        
        clear();
        
        return true;
    } else {
        return false;
    }
}

bool Body::load( string _file, ofPoint _initPos ){
    
    ofxXmlSettings XML;
    if (XML.loadFile(_file)){
        if (init( XML.getValue("texture", "image.png") ,_initPos)){
            
            //  Load the Vertex
            //
            int nVertex     = XML.getNumTags("vertex");
            for (int i = 0; i < nVertex; i++){
                if ( XML.pushTag("vertex",i ) ){
                    ofPoint pos = ofPoint(ofPoint(XML.getValue("pos:x", 0.0),
                                                  XML.getValue("pos:y", 0.0) ) );
                    addVertex( pos );
                    vertices[ vertices.size()-1 ]->nId = XML.getValue("nId", 1);
                                          
                    XML.popTag();
                }
            }
            
            //  Load the Spring
            //
            int nSprings    = XML.getNumTags("spring");
            for (int i = 0; i < nSprings; i++){
                if ( XML.pushTag("spring",i ) ){
                    int A   = XML.getValue("A", -1);
                    int B   = XML.getValue("B", -1);
                    float k = XML.getValue("k", 0.5);
                    
                    addSpring( _getIndexForId(A), _getIndexForId(B), k);
                    XML.popTag();
                }
            }
        }
        _calculateTriangles();
        _updateMesh();
        
        return true;
    } else {
        return false;
    }
}

bool Body::save( string _file ){
    
    ofxXmlSettings XML;
    XML.loadFile(_file);
    
    //  Image Ref
    //
    XML.setValue("texture",imageFile);
                 
    //  Add Verteces
    //
    for (int i = 0; i < vertices.size() ; i++){
        XML.addTag("vertex");
    }
    
    for (int i = 0; i < vertices.size(); i++){
        if ( XML.pushTag("vertex",i ) ){
            
            XML.setValue("pos:x", vertices[i]->getTexCoord().x);
            XML.setValue("pos:y", vertices[i]->getTexCoord().y);
            XML.setValue("nId", vertices[i]->nId);
            
            XML.popTag();
        }
    }
    
    //  Add Springs
    //
    for (int i = 0; i < springs.size() ; i++){
        XML.addTag("spring");
    }
    
    for (int i = 0; i < springs.size(); i++){
        if ( XML.pushTag("spring",i ) ){
            
            XML.setValue("A", springs[i].vertexA->nId);
            XML.setValue("B", springs[i].vertexB->nId);
            XML.setValue("k", springs[i].k );
            
            XML.popTag();
        }
    }

    return XML.saveFile(_file);
}

void Body::startEditMode(){
    if (!bEdit){
        ofAddListener(ofEvents().mousePressed, this, &Body::_mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &Body::_mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &Body::_mouseReleased);
        nVertexSelected = -1;
        nVertexHover    = -1;
        nVertexSelected = -1;
        nSpringHover    = -1;
        bEdit = true;
    }
}

void Body::stopEditMode(){
    if (bEdit){
        ofRemoveListener(ofEvents().mousePressed, this, &Body::_mousePressed);
        ofRemoveListener(ofEvents().mouseDragged, this, &Body::_mouseDragged);
        ofRemoveListener(ofEvents().mouseReleased, this, &Body::_mouseReleased);
        nVertexSelected = -1;
        nVertexHover    = -1;
        nVertexSelected = -1;
        nSpringHover    = -1;
        bEdit = false;
    }
}

void Body::togleEditMode(){
    if(!bEdit){
        startEditMode();
    } else {
        stopEditMode();
    }
}

void Body::clear(){
    for(int i = 0; i < vertices.size(); i++){
        delete vertices[i];
    }
    vertices.clear();
    triangles.clear();
    springs.clear();
}

void Body::restart(){
    for(int i = 0; i < vertices.size(); i++){
        ofPoint toCenter = vertices[i]->getTexCoord() - imageCenter;
        float angle = atan2(toCenter.y,toCenter.x);
        float radio = toCenter.length();
        
        vertices[i]->x = origin.x + cos(angle)*radio;
        vertices[i]->y = origin.y + sin(angle)*radio;
        
        //vertices[i]->vel.set(0,0);
    }
}

// -------------------------------------------- INFO ( Maths ) 
int Body::_getIndexForId(int _nId){
    int rta = -1;
    
    for(int i = 0; i < vertices.size(); i++){
        if ( vertices[i]->nId == _nId){
            rta = i;
            break;
        }
    }
    
    return rta;
}

ofPoint Body::_getNormalPoint(ofPoint p, ofPoint a, ofPoint b) {
    ofPoint ap = p - a;
    ofPoint ab = b - a;
    ab.normalize();
    ab *= ap.dot(ab);
    return a+ab;
}

int Body::getVertexIndexAt( ofPoint _pos, float _maxDist ){
    int rta = -1;
    
    for (int i = 0; i < vertices.size(); i++) {
        if (_pos.distance( vertices[i]->getTexCoord() ) < _maxDist){
            rta = i;
        }
    }
    
    return rta;
}

int Body::getSpringIndexAt( ofPoint _pos, float _maxDist ){
    int rta = -1;
    
    for (int i = 0; i < springs.size() ; i++) {
        
        ofPoint a = springs[i].vertexA->getTexCoord();
        ofPoint b = springs[i].vertexB->getTexCoord();
        float   distance = springs[i].dist;
        
        ofPoint normalPoint = _getNormalPoint(_pos, a, b);
        
        if ( (b-a).length() == (normalPoint - a).length() + (b - normalPoint).length() ){
            if (_pos.distance(normalPoint) < _maxDist){
                rta = i;
                break;
            }
        }
    }
    
    return rta;
}
//---------------------------------------------------- ACCIONS ( PHYSICS )
void Body::addVertex(ofPoint _pos){
    Vertex *newVertex = new Vertex();
    
    newVertex->setTexCoord(_pos);
    
    ofPoint toCenter = _pos - imageCenter;
    float angle = atan2(toCenter.y,toCenter.x);
    float radio = toCenter.length();
    
    newVertex->x = origin.x + cos(angle)*radio;
    newVertex->y = origin.y + sin(angle)*radio;
    newVertex->nId = vertices.size();
    
    vertices.push_back(newVertex);
}

bool Body::addSpring(unsigned int _from, unsigned int _to, float _k ){
    bool rta = false;
    
    if ( (_from < vertices.size()) && (_to < vertices.size()) && (_to != _from) ){
        Spring newSpring;
        
		newSpring.k         = _k;
		newSpring.vertexA   = vertices[ _from];
		newSpring.vertexB   = vertices[ _to];
        newSpring.dist      = vertices[ _from]->getTexCoord().distance( vertices[ _to]->getTexCoord() );
        
        springs.push_back(newSpring);
        rta = true;
    }
    
    return rta;
}

void Body::_updateSpringsConectedTo(int _index){
    int nId = vertices[_index]->nId;
    
    for (int i = 0; i < springs.size(); i++){
        if ( (springs[i].vertexA->nId == nId) || ( springs[i].vertexB->nId == nId) ){
            springs[i].dist = springs[i].vertexA->getTexCoord().distance(springs[i].vertexB->getTexCoord());
        }
    }
}

void Body::update(VectorField *_VF){
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
    for (int i = 0; i < vertices.size(); i++){
        
        //  Gravity
        //
//		vertices[i]->addForce(0,0.1f);
        
        //  Simple Mouse Interaction
        //
		vertices[i]->addRepulsionForce(ofPoint (ofGetMouseX(), ofGetMouseY()), 300, 0.7f);
        
        //  If there is a VectorFeal use it
        //
        if(_VF != NULL){
            if ( _VF->inside( *vertices[i] ) ){
                vertices[i]->addForce(  _VF->getForceFromPos( *vertices[i] ) );
            }
        }
        
        vertices[i]->bounceOffWalls();
		vertices[i]->update();
	}
}

//------------------------------------------------- RENDERING

// comparison routine for sort...
//
bool comparisonFunction(  Vertex * a, Vertex * b ) {
	return a->getTexCoord().x < b->getTexCoord().x;
}

void Body::_calculateTriangles(){
    //  Prepare the vertices
    //
    nVertexSelected = -1;
    int nv = vertices.size();
    
    if (nv >= 3){
        sort( vertices.begin(), vertices.end(), comparisonFunction );
        
        //  Extract the origin postions
        //
        vector<ofPoint> tmpVertices;
        for (int i = 0 ; i < vertices.size(); i++) {
            ofPoint newPoint = vertices[i]->getTexCoord();
            tmpVertices.push_back( newPoint );
        }
        
        //  Add 3 more slots ( required by the Triangulate call)
        //
        tmpVertices.push_back( ofPoint(0,0) );
        tmpVertices.push_back( ofPoint(0,0) );
        tmpVertices.push_back( ofPoint(0,0) );
        
        //  Allocate space for triangles indices
        //
        triangles.resize(3*nv);
        
        //  Make the triangulation
        //
        nTriangles = 0;
        Triangulate( nv, &tmpVertices[0], &triangles[0], nTriangles );
    }
}

////////////////////////////////////////////////////////////////////////
// CircumCircle() :
//   Return true if a point (xp,yp) is inside the circumcircle made up
//   of the points (x1,y1), (x2,y2), (x3,y3)
//   The circumcircle centre is returned in (xc,yc) and the radius r
//   Note : A point on the edge is inside the circumcircle
////////////////////////////////////////////////////////////////////////

int CircumCircle(double xp, double yp, double x1, double y1, double x2,
                 double y2, double x3, double y3, double &xc, double &yc, double &r){
    double m1, m2, mx1, mx2, my1, my2;
    double dx, dy, rsqr, drsqr;
    
    /* Check for coincident points */
    if(abs(y1 - y2) < EPSILON && abs(y2 - y3) < EPSILON)
        return(false);
    if(abs(y2-y1) < EPSILON){
        m2 = - (x3 - x2) / (y3 - y2);
        mx2 = (x2 + x3) / 2.0;
        my2 = (y2 + y3) / 2.0;
        xc = (x2 + x1) / 2.0;
        yc = m2 * (xc - mx2) + my2;
    }else if(abs(y3 - y2) < EPSILON){
        m1 = - (x2 - x1) / (y2 - y1);
        mx1 = (x1 + x2) / 2.0;
        my1 = (y1 + y2) / 2.0;
        xc = (x3 + x2) / 2.0;
        yc = m1 * (xc - mx1) + my1;
    }else{
        m1 = - (x2 - x1) / (y2 - y1);
        m2 = - (x3 - x2) / (y3 - y2);
        mx1 = (x1 + x2) / 2.0;
        mx2 = (x2 + x3) / 2.0;
        my1 = (y1 + y2) / 2.0;
        my2 = (y2 + y3) / 2.0;
        xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        yc = m1 * (xc - mx1) + my1;
    }
    dx = x2 - xc;
    dy = y2 - yc;
    rsqr = dx * dx + dy * dy;
    r = sqrt(rsqr);
    dx = xp - xc;
    dy = yp - yc;
    drsqr = dx * dx + dy * dy;
    return((drsqr <= rsqr) ? true : false);
}


///////////////////////////////////////////////////////////////////////////////
// Triangulate() :
//   Triangulation subroutine
//   Takes as input NV vertices in array pxyz
//   Returned is a list of ntri triangular faces in the array v
//   These triangles are arranged in a consistent clockwise order.
//   The triangle array 'v' should be malloced to 3 * nv
//   The vertex array pxyz must be big enough to hold 3 more points
//   The vertex array must be sorted in increasing x values say
//
//   qsort(p,nv,sizeof(XYZ),XYZCompare);
///////////////////////////////////////////////////////////////////////////////

int Triangulate(int nv, ofPoint pxyz[], Triangle v[], int &ntri){
    int *complete = NULL;
    Edge *edges = NULL;
    Edge *p_EdgeTemp;
    int nedge = 0;
    int trimax, emax = 200;
    int status = 0;
    int inside;
    int i, j, k;
    double xp, yp, x1, y1, x2, y2, x3, y3, xc, yc, r;
    double xmin, xmax, ymin, ymax, xmid, ymid;
    double dx, dy, dmax;
    
    /* Allocate memory for the completeness list, flag for each triangle */
    trimax = 4 * nv;
    complete = new int[trimax];
    /* Allocate memory for the edge list */
    edges = new Edge[emax];
    /*
     Find the maximum and minimum vertex bounds.
     This is to allow calculation of the bounding triangle
     */
    xmin = pxyz[0].x;
    ymin = pxyz[0].y;
    xmax = xmin;
    ymax = ymin;
    for(i = 1; i < nv; i++){
        if (pxyz[i].x < xmin) xmin = pxyz[i].x;
        if (pxyz[i].x > xmax) xmax = pxyz[i].x;
        if (pxyz[i].y < ymin) ymin = pxyz[i].y;
        if (pxyz[i].y > ymax) ymax = pxyz[i].y;
    }
    dx = xmax - xmin;
    dy = ymax - ymin;
    dmax = (dx > dy) ? dx : dy;
    xmid = (xmax + xmin) / 2.0;
    ymid = (ymax + ymin) / 2.0;
    /*
     Set up the supertriangle
     his is a triangle which encompasses all the sample points.
     The supertriangle coordinates are added to the end of the
     vertex list. The supertriangle is the first triangle in
     the triangle list.
     */
    pxyz[nv+0].x = xmid - 20 * dmax;
    pxyz[nv+0].y = ymid - dmax;
    pxyz[nv+1].x = xmid;
    pxyz[nv+1].y = ymid + 20 * dmax;
    pxyz[nv+2].x = xmid + 20 * dmax;
    pxyz[nv+2].y = ymid - dmax;
    v[0].p1 = nv;
    v[0].p2 = nv+1;
    v[0].p3 = nv+2;
    complete[0] = false;
    ntri = 1;
    /*
     Include each point one at a time into the existing mesh
     */
    for(i = 0; i < nv; i++){
        xp = pxyz[i].x;
        yp = pxyz[i].y;
        nedge = 0;
        /*
         Set up the edge buffer.
         If the point (xp,yp) lies inside the circumcircle then the
         three edges of that triangle are added to the edge buffer
         and that triangle is removed.
         */
        for(j = 0; j < ntri; j++){
            if(complete[j])
                continue;
            x1 = pxyz[v[j].p1].x;
            y1 = pxyz[v[j].p1].y;
            x2 = pxyz[v[j].p2].x;
            y2 = pxyz[v[j].p2].y;
            x3 = pxyz[v[j].p3].x;
            y3 = pxyz[v[j].p3].y;
            inside = CircumCircle(xp, yp, x1, y1, x2, y2, x3, y3, xc, yc, r);
            if (xc + r < xp)
                // Suggested
                // if (xc + r + EPSILON < xp)
                complete[j] = true;
            if(inside){
                /* Check that we haven't exceeded the edge list size */
                if(nedge + 3 >= emax){
                    emax += 100;
                    p_EdgeTemp = new Edge[emax];
                    for (int i = 0; i < nedge; i++) { // Fix by John Bowman
                        p_EdgeTemp[i] = edges[i];
                    }
                    delete []edges;
                    edges = p_EdgeTemp;
                }
                edges[nedge+0].p1 = v[j].p1;
                edges[nedge+0].p2 = v[j].p2;
                edges[nedge+1].p1 = v[j].p2;
                edges[nedge+1].p2 = v[j].p3;
                edges[nedge+2].p1 = v[j].p3;
                edges[nedge+2].p2 = v[j].p1;
                nedge += 3;
                v[j] = v[ntri-1];
                complete[j] = complete[ntri-1];
                ntri--;
                j--;
            }
        }
        /*
         Tag multiple edges
         Note: if all triangles are specified anticlockwise then all
         interior edges are opposite pointing in direction.
         */
        for(j = 0; j < nedge - 1; j++){
            for(k = j + 1; k < nedge; k++){
                if((edges[j].p1 == edges[k].p2) && (edges[j].p2 == edges[k].p1)){
                    edges[j].p1 = -1;
                    edges[j].p2 = -1;
                    edges[k].p1 = -1;
                    edges[k].p2 = -1;
                }
                /* Shouldn't need the following, see note above */
                if((edges[j].p1 == edges[k].p1) && (edges[j].p2 == edges[k].p2)){
                    edges[j].p1 = -1;
                    edges[j].p2 = -1;
                    edges[k].p1 = -1;
                    edges[k].p2 = -1;
                }
            }
        }
        /*
         Form new triangles for the current point
         Skipping over any tagged edges.
         All edges are arranged in clockwise order.
         */
        for(j = 0; j < nedge; j++) {
            if(edges[j].p1 < 0 || edges[j].p2 < 0)
                continue;
            v[ntri].p1 = edges[j].p1;
            v[ntri].p2 = edges[j].p2;
            v[ntri].p3 = i;
            complete[ntri] = false;
            ntri++;
        }
    }
    /*
     Remove triangles with supertriangle vertices
     These are triangles which have a vertex number greater than nv
     */
    for(i = 0; i < ntri; i++) {
        if(v[i].p1 >= nv || v[i].p2 >= nv || v[i].p3 >= nv) {
            v[i] = v[ntri-1];
            ntri--;
            i--;
        }
    }
    delete[] edges;
    delete[] complete;
    return 0;
}

void Body::_updateMesh(){
	mesh.clear();
    
    //  Pass the position of the vertices
    //
	for (int i = 0; i < vertices.size(); i++){
        mesh.addVertex( *vertices[i] );
        mesh.addTexCoord( vertices[i]->getTexCoord() );
    }
    
    //  Pass the triagles indices of how to arrange them
    //
	for(int i = 0; i < nTriangles; i++){
		mesh.addIndex(triangles[ i ].p1);
		mesh.addIndex(triangles[ i ].p2);
		mesh.addIndex(triangles[ i ].p3);
	}
}

void Body::draw(){
    if (bEdit){
        ofPushStyle();
        
        //  Get Info
        //
        ofPoint mouse = ofPoint(ofGetMouseX(),ofGetMouseY());
        
        //  If nothing is selected then lisen hover states
        //
        if (nVertexSelected == -1 && nSpringSelected == -1){
            nVertexHover = getVertexIndexAt(mouse);
            nSpringHover = getSpringIndexAt(mouse);
        }
        
        //  Draw Texture
        //
        ofSetColor(255,100);
        image.draw(0, 0);
        
        //  Draw Springs
        //
        ofSetColor(255,200);
        ofFloatColor lineColor = ofFloatColor(1.0,0.0,0.0);
        for (int i = 0; i < springs.size(); i++){
            ofPushStyle();
            
            if (nSpringHover == i){
                ofSetLineWidth(3);
            }
            lineColor.setHue( 0.5 + springs[i].k );
            
            ofSetColor(lineColor,100);
            ofLine(springs[i].vertexA->getTexCoord(), springs[i].vertexB->getTexCoord());
            
            if ( nSpringHover == i){
                ofSetColor(lineColor, 255);
                ofDrawBitmapString(ofToString(springs[i].k), mouse.x+5, mouse.y - 5);
            }
            ofPopStyle();
        }
        
        //  Draw Vectors
        //
        ofSetColor(255,180);
        for (int i = 0; i < vertices.size(); i++){
            if ( i == nVertexHover){
                ofNoFill();
                ofCircle( vertices[i]->getTexCoord(), 5);
            }
            
            ofFill();
            ofCircle(vertices[i]->getTexCoord(),3);
        }
        
        //  There is spring setting in progress here
        //
        if(nVertexSelected != -1){
            ofNoFill();
            ofSetColor(255,200);
            ofCircle( vertices[nVertexSelected]->getTexCoord(), 5);
            ofLine( vertices[nVertexSelected]->getTexCoord(), mouse);
        }
        
        ofPopStyle();
    }
    
    _updateMesh();
    
    ofSetColor(255);
    image.bind();
    mesh.draw();
    image.unbind();
    
    if (bEdit){
        ofSetColor(255,50);
        mesh.drawWireframe();
    }
}

//--------------------------------------------------- EVENTS
void Body::_mousePressed(ofMouseEventArgs &e){
	if(bEdit){
        ofPoint mouse = ofPoint(e.x,e.y);
        
        //  If Nothing Selected
        //
        if ( nVertexSelected == -1 && nSpringSelected == -1){
            
            if ( nVertexHover != -1 ) {
                //  If click over a vertex
                //
                nVertexSelected = nVertexHover;
            } else if ( nSpringHover != -1) {
                //  If click over a spring
                //
                nSpringSelected = nSpringHover;
            } else {
                //  If click over nothing
                //
                addVertex(mouse);
            }
            
            if (e.button != 0) {
                bRightClick = true;
            }
        }
    }
}

void Body::_mouseDragged(ofMouseEventArgs &e){
    ofPoint mouse = ofPoint(e.x,e.y);
    
    if (bRightClick){
        
        if (nVertexSelected != -1){
            vertices[nVertexSelected]->setTexCoord(mouse);
            _updateSpringsConectedTo(nVertexSelected);
            _updateMesh();
        } else if ( nSpringSelected != -1){
            
            ofPoint a = springs[nSpringSelected].vertexA->getTexCoord();
            ofPoint b = springs[nSpringSelected].vertexB->getTexCoord();
            float   distance = springs[nSpringSelected].dist;
            
            ofPoint normalPoint = _getNormalPoint(mouse, a, b);
            
            springs[nSpringSelected].k = ofMap((normalPoint-a).length()/(b-a).length(),
                                               0.0,1.0,0.0,0.5);
            
        }
        
    }
}

void Body::_mouseReleased(ofMouseEventArgs &e){
    if (bEdit){
        ofPoint mouse = ofPoint(e.x,e.y);
        int index = getVertexIndexAt(mouse);
        
        if ( nVertexSelected != -1){
            if ( index == -1 ){
                addVertex(mouse);
                index = vertices.size()-1;
            }
            addSpring(nVertexSelected, index);
        }
        
        _calculateTriangles();
        _updateMesh();
        
        nVertexSelected = -1;
        nSpringSelected = -1;
        bRightClick = false;
    }
}
