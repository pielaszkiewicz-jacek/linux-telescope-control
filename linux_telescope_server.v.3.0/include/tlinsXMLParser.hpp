#ifndef _tlins_xmlParser_hpp_
#define _tlins_xmlParser_hpp_

#include <tlinsBacktrace.hpp>
#include <tlinsException.hpp>
#include <tlinsLogger.hpp>
#include <tlinsParametersList.hpp>

#include <tinystr.h>
#include <tinyxml.h>

#include <iostream>
#include <list>
#include <string>

/*
 * -------------------------------------------------------------
 *
 * Definicja wyjatkow zglaszanych przez klase parsera XML
 *
 * -------------------------------------------------------------
 */
class tlinsXMLParserException : public tlinsException {
  public:
	static const int XML_PARSER_ERROR_PARSING_XML_BUFFER  = -50000;
	static const int XML_PARSER_ERROR_PARSING_XML_FILE    = -50001;
	static const int XML_PARSER_ERROR_LOADING_XML_FILE    = -50002;
	static const int XML_PARSER_ERROR_OPENNING_INPUT_FILE = -50004;

  public:
	tlinsXMLParserException(const char *errorMessage, int errorID);
};

/*
 * -------------------------------------------------------------
 *
 * Klasa parsera XML
 *
 * -------------------------------------------------------------
 */
class tlinsXMLParser {
  private:
	// Enkoding
	TiXmlEncoding encoding;

	// XML document
	TiXmlDocument *document;

	// Nazwa dokumentu
	std::string documetName;

	// Nazwa pliku
	std::string fileName;

	bool isFile;

  public:
	static void parsParameters(TiXmlElement *element, tlinsParametersList &parameters)
	{
		list<TiXmlElement *> ele;
		tlinsXMLParser::getChildNodes(element, ele);

		for (auto iter = ele.begin(); iter != ele.end(); iter++) {
			// Czyszczenie listy
			list<TiXmlAttribute *> attributes;

			// Pobranie atrybutow
			tlinsXMLParser::getChildNodes(*iter, attributes);

			if (attributes.size() == 0)
				continue;

			for (auto iterA = attributes.begin(); iterA != attributes.end(); iterA++) {
				if (strcmp((*iterA)->Name(), "name") == 0) {
					// Nazwa parameteru
					std::string paraName = (*iterA)->Value();
					std::string paraValue{};

					if ((*iter)->FirstChild() != nullptr && (*iter)->FirstChild()->Type() == TiXmlNode::TINYXML_TEXT) {
						paraValue = (*iter)->FirstChild()->Value();
					}
					parameters.setParameter(paraName, paraValue, false);
				}
			}
		}
	}


	static bool readAttribueValue(TiXmlElement *element, const std::string &name, std::string &value)
	{
		list<TiXmlAttribute *> attributes;

		// Pobranie atrybutow
		tlinsXMLParser::getChildNodes(element, attributes);

		if (attributes.size() == 0) {
			return false;
		}

		for (auto iterA = attributes.begin(); iterA != attributes.end(); iterA++) {
			if (name.compare((*iterA)->Name()) == 0) {
				value = (*iterA)->Value();
				return true;
			}
		}
		return false;
	}

	// Metoda zwraca wskazany wezel na podstawie przekazanej sciezki
	static TiXmlElement *getNode(TiXmlElement *ele, list<std::string> &lst)
	{
		// Gdy list apusta nic nie robie
		if (lst.size() == 0)
			return nullptr;

		// Przejscie po liscie
		list<std::string>::iterator iter = lst.begin();

		TiXmlElement *element = ele->FirstChildElement(const_cast<const char *>(iter->c_str()));
		++iter;

		for (; iter != lst.end() && element != nullptr; ++iter) {
			cout << iter->c_str() << endl;
			element = element->FirstChildElement(const_cast<const char *>(iter->c_str()));
		}

		return element;
	}


	// Metoda zwraca wskazany wezel na podstawie przekazanej sciezki
	static TiXmlElement *getNode(TiXmlDocument *document, list<std::string> &lst)
	{
		// Gdy list apusta nic nie robie
		if (lst.size() == 0)
			return nullptr;

		// Przejscie po liscie
		list<std::string>::iterator iter = lst.begin();

		TiXmlElement *element = document->FirstChildElement(const_cast<const char *>(iter->c_str()));
		++iter;

		for (; iter != lst.end() && element != nullptr; ++iter) {
			cout << iter->c_str() << endl;
			element = element->FirstChildElement(const_cast<const char *>(iter->c_str()));
		}

		return element;
	}

	// Pobranie nodow dzieci
	static void getChildNodes(TiXmlElement *el, list<TiXmlElement *> &result)
	{
		for (TiXmlElement *fc = el->FirstChildElement(); fc != nullptr; fc = fc->NextSiblingElement())
			result.push_back(fc);
	};

	// Pobranie listy wszystkich atrybutow dla biezacego wezla
	static void getChildNodes(TiXmlElement *el, list<TiXmlAttribute *> &result)
	{
		for (TiXmlAttribute *attr = el->FirstAttribute(); attr != nullptr; attr = attr->Next())
			result.push_back(attr);
	}

	// Pobranie wartosci atrybutu
	static const char *getValue(TiXmlElement *el, std::string &name)
	{
		TiXmlElement *ce = el->FirstChildElement(name.c_str());

		// Nie ma elementu podrzednego
		if (ce == nullptr)
			return nullptr;

		if (ce->Type() != TiXmlNode::TINYXML_TEXT)
			return nullptr;

		return ce->Value();
	}

	// Pobranie wartosci atrybutu
	static const char *getValue(TiXmlElement *el)
	{
		TiXmlElement *ce = el->FirstChildElement();

		// Nie ma elementu podrzednego
		if (ce == nullptr)
			return nullptr;

		if (ce->Type() != TiXmlNode::TINYXML_TEXT)
			return nullptr;

		return ce->Value();
	}

  public:
	// Parsowanie bufora wejsciowego
	void parseBuffer(std::string &xmlText);

	// Parsowanie pliku
	void parseFile(void);
	void parseFile(std::string &file);

	// Pobranie znacznika czy parser jest plikiem
	bool getIsFile(void) const;

	// Pobranie sparsowanego dokumentu
	TiXmlDocument *getDocument(void);

	std::string &getDocumentName(void);

	// Konstruktor i destruktor klasy
	tlinsXMLParser(const std::string &docName, const std::string &inputFile,
	               TiXmlEncoding enc = TIXML_DEFAULT_ENCODING);
	tlinsXMLParser(const std::string &docName, TiXmlEncoding enc = TIXML_DEFAULT_ENCODING);
	~tlinsXMLParser(void);
};

#endif
