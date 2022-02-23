#include "KCollsion.h"

bool KCollsion::RectToPoint(KRect rt, int x, int y)
{
    return false;
}

bool KCollsion::RectToPoint(KRect rt, KVector2 v)
{
    return false;
}

KCollisionResult KCollsion::RectToRect(KRect, KRect)
{
    return KCollisionResult();
}

KCollisionResult KCollsion::ToRect(KRect rt1, KRect rt2)
{
    return KCollisionResult();
}

KRect KCollsion::UnionRect(KRect rt1, KRect rt2)
{
    return KRect();
}

bool KCollsion::IntersectRect(KRect rt1, KRect rt2, KRect* rt)
{
    return false;
}

bool KCollsion::BoxToPoint(KBox rt, int x, int y, int z)
{
    return false;
}

bool KCollsion::BoxToPoint(KBox rt, KVector3 v)
{
    return false;
}

KCollisionResult KCollsion::BoxToBox(KBox, KBox)
{
    return KCollisionResult();
}

KBox KCollsion::UnionBox(KBox rt1, KBox rt2)
{
    return KBox();
}

bool KCollsion::IntersectBox(KBox rt1, KBox rt2, KBox* rt)
{
    return false;
}
