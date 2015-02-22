/*
 * =====================================================================================
 *
 *       Filename:  VertexBuffer.hpp
 *
 *    Description:  
 *
 *        Created:  08/02/2015 22:59:15
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#ifndef VERTEXBUFFER_HPP_
#define VERTEXBUFFER_HPP_

#include "OpenGL.hpp"

class VertexBuffer {
	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer &) = delete;
		VertexBuffer(VertexBuffer &&vertexBuffer);
		~VertexBuffer();
		
		void setData(GLsizeiptr size, const GLvoid *data, GLenum usage);
		void updateData(GLintptr offset, GLsizeiptr size, const GLvoid *data);
		
		static void bind(const VertexBuffer *vertexBuffer);
		
		GLuint id() const { return m_id; }
		
	private:
		GLuint m_id = 0;
};

#endif // VERTEXBUFFER_HPP_
