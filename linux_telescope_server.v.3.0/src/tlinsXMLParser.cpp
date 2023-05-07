/*
 * tlins_xmlParser.cpp
 *
 *  Created on: 19-04-2012
 *      Author: jacek
 */

#include <tlinsBacktrace.hpp>
#include <tlinsXMLParser.hpp>

#include <iostream>
#include <stdio.h>

tlinsXMLParserException::tlinsXMLParserException(const char *errorMessage, int errorID)
    : tlinsException(errorMessage, errorID)
{
}

// Parsowanie pliku
void tlinsXMLParser::parseFile(void)
{
	parseFile(fileName);
}

void tlinsXMLParser::parseFile(string &file)
{
	// Otwarcie pliku wejsciowego
	FILE *fPtr = fopen(file.c_str(), "r");
	if (fPtr == nullptr) {
		throw tlinsXMLParserException("Error opening input file",
		                              tlinsXMLParserException::XML_PARSER_ERROR_OPENNING_INPUT_FILE);
	}

	// Czyszczenie bledu
	document->ClearError();

	// Parsowanie dokumentu
	if (!document->LoadFile(fPtr)) {
		fclose(fPtr);
		throw tlinsXMLParserException((char *) (document->ErrorDesc()),
		                              tlinsXMLParserException::XML_PARSER_ERROR_LOADING_XML_FILE);
	}
	fclose(fPtr);
}


// Parsowanie bufora wejsciowego
void tlinsXMLParser::parseBuffer(string &xmlText)
{
	// Czyszczenie bledu
	document->ClearError();

	// Parsowanie dokumentu
	document->Parse(xmlText.c_str());

	// Weryfikacja rezultatu operacji
	if (document->Error()) {
		throw tlinsXMLParserException((char *) (document->ErrorDesc()),
		                              tlinsXMLParserException::XML_PARSER_ERROR_PARSING_XML_BUFFER);
	}
}

// Pobranie sparsowanego dokumentu
TiXmlDocument *tlinsXMLParser::getDocument(void)
{
	return document;
}

string &tlinsXMLParser::getDocumentName(void)
{
	return documetName;
}

bool tlinsXMLParser::getIsFile(void) const
{
	return isFile;
}

// Konstruktor i destruktor klasy
tlinsXMLParser::tlinsXMLParser(const string &docName, const string &file, TiXmlEncoding enc)
{
	document = new TiXmlDocument(const_cast<const char *>(docName.c_str()));
	if (document == nullptr) {
		throw tlinsXMLParserException("Out of memory", tlinsException::ERROR_OUT_OFF_MEMORY);
	}

	documetName = docName;
	fileName    = file;
	encoding    = enc;
	isFile      = true;
}

tlinsXMLParser::tlinsXMLParser(const string &docName, TiXmlEncoding enc)
{
	document = new TiXmlDocument(const_cast<const char *>(docName.c_str()));
	if (document == nullptr) {
		throw tlinsXMLParserException("Out of memory", tlinsException::ERROR_OUT_OFF_MEMORY);
	}

	documetName = docName;
	encoding    = enc;
	isFile      = false;
}

tlinsXMLParser::~tlinsXMLParser(void)
{
	if (document != nullptr) {
		delete document;
	}
}
