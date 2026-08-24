#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

class Converter
{
public:
	Converter();
	
	std::string getWebsiteUrl() const;
	void setWebsiteUrl(const std::string& websiteUrl);
	
	int convertToMp4();
	int convertToMp3();
	
private:
	std::string websiteUrl;
};

#endif
