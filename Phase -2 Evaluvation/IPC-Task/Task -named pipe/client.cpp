#include <sys/types.h> 
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>

using namespace std;

class labTest {
private:
    string labTestId;
    int result;

public:
    labTest(string labTestId, int result) : labTestId(labTestId), result(result) {}

    int getresult() {
        return result;
    }
};

int main() {
    vector<labTest> tests;
    tests.emplace_back("LT001", 78);
    tests.emplace_back("LT002", 85);
    tests.emplace_back("LT003", 92);
    tests.emplace_back("LT004", 88);
    tests.emplace_back("LT005", 79);

    int results[tests.size()] = {0};

    for (int i = 0; i < tests.size(); i++) {
        results[i] = tests[i].getresult();
    }

    int numOfElements = tests.size();

    const char* pipe1 = "pipe1";
    const char* pipe2 = "pipe2";
    int pipe_two_read_fd, pipe_one_write_fd;
    pipe_one_write_fd = open(pipe1, O_WRONLY);
    pipe_two_read_fd = open(pipe2, O_RDONLY);

    if (pipe_one_write_fd == -1) {
        perror("pipe1 open failure at client");
        return 1;
    }
    if (pipe_two_read_fd == -1) {
        perror("pipe2 open failure at client");
        return 1;
    }

    write(pipe_one_write_fd, &numOfElements, sizeof(int));
    cout << "Client sent number of elements: " << numOfElements << endl;

    write(pipe_one_write_fd, results, sizeof(results));
    cout << "Client sent test results: ";
    for (int result : results) {
        cout << result << "\t";
    }
    cout << endl;
    close(pipe_one_write_fd);

    sleep(1);

    int sum;
    read(pipe_two_read_fd, &sum, sizeof(int));
    cout << "Sum received from server: " << sum << endl;

    close(pipe_two_read_fd);

    return 0;
}
