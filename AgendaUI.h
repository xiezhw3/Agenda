#ifndef AGENDAUI_H
#define AGENDAUI_H

#include "AgendaService.h"
#include <iostream>
#include <string>
#include <list>

class AgendaUI {
public:
    AgendaUI();
    void getOperation(void);
    
private:
    // task functions
    void startAgenda(void);
    bool executeOperation(std::string op);
    void userLogIn(void);
    void userRegister(void);
    void quitAgenda(void);
    void userLogOut(void);
    void deleteUser(void);
    void listAllUsers(void);
    void createMeeting(void);
    void listAllMeetings(void);
    void listAllSponsorMeetings(void);
    void listAllParticipateMeetings(void);
    void queryMeetingByTitle(void);
    void queryMeetingByTimeInterval(void);
    void deleteMeetingByTitle(void);
    void deleteAllMeetings(void);
    void printMeetings(std::list<Meeting> meetings);
    void printMainScreen(void);
    void printUserScreen(void);
    void printUserList(std::list<User> users);
    void printDelayed(void);
    // own functions
    std::string getCmd(void);
    std::string  getUserCmd(void);
    // dates
    User *currentUser_;
    AgendaService agendaService_;
};

#endif
