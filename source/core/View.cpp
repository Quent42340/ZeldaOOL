/*
 * =====================================================================================
 *
 *       Filename:  View.cpp
 *
 *    Description:
 *
 *        Created:  09/10/2014 14:17:30
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include "Shader.hpp"
#include "View.hpp"

View::View(float x, float y, u16 width, u16 height) {
	load(x, y, width, height);
}

void View::load(float x, float y, u16 width, u16 height) {
	reset(x, y, width, height);
}

void View::reset(float x, float y, u16 width, u16 height) {
	m_x = x;
	m_y = y;

	m_width = width;
	m_height = height;
}

void View::move(float offsetX, float offsetY) {
	m_x += offsetX;
	m_y += offsetY;

	if (Shader::currentShader)
		Shader::currentShader->setUniform("u_viewPosition", m_x, m_y);
}

void View::setPosition(float x, float y) {
	m_x = x;
	m_y = y;

	if (Shader::currentShader)
		Shader::currentShader->setUniform("u_viewPosition", m_x, m_y);
}

void View::bind(const View *view, const Shader *shader) {
	if (shader) {
		if (view) {
			shader->setUniform("u_viewPosition", view->m_x, view->m_y);
		} else {
			shader->setUniform("u_viewPosition", 0, 0);
		}
	}
}

