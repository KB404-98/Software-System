#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/socket.h>

/*---------------------------VIEW ALL COURSES-----------------------------------------------------------------------------------------------------------------------------------------------------*/


int viewAllCourses(int clientSocket) {
    int fd;
    struct course cr;

    // Open the file for reading using system call
    fd = open("course.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Create a dynamic buffer to store course details
    char buffer[4096];  // Adjust the size as needed

    // Initialize the buffer
    memset(buffer, 0, sizeof(buffer));

    // Capture the course details in the buffer
    ssize_t bytes_read;
    while ((bytes_read = read(fd, &cr, sizeof(struct course)) > 0)) {
        char course_str[512];  // Adjust the size as needed for a single course
        snprintf(course_str, sizeof(course_str), "Course ID: %s\n"
                                                "Professor ID: %s\n"
                                                "Course Name: %s\n"
                                                "Department: %s\n"
                                                "Credit: %s\n"
                                                "Total Seats: %s\n"
                                                "Available Seats: %s\n\n",
                 cr.course_id, cr.prof_id, cr.course_name,
                 cr.dept, cr.course_credit, cr.total_seats, cr.avail_seats);
        strcat(buffer, course_str);
    }
    // Close the file using system call
    close(fd);

    // Now, 'buffer' contains all course details as a single string
   send(clientSocket, buffer, strlen(buffer), 0);

    return 0;
}


/*-----------------------------ENROLL A NEW COURSE----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void enroll(int clientSocket) {
    struct course course_record;

    // Open the courses.txt file for reading and writing
    int fd = open("course.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return;
    }
    char courseID[10];

    send(clientSocket, "Enter the Course ID\n", strlen("Enter the Course ID\n"), 0);
    int bytesRead = recv(clientSocket, courseID, sizeof(courseID) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Login Id");
        return ;
    }
    courseID[bytesRead] = '\0';
    int found = 0;

    // Apply mandatory file lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return;
    }

    // Search for the course with the matching ID
    while (read(fd, &course_record, sizeof(struct course)) > 0) {
        if (strcmp(courseID, course_record.course_id) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        // Check if there are available seats
        int avail_seats = atoi(course_record.avail_seats);
        if (avail_seats > 0) {
            // Enroll the student (decrement available seats)
            avail_seats--;
            snprintf(course_record.avail_seats, sizeof(course_record.avail_seats), "%d", avail_seats);

            // Seek back to the beginning of the course record
            lseek(fd, -sizeof(struct course), SEEK_CUR);

            // Write the updated course data back to the file
            if (write(fd, &course_record, sizeof(struct course)) == -1) {
                perror("Error writing to the file");
            } else {
                send(clientSocket, "Enrollment successful\n", strlen("Enrollment successful\n"), 0);
            }
        } else {
            send(clientSocket, "No available seats for this course\n", strlen("No available seats for this course\n"), 0);
        }
    } else {
        send(clientSocket, "Course not found\n", strlen("Course not found\n"), 0);
    }

    flock(fd, LOCK_UN);
    // Close the file
    close(fd);
}




/*-------------------------DROP A COURSE----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void drop(int clientSocket) {
    struct course course_record;

    // Open the courses.txt file for reading and writing
    int fd = open("course.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening the file");
        return;
    }
    char courseID[10];

    send(clientSocket, "Enter the Course ID\n", strlen("Enter the Course ID\n"), 0);
    int bytesRead = recv(clientSocket, courseID, sizeof(courseID) - 1, 0);
    if (bytesRead <= 0) {
        perror("Error while receiving Login Id");
        return ;
    }
    courseID[bytesRead] = '\0';
    int found = 0;

    // Apply mandatory file lock
    if (flock(fd, LOCK_EX) == -1) {
        perror("Error applying lock");
        close(fd);
        return;
    }

    // Search for the course with the matching ID
    while (read(fd, &course_record, sizeof(struct course)) > 0) {
        if (strcmp(courseID, course_record.course_id) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
         // Increment available seats
        int total_seats = atoi(course_record.total_seats);
        int avail_seats = atoi(course_record.avail_seats);

        if (avail_seats < total_seats) {
            avail_seats++;
            snprintf(course_record.avail_seats, sizeof(course_record.avail_seats), "%d", avail_seats);

            // Seek back to the beginning of the course record
            lseek(fd, -sizeof(struct course), SEEK_CUR);

            // Write the updated course record back to the file
            if (write(fd, &course_record, sizeof(struct course)) == -1) {
                perror("Error writing to the file");
            }else {
                // Send a "drop successful" message
                send(clientSocket, "Course dropped successfully. Available seats updated.\n", strlen("Course dropped successfully. Available seats updated.\n"), 0);
            }
        } else {
            send(clientSocket, "No more available seats for this course.\n", strlen("No more available seats for this course.\n"), 0);
        }
    } else {
        send(clientSocket, "Course not found.\n", strlen("Course not found.\n"), 0);
    }

    // Release the lock before closing the file
    flock(fd, LOCK_UN);

    // Close the file
    close(fd);
}










/*---------------------------STUDENT AUTHENTICATION-----------------------------------------------------------------------------------------------------------------------------------*/


int student_Authentication(int client_socket) {
    char loginId[100];
    char pass[100];

    // Send a prompt for the username
    const char *uname_msg = "\nEnter StudentID of Student: ";
    send(client_socket, uname_msg, strlen(uname_msg), 0);

    // Receive the username from the client
    ssize_t bytesRead = recv(client_socket, loginId, sizeof(loginId), 0);
    if (bytesRead <= 0) {
        close(client_socket);
        return false;
    }
    if (loginId[bytesRead - 1] == '\n') {
        loginId[bytesRead - 1] = '\0';
    } else {
        loginId[bytesRead] = '\0';
    }

    // Send a prompt for the password
    const char *pswd_msg = "\nEnter password of the Student: ";
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

    struct student s;

    int fd = open("student.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return false;
    }
    int found = 0;

     while (read(fd, &s, sizeof(struct student)) > 0) {
        if (strcmp(loginId, s.stud_id) == 0) {
            if(strcmp(pass,s.password ) ==0){
            
                found = 1;
                break;
            }
        }
    }

    if(found){
        
        send(client_socket, "Authentication successful\n", strlen("Authentication successful\n"), 0);
        close(fd);
        return true;
    }else{
        
        send(client_socket, "Authentication failed. Exiting.\n", strlen("Authentication failed. Exiting.\n"), 0);
        close(fd);
        close(client_socket);
        return false;

    }

    
}

/*-----------------------------STUDENT FUNCTIONALITY-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int student_Fun(int client_socket) {
    // You can implement admin-specific functionality here
    // This function will be called after successful admin authentication
    // Add your code to handle admin tasks, menu options, etc.
    // For example, sending admin menu options and processing admin tasks

    char student_Menu[] = "\nStudent Menu:\n1. View All Courses\n2. Enroll New Course\n3. Drop Course\n4. View Enrolled Course Details\n5. Change Password\n6. Exit\nEnter Choice\n";

    while (1) {
        send(client_socket, student_Menu, strlen(student_Menu), 0);
        char choice_buffer[10];
        ssize_t bytesRead = recv(client_socket, choice_buffer, sizeof(choice_buffer), 0);

        if (bytesRead <= 0) {
            perror("Error receiving admin menu choice");
            close(client_socket);
            return false;
        }

        int choice = atoi(choice_buffer);

        // Handle Faculty menu options
        switch (choice) {
            case 1:
                 // View all Courses
                viewAllCourses(client_socket);
                
                break;
        
            case 2:
                //Enroll New Course
                enroll(client_socket); 
                break;

            case 3:
                //Drop Course
                drop(client_socket);

                break;

            case 4:
                //View Enrolled Course Details
                //updatePass(client_socket);

                break;
            case 5:
                //Change Password
                break;
            case 6:
                // Exit admin functionality
                return true;

            default:
                // Handle invalid options
                send(client_socket, "Invalid choice. Try again.\n", strlen("Invalid choice. Try again.\n"), 0);
                break;
        }
    }
    
}


