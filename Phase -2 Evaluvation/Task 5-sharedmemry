#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

class Vaccination {
private:
    string VaccinationId;
    int DoseAdministered;
public:
    Vaccination(string id, int dose) : VaccinationId(id), DoseAdministered(dose) {}

    int getDoseAdministered() const { return DoseAdministered; }
};

struct SharedMemory {
    int size;
    int doses[100];
    int sum;
};

void client(SharedMemory* shared_mem) {
    vector<Vaccination> vacc = {
        Vaccination("P001", 4), 
        Vaccination("P002", 5), 
        Vaccination("P003", 6), 
        Vaccination("P004", 15), 
        Vaccination("P005", 1)
    };

    shared_mem->size = vacc.size();
    for (int i = 0; i < shared_mem->size; ++i) {
        shared_mem->doses[i] = vacc[i].getDoseAdministered();
    }

    cout << "Client sending doses: ";
    for (int i = 0; i < shared_mem->size; ++i) {
        cout << shared_mem->doses[i] << " ";
    }
    cout << endl;
}

void server(SharedMemory* shared_mem) {
    int sum = 0;

    for (int i = 0; i < shared_mem->size; ++i) {
        sum += shared_mem->doses[i];
    }

    shared_mem->sum = sum;
    cout << "Server calculated sum: " << sum << endl;
}

int main() {
    key_t key = ftok("shmfile", 65);  // Create a unique key for shared memory
    int shmid = shmget(key, sizeof(SharedMemory), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory creation failed");
        return 1;
    }

    SharedMemory* shared_mem = (SharedMemory*) shmat(shmid, nullptr, 0);
    if (shared_mem == (SharedMemory*) -1) {
        perror("Shared memory attachment failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process (Client)
        client(shared_mem);
        shmdt(shared_mem);  // Detach from shared memory
        exit(0);
    } else {  // Parent process (Server)
        wait(nullptr);  // Wait for child process
        server(shared_mem);
        cout << "Server sent sum: " << shared_mem->sum << endl;
        shmdt(shared_mem);  // Detach from shared memory
        shmctl(shmid, IPC_RMID, nullptr);  // Remove shared memory
    }

    return 0;
}
