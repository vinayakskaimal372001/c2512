#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>

#define SHM_KEY 1234

class Vaccination {
public:
    std::string VaccinationId;
    int DoseAdministered;

    Vaccination(std::string id, int dose) : VaccinationId(id), DoseAdministered(dose) {}

    std::string getVaccinationId() const { return VaccinationId; }
    int getDoseAdministered() const { return DoseAdministered; }
};

struct SharedMemory {
    int doses[5];
    int sum;
    bool dataReady;       
    bool serverDone;      
};

void client(int& shmid) { 
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);

   
    std::vector<Vaccination> vacc = {
        Vaccination("P001", 4),
        Vaccination("P002", 5),
        Vaccination("P003", 6),
        Vaccination("P004", 15),
        Vaccination("P005", 1)
    };

    
    for (int i = 0; i < 5; ++i) {
        sharedMem->doses[i] = vacc[i].getDoseAdministered();
    }

    std::cout << "Client sent doses: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->doses[i] << " ";
    }
    std::cout << std::endl;

    
    sharedMem->dataReady = true;

    
    while (!sharedMem->serverDone) {
        sleep(1);  
    }

  
    std::cout << "Client received sum from server: " << sharedMem->sum << std::endl;

    shmdt(sharedMem);
}

void server(int& shmid) { 
    SharedMemory* sharedMem = (SharedMemory*)shmat(shmid, nullptr, 0);


    while (!sharedMem->dataReady) {
        sleep(1);  
    }

    
    std::cout << "Server received doses: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << sharedMem->doses[i] << " ";
    }
    std::cout << std::endl;

   
    sharedMem->sum = 0;
    for (int i = 0; i < 5; ++i) {
        sharedMem->sum += sharedMem->doses[i];
    }

    std::cout << "Server calculated sum: " << sharedMem->sum << std::endl;

   
    sharedMem->serverDone = true;

    shmdt(sharedMem);
}

int main() {
 
    int shmid = shmget(SHM_KEY, sizeof(SharedMemory), 0666 | IPC_CREAT);

    if (shmid == -1) {
        std::cerr << "Shared memory allocation failed!" << std::endl;
        return 1;
    }

    {
    pid_t pid = fork();
        if (pid == 0) {
            server(shmid);
            shmctl(shmid, IPC_RMID, nullptr);  
            return 0;
        }
    }

   
    sleep(1);
    {
        int pid = fork();
        if (pid == 0) {
            
            client(shmid);
            return 0;
        }
    }

    
    wait(nullptr);
    wait(nullptr);

    return 0;
}
