#ifndef INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP
#define INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP

#include <zeno/Graphics/Shape.hpp>

namespace zeno {

    class Circle : public Shape
    {
    public:
        Circle(float _radius, unsigned int _points = 30);

        void setRadius(float _radius);
        void setPoints(unsigned int _points);

    private:
        void regeneratePoints(void);

    private:
        unsigned int m_CirclePoints;

        float m_Radius;
    };

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_GRAPHICS_CIRCLE_HPP