#include <iostream>
#include <stdlib.h>
using namespace std;

struct student
{
    int id;
    struct student *prev1;
    struct student *next1;
};
struct course
{
    struct course *prev;
    struct course *next;
    struct student *sstart;
    int Cno;
};
struct course *cstart = NULL;

void course_insertion(int cno)
{
    struct course *temp = (struct course *)malloc(sizeof(struct course));
    temp->Cno = cno;
    temp->next = temp->prev = NULL;
    temp->sstart = NULL;
    if (cstart == NULL)
    {
        cstart = temp;
        return;
    }
    struct course *curr = cstart;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    temp->prev = curr;
}
void student_insertion(int cno, int sid)
{
    struct student *newStudent = (struct student *)malloc(sizeof(struct student));
    newStudent->id = sid;
    newStudent->next1 = newStudent->prev1 = NULL;

    struct course *curr = cstart;
    while (curr != NULL)
    {
        if (curr->Cno == cno)
        {
            if (curr->sstart == NULL)
            {
                curr->sstart = newStudent;
            }
            else
            {
                struct student *temp = curr->sstart;
                while (temp->next1 != NULL)
                {
                    temp = temp->next1;
                }
                temp->next1 = newStudent;
                newStudent->prev1 = temp;
            }
            break;
        }
        curr = curr->next;
    }
}
void delete_student(int cno, int sid)
{
    if (cstart == NULL)
    {
        cout << "List is empty" << endl;
    }
    else
    {
        struct course *curr = cstart;
        while (curr != NULL && curr->Cno != cno)
        {
            curr = curr->next;
        }
        if (curr != NULL)
        {
            struct student *Scurr = curr->sstart;
            while (Scurr != NULL && Scurr->id != sid)
            {
                Scurr = Scurr->next1;
            }
            if (Scurr != NULL)
            {
                if (Scurr->prev1 != NULL)
                {
                    Scurr->next1->prev1 = Scurr->prev1;
                    Scurr->prev1->next1 = Scurr->next1;
                }
                else
                {
                    curr->sstart = Scurr->next1;
                }
                free(Scurr);
            }
            else
            {
                cout << "student id not found." << endl;
            }
        }
        else
        {
            cout << "Course not found." << endl;
        }
    }
}

void delete_course(int cno)
{
    if (cstart == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    if (cstart->Cno == cno)
    {
        free(cstart);
        return;
    }
    struct course *curr = cstart;
    while (curr != NULL)
    {
        if (curr->Cno == cno)
        {
            break;
        }
        curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    free(curr);
}
void print()
{
    struct course *curr_c = cstart;
    while (curr_c != NULL)
    {
        cout << "The course is: " << curr_c->Cno << endl;
        cout << "Following are the student ids on this course: " << endl;
        struct student *curr_s = curr_c->sstart;
        while (curr_s != NULL)
        {
            cout << curr_s->id << " ";
            curr_s = curr_s->next1;
        }
        cout << endl;
        curr_c = curr_c->next;
    }
}
int main()
{
    course_insertion(1);
    course_insertion(3);
    course_insertion(4);
    course_insertion(2);
    course_insertion(5);
    student_insertion(1, 6);
    student_insertion(1, 5);
    student_insertion(3, 5);
    delete_course(4);
    delete_student(1, 6);
    delete_student(3, 5);
    print();
}