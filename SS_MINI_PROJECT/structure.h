struct UserCred
{
    char username[100];
    char pass[100];
};
struct UserCred adminCred = {"Kuldip", "2357"};

struct student
{
	char stud_id[11];
    char password[10];
	char dept[10];
	char name[30];
    char age[3];
    char email[25];
};

struct faculty
{
    char login_id[11];
    char password[10];
	char dept[10];
	char name[30];
    char age[3];
    char email[25]; 


};

struct course
{
    char course_id[10];
    char prof_id[10];
    char course_name[20];
    char dept[10];
    char course_credit[5];
    char total_seats[6];
    char avail_seats[6];
    
};