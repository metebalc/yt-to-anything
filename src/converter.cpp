#include "converter.h"

#include <cstdio>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

Converter::Converter() = default;

std::string Converter::getWebsiteUrl() const
{
    return websiteUrl;
}

void Converter::setWebsiteUrl(const std::string& websiteUrl)
{
    this->websiteUrl = websiteUrl;
}

int Converter::runYtDlp(const std::vector<std::string>& extraArgs)
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

        std::vector<std::string> args;
        args.push_back(program);

        for (const auto& arg : extraArgs)
            args.push_back(arg);

        args.push_back(websiteUrl);

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

/* VIDEO FORMATS */

int Converter::convertToMp4()
{
    return runYtDlp({
        "-f",
        "bv*+ba/b",
        "--merge-output-format",
        "mp4",
        "-o",
        "../downloads/mp4/%(title)s.%(ext)s"
    });
}

int Converter::convertToWebm()
{
	return runYtDlp({
		"-f",
		"bv*+ba/b",
        "--merge-output-format",
        "webm",
        "-o",
        "../downloads/webm/%(title)s.%(ext)s"
	});
}

int Converter::convertToMov()
{
	return runYtDlp({
		"-f",
		"bv*+ba/b",
        "--merge-output-format",
        "mov",
        "-o",
        "../downloads/mov/%(title)s.%(ext)s"
	});
}

int Converter::convertToMkv()
{
	return runYtDlp({
		"-f",
		"bv*+ba/b",
        "--merge-output-format",
        "mkv",
        "-o",
        "../downloads/mkv/%(title)s.%(ext)s"
	});
}

/* AUDIO FORMATS */

int Converter::convertToMp3()
{
    return runYtDlp({
        "-x",
        "--audio-format",
        "mp3",
        "-o",
        "../downloads/mp3/%(title)s.%(ext)s"
    });
}

int Converter::convertToAac()
{
    return runYtDlp({
        "-x",
        "--audio-format",
        "aac",
        "-o",
        "../downloads/aac/%(title)s.%(ext)s"
    });
}

int Converter::convertToM4a()
{
    return runYtDlp({
        "-x",
        "--audio-format",
        "m4a",
        "-o",
        "../downloads/m4a/%(title)s.%(ext)s"
    });
}

int Converter::convertToWav()
{
	return runYtDlp({
	"-x",
	"--audio-format",
	"wav",
	"-o",
	"../downloads/wav/%(title)s.%(ext)s"
    });
}	

int Converter::convertToOgg()
{
	return runYtDlp({
	"-x",
	"--audio-format",
	"ogg",
	"-o",
	"../downloads/ogg/%(title)s.%(ext)s"
    });
}
