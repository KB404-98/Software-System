#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include "structure.h"


int addStudent(int clientSocket) {
    struct student s;

    // Prompt and receive the Login Id
    send(clientSocket, "Enter the Login Id of the student you want to add\n", strlen("Enter the Login Id of the student you want to add\n"), 0);
    int bytesRead = recv(clientSocket, s.login_id, sizeof(s.login_id) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Login Id");
        return false;
    }
    s.login_id[bytesRead] = '\0';

    // Set the Password to "1234"
    strcpy(s.password, "1234");

    // Prompt and receive the Department
    send(clientSocket, "Enter the Department of the student you want to add\n", strlen("Enter the Department of the student you want to add\n"), 0);
    bytesRead = recv(clientSocket, s.dept, sizeof(s.dept) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Department");
        return false;
    }
    s.dept[bytesRead] = '\0';

    // Prompt and receive the Name
    send(clientSocket, "Enter the Name of the student you want to add\n", strlen("Enter the Name of the student you want to add\n"), 0);
    bytesRead = recv(clientSocket, s.name, sizeof(s.name) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Name");
        return false;
    }
    s.name[bytesRead] = '\0';

    // Prompt and receive the Age
    send(clientSocket, "Enter the Age of the student you want to add\n", strlen("Enter the Age of the student you want to add\n"), 0);
    bytesRead = recv(clientSocket, s.age, sizeof(s.age) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Age");
        return false;
    }
    s.age[bytesRead] = '\0';

    // Prompt and receive the Email
    send(clientSocket, "Enter the Email of the student you want to add\n", strlen("Enter the Email of the student you want to add\n"), 0);
    bytesRead = recv(clientSocket, s.email, sizeof(s.email) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Email");
        return false;
    }
    s.email[bytesRead] = '\0';

    // Open the file to enter this data in the database
    int fd = open("student.txt", O_WRONLY | O_APPEND | O_CREAT, 0666); // Open the file in append mode

    if (fd == -1) {
        perror("Error opening the file");
        return false;
    }

    // Use flock to apply a mandatory lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return false;
    }

    // Write the structure data to the file
    if (write(fd, &s, sizeof(struct student)) == -1) {
        perror("Error writing to the file");
        flock(fd, LOCK_UN); // Release the lock before closing the file
        close(fd);
        send(clientSocket, "Failed to add Student\n", strlen("Failed to add Student\n"), 0);

    }else{

        flock(fd, LOCK_UN); // Release the lock
        close(fd);          // Close the file
        send(clientSocket, "Student adeed successfully\n", strlen("Student adeed successfully\n"), 0);

    }
    
}



int viewStudentDetails(int clientSocket) {

    char buff[1024];
    int fd = open("student.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return false;
    }
    int found = 0;
    char loginID[10];

    struct student s;

    memset(loginID,0,sizeof(loginID));
    
    send(clientSocket, "Enter the Login Id of the student you want to display\n", strlen("Enter the Login Id of the student you want to display\n"), 0);
    int bytesRead = recv(clientSocket, loginID, sizeof(loginID) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Login Id");
        return false;
    }
    loginID[bytesRead] = '\0';



    
    // Search for the student with the matching login ID
    while (read(fd, &s, sizeof(struct student)) > 0) {
        if (strcmp(loginID, s.login_id) == 0) {
            // Print student details when found
            found = 1;
            break;
        }
    }
    memset(buff,0,sizeof(buff));

    if(found){
        // construct detailed message
        sprintf(buff,"\n--Required Details of student--\nLogin ID:%s\nName:%s\nDept:%s\nAge:%s\nEmail:%s\n",s.login_id,s.name,s.dept,s.age,s.email);
        send(clientSocket, buff, strlen(buff),0);
        close(fd);
        
    }else{

        send(clientSocket, "Student not found..\n", strlen("Student not found..\n"), 0);
        close(fd);
        
    }
     
}




int admin_Authentication(int client_socket) {
    char username[100];
    char pass[100];

    // Send a prompt for the username
    const char *uname_msg = "\nEnter Username of Admin: ";
    send(client_socket, uname_msg, strlen(uname_msg), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(client_socket, username, sizeof(username), 0);
    if (bytesRead <= 0) {
        close(client_socket);
        return false;
    }
    if (username[bytesRead - 1] == '\n') {
        username[bytesRead - 1] = '\0';
    } else {
        username[bytesRead] = '\0';
    }

    // Send a prompt for the password
    const char *pswd_msg = "\nEnter password of the Admin: ";
    send(client_socket, pswd_msg, strlen(pswd_msg), 0);

    // Receive the password from the client
    bytesRead = recv(client_socket, pass, sizeof(pass), 0);
    if (bytesRead <= 0) {
        close(client_socket);
        return false;
    }
    if (pass[bytesRead - 1] == '\n') {
        pass[bytesRead - 1] = '\0';
    } else {
        pass[bytesRead] = '\0';
    }

    // Compare the received username and password with stored credentials
    if (strcmp(username, adminCred.username) == 0 && strcmp(pass, adminCred.pass) == 0) {
        // Authentication successful
        send(client_socket, "Authentication successful\n", strlen("Authentication successful\n"), 0);
        return true;
    } else {
        // Authentication failed
        send(client_socket, "Authentication failed. Exiting.\n", strlen("Authentication failed. Exiting.\n"), 0);
        close(client_socket);
        return false;
    }
}

int admin_Fun(int client_socket) {
    // You can implement admin-specific functionality here
    // This function will be called after successful admin authentication
    // Add your code to handle admin tasks, menu options, etc.
    // For example, sending admin menu options and processing admin tasks

    char admin_Menu[] = "\nAdmin Menu:\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Update Student Details\n8. Update Faculty Details\n9. Exit\nEnter Choice\n";

    while (1) {
        send(client_socket, admin_Menu, strlen(admin_Menu), 0);
        char choice_buffer[10];
        ssize_t bytesRead = recv(client_socket, choice_buffer, sizeof(choice_buffer), 0);

        if (bytesRead <= 0) {
            perror("Error receiving admin menu choice");
            close(client_socket);
            return false;
        }

        int choice = atoi(choice_buffer);

        // Handle admin menu options
        switch (choice) {
            case 1:
                // Add Student
                addStudent(client_socket); 
                break;

            case 2:
                // View student details
                viewStudentDetails(client_socket);

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:

                break;

            case 7:

                break;

            case 8:

                break;

            case 9:
                // Exit admin functionality
                return true;

            default:
                // Handle invalid options
                send(client_socket, "Invalid choice. Try again.\n", strlen("Invalid choice. Try again.\n"), 0);
                break;
        }
    }
    return false;
}
