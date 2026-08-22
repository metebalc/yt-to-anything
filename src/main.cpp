#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int runYtDlp(const std::string& url)
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
            url
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

int main()
{
    std::string websiteUrl;

    std::cout << "Enter URL: ";
    std::getline(std::cin, websiteUrl);

    int result = runYtDlp(websiteUrl);

    if (result != 0)
    {
        std::cerr << "yt-dlp failed with exit code " << result << '\n';
        return 1;
    }

    std::cout << "Download complete.\n";
    return 0;
}
