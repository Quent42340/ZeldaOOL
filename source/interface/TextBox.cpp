/*
 * =====================================================================================
 *
 *       Filename:  TextBox.cpp
 *
 *    Description:
 *
 *        Created:  23/02/2015 17:15:03
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include <functional>

#include "AudioPlayer.hpp"
#include "Exception.hpp"
#include "TextBox.hpp"

TextBox::TextBox(const std::string &text) {
	m_charTimer.start();

	setText(text);
}

void TextBox::setSize(u16 width, u16 height) {
	m_width = width;
	m_height = height;
}

void TextBox::draw(RenderTarget &target, RenderStates states) const {
	// FIXME
	// u16 charX = getPosition().x + 8;
	// u16 charY = getPosition().y;
    //
	// m_charPerLine = (m_width - 16) / m_text.charWidth();
    //
	// m_charsToDisplay = m_charPerLine * 2;
    //
	// m_currentColor = Color::text;
    //
	// for(u16 i = 0 ; i < m_string.length() ; i++) {
	// 	// Change color if a color tag is found
	// 	if(m_colorChanges.find(i) != m_colorChanges.end()) {
	// 		m_currentColor = m_colorChanges[i];
	// 	}
    //
	// 	// If the text is out of the box, don't display it
	// 	if(i < m_page * m_charPerLine) continue;
    //
	// 	// If the text is out of the box, don't display it
	// 	if(charY + m_text.charHeight() > y + height) {
	// 		break;
	// 	}
    //
	// 	// Letter by letter text display
	// 	if(isTimeToDisplayLetter(i)) {
	// 		AudioPlayer::repeatEffect("textLetter", m_delay);
	// 		break;
	// 	}
    //
	// 	// Jump to next line if a newline character is encountered
	// 	if(m_string[i] == '\n') {
	// 		m_charsToDisplay -= m_charPerLine - (charX - x - 8) / m_text.charWidth();
    //
	// 		charX = x + 8;
	// 		charY += m_text.charHeight();
    //
	// 		continue;
	// 	}
    //
	// 	if(m_string[i] == ' ') {
	// 		// If a space is the first character of a line, don't display it
	// 		if(charX == x + 8) continue;
    //
	// 		size_t nextSpace = m_string.find_first_of(' ', i + 1);
    //
	// 		u8 wordLength = ((nextSpace != std::string::npos) ? nextSpace : m_string.length()) - i - 1;
    //
	// 		// Check if the word is out of the box, if it is, jump to next line
	// 		if(charX + wordLength * m_text.charWidth() > x + width - 16) {
	// 			m_charsToDisplay -= m_charPerLine - (charX - x - 8) / m_text.charWidth();
    //
	// 			charX = x + 8;
	// 			charY += m_text.charHeight();
    //
	// 			continue;
	// 		}
	// 	}
    //
	// 	m_text.drawChar(charX, charY, m_string[i], m_currentColor);
    //
	// 	charX += m_text.charWidth();
	// }
}

void TextBox::setText(const std::string &text) {
	m_string = text;

	// Fix problems with accents
	m_string.erase(std::remove_if(m_string.begin(), m_string.end(), std::bind(std::equal_to<u8>(), 195, std::placeholders::_1)), m_string.end());

	// Search for color tags in the form '[0..9]', for example: '[2]'
	// and add their informations to m_colorChanges
	size_t nextColorTag = m_string.find_first_of('[');
	while(nextColorTag != std::string::npos) {
		Color color;

		// Find the color
		switch(m_string[nextColorTag + 1]) {
			case '0': color = Color::text; break;
			case '1': color = Color::blue; break;
			case '2': color = Color::red;  break;
			default: throw EXCEPTION("MessageBox parsing error at string index", std::to_string(nextColorTag + 1) + ":", "Unrecognized color tag");
		}

		// Make sure that the tag is complete
		if(m_string[nextColorTag + 2] != ']') {
			throw EXCEPTION("MessageBox parsing error at string index", std::to_string(nextColorTag + 2) + ":", "Missing ']'");
		}

		m_colorChanges[nextColorTag] = color;

		// Delete the tag from the string
		m_string.erase(nextColorTag, 3);

		nextColorTag = m_string.find_first_of('[', nextColorTag);
	}
}


bool TextBox::scrollDown() {
	// Don't animate again the first line's drawing
	m_charTimer.setTime(m_charsToDisplay * m_delay);

	if(!isAtLastPage()) {
		m_page++;
		return false;
	} else {
		return true;
	}
}

void TextBox::stopTextAnimation() {
	m_charTimer.setTime((m_charsToDisplay + m_page * m_charPerLine) * m_delay);
}

bool TextBox::isAtLastPage() const {
	return m_string.length() / m_charPerLine <= m_page + 1u;
}

bool TextBox::textDisplayFinished() const {
	return m_charTimer.time() / m_delay > u16(m_charsToDisplay + m_page * m_charPerLine);
}

bool TextBox::isTimeToDisplayLetter(u16 letterIndex) const {
	return m_charTimer.time() / m_delay < letterIndex;
}

