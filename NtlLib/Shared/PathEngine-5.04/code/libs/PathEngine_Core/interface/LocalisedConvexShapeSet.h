
//**********************************************************************
//
// Copyright (c) 2004
// PathEngine
// Lyon, France
//
// All Rights Reserved
//
//**********************************************************************

#ifndef LOCALISED_CONVEX_SHAPE_SET_INCLUDED
#define LOCALISED_CONVEX_SHAPE_SET_INCLUDED

#include "libs/Mesh2D/interface/tMesh_Iterators.h"
#include "libs/Geometry/interface/tLine_Header.h"
#include "libs/Geometry/interface/tIntersection_Header.h"
#include "libs/PathEngine_Core/interface/iCollisionTester.h"
#include "common/STL/vector.h"
#include "common/Containers/CollapsedVectorVector.h"

class cLocalisedConvexShape;
class cInternalPosition;
class cAxisFraction;

class cLocalisedConvexShape_ShapesInFaceIterator
{
public:

    long _faceIndex;
    long _indexInFace;
};

class cLocalisedConvexShapeSet : public iLineCollisionTester, public iPointCollisionTester
{
    long _facesInMesh;
    std::vector<const cLocalisedConvexShape*> _expansions;
//    std::vector<std::vector<size_t> > _expansionLookup;
    cCollapsedVectorVector<long> _expansionLookup;
    bool _setCompletedCalled;

public:

    cLocalisedConvexShapeSet(long facesInMesh);

// generation, regeneration and modifications

    void clear();
    void deleteAllAndClear();

    // ownership of the shape is not taken here
    void push_back(const cLocalisedConvexShape* shape);

    void setCompleted();

    void shrinkToFit();

// end user

    long size() const
    {
        return SizeL(_expansions);
    }
    bool empty() const
    {
        return _expansions.empty();
    }
    const cLocalisedConvexShape& operator[](long index) const
    {
        return *_expansions[index];
    }
    long shapesInFace(long faceIndex) const
    {
        return _expansionLookup.subVectorSize(faceIndex);
    }
    long indexForShapeInFace(long faceIndex, long indexInFace) const
    {
        return _expansionLookup[faceIndex][indexInFace];
    }
    const cLocalisedConvexShape& shapeInFace(long faceIndex, long indexInFace) const
    {
        return *_expansions[indexForShapeInFace(faceIndex, indexInFace)];
    }

    typedef cLocalisedConvexShape_ShapesInFaceIterator tShapesInFaceIterator;
    static void initShapesInFaceIterator(long faceIndex, tShapesInFaceIterator& it);
    bool nextShapeInFace(tShapesInFaceIterator& it, long& index, const cLocalisedConvexShape*& shapePtr) const;
    bool nextShapeInFace(tShapesInFaceIterator& it, const cLocalisedConvexShape*& shapePtr) const;

// interface for iPointCollisionTester

    bool testPointCollision(cQueryContext& qc, tFace f, const tPoint& p) const;

// interface for iLineCollisionTester

    bool testCollision(cQueryContext& qc, const cInternalPosition& from, const cInternalPosition& to) const;
    bool testCollisionToXY(cQueryContext& qc, tFace startF, const tLine& line) const;
    bool testCollisionToXY(cQueryContext& qc, tFace startF, const tLine& line, tFace& endF) const;
    bool testForSnagsToSegmentEnd(cQueryContext& qc, const tLine& segmentLine, const cInternalPosition& approximation) const;
};

#endif
