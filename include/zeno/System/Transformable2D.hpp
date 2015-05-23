#ifndef INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_2D_HPP
#define INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_2D_HPP

#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	zeno
///
////////////////////////////////////////////////////////////
namespace zeno {

////////////////////////////////////////////////////////////
///
///	\brief	Class that represents a 2D transformation
///
////////////////////////////////////////////////////////////
    class Transformable2D
    {
    public:
        ////////////////////////////////////////////////////////////
        ///
        ///	\brief		Default constructor
        ///
        ///	Initialises the internal transformation to the identity
        ///	matrix
        ///
        ////////////////////////////////////////////////////////////
        Transformable2D(void);


        ////////////////////////////////////////////////////////////
        ///
        ///	\brief		Resets the internal transformation to the
        ///				identity matrix
        ///
        ////////////////////////////////////////////////////////////
        void resetTransformation(void);


        ////////////////////////////////////////////////////////////
        ///
        ///	\brief		Gets a read only reference to the transform
        ///
        ///	\return		Mat4x4 read only reference
        ///
        ////////////////////////////////////////////////////////////
        const Mat4x4& getTransform(void) const;

        ////////////////////////////////////////////////////////////
        ///
        /// \brief      Gets a read/write reference to the transform
        ///
        /// \return     Mat4x4 read/write reference
        ///
        ////////////////////////////////////////////////////////////
        Mat4x4& getTransform(void);


        ////////////////////////////////////////////////////////////
        ///
        /// \brief      Increases the translation by the given offset
        ///
        /// \param      _offset Vector2
        ///
        ////////////////////////////////////////////////////////////
        void move(const Vector2f& _offset);
        ////////////////////////////////////////////////////////////
        ///
        /// \brief      Sets the translation to the given position
        ///
        /// \param      _position Vector2
        ///
        ////////////////////////////////////////////////////////////
        void setPosition(const Vector2f& _position);
        ////////////////////////////////////////////////////////////
        ///
        /// \brief      Gets the accumulated translation
        ///
        /// \return     Vector2 representing the translation
        ///
        ////////////////////////////////////////////////////////////
        Vector2f getPosition(void) const;

    private:
        Mat4x4				m_Transform;    ///<    Internal representation of the transformation

    };

} //~ namespace zeno

#endif //~ INCLUDED_ZENO_SYSTEM_TRANSFORMABLE_2D_HPP

////////////////////////////////////////////////////////////
///
///	\class zeno::Transformable2D
///	\ingroup System
///
///	Explanation of how this all works
///
///	\code
///	zeno::Transformable2D transform = zeno::Transformable2D();
///	\endcode
///
////////////////////////////////////////////////////////////