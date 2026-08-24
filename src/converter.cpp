#include "converter.h"

#include <cstdio>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

Converter::Converter() {};

std::string Converter::getWebsiteUrl()  const
{
	return websiteUrl;
}

void Converter::setWebsiteUrl(const std::string& websiteUrl)
{
	this->websiteUrl = websiteUrl;
}

int Converter::convertToMp4()
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return 1;
	}

	if (pid == 0)
	{
		const char* program = "/home/pax/.local/bin/yt-dlp";

		std::vector<std::string> args = {
			program,
			"-f",
			"bv*+ba/b",
			"--merge-output-format",
			"mp4",
			"-o",
			"%(title)s.%(ext)s",
			websiteUrl
		};

		std::vector<char*> argv;

		for (std::string& arg : args)
			argv.push_back(arg.data());

		argv.push_back(nullptr);

		execv(program, argv.data());

		perror("execv");
		_exit(1);
	}

	int status = 0;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return 1;
	}

	if (WIFEXITED(status))
		return WEXITSTATUS(status);

	return 1;
}

int Converter::convertToMp3()
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return 1;
	}

	if (pid == 0)
	{
		const char* program = "/home/pax/.local/bin/yt-dlp";

		std::vector<std::string> args = {
			program,
			"-t",
			"mp3",
			"-o",
			"%(title)s.%(ext)s",
			websiteUrl
		};

		std::vector<char*> argv;

		for (std::string& arg : args)
			argv.push_back(arg.data());

		argv.push_back(nullptr);

		execv(program, argv.data());

		perror("execv");
		_exit(1);
	}

	int status = 0;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return 1;
	}

	if (WIFEXITED(status))
		return WEXITSTATUS(status);

	return 1;
}
