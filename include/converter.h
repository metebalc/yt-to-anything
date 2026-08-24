#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <vector>

class Converter
{
public:
	Converter();
	
	std::string getWebsiteUrl() const;
	void setWebsiteUrl(const std::string& websiteUrl);
	
	int convertToMp4();
	int convertToMov();
	int convertToWebm();
	int convertToMkv();
	
	int convertToMp3();
	int convertToAac();
	int convertToM4a();
	int convertToWav();
	int convertToOgg();
	
	// TODO for future
	int convert(const std::string& format);
	
private:
	std::string websiteUrl;
	int runYtDlp(const std::vector<std::string>& extraArgs);
};

#endif
