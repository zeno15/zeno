#include <zeno/Graphics/Polygon.hpp>

namespace zeno {

    void Polygon::addPoint(const Vector2f& _point, bool _update /*= true*/)
    {
        m_Points.push_back(_point);

        if  (_update)
        {
            updateInternalPositions();
        }
    }
    void Polygon::addPoints(const std::vector<Vector2f>& _points)
    {
        for (const Vector2f& vec : _points)
        {
            addPoint(vec, false);
        }

        updateInternalPositions();
    }

} //~ namespace zeno