#include "AgendaUI.h"
#include "User.h"
#include <algorithm>
#include <cstdio>
#include <list>
AgendaUI::AgendaUI() {
    currentUser_ = nullptr;
}

void AgendaUI::startAgenda(void) {
    agendaService_.startAgenda();
}

void AgendaUI::getOperation(void) {
    std::string op;
    
    startAgenda();
    while (!executeOperation(getCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
}

std::string AgendaUI::getCmd(void) {
    std::string cmd;
    printMainScreen();
    std::cin >> cmd;
    
    return cmd;
}

void AgendaUI::printMainScreen(void) {
    std::cout << "-----------------------Agenda---------------------"<< "\n"
    << "Action:" << "\n"
    << "l   - log in Agenda by user name and password" << "\n"
    << "r   - register an Agenda account" << "\n"
    << "q   - quit Agenda" << "\n"
    << "--------------------------------------------------" << "\n" << "\n"
    << "Agenda : $" << std::flush;
}

bool AgendaUI::executeOperation(std::string op) {
    if (!([&](void) {return op == "r"  || op == "l"  || op == "dc"  ||
        op == "q"  || op == "o"  || op == "lu"  ||
        op == "cm" || op == "la" || op == "las" ||
        op == "lap" || op == "qm" || op == "qt" ||
        op == "dm" || op == "da";}())) {
            return false;
        }
    
    if (op == "l") userLogIn();
    else if (op == "r") userRegister();
    else if (op == "q") quitAgenda();
    else if (op == "o") userLogOut();
    else if (op == "dc") deleteUser();
    else if (op == "lu") listAllUsers();
    else if (op == "cm") createMeeting();
    else if (op == "la") listAllMeetings();
    else if (op == "las") listAllSponsorMeetings();
    else if (op == "lap") listAllParticipateMeetings();
    else if (op == "qm") queryMeetingByTitle();
    else if (op == "qt") queryMeetingByTimeInterval();
    else if (op == "dm") deleteMeetingByTitle();
    else if (op == "da") deleteAllMeetings();
    
    return true;
}

void AgendaUI::userLogIn() {
    std::cout << "\n"
    << "[log in] [User name] [password]" << "\n"
    << "[log in] " << std::flush;
    
    std::string userName;
    std::string password;
    std::cin >> userName >> password;
    currentUser_ = new User(userName, password, "", "");
    bool isLogInSucceed = agendaService_.userLogIn(userName, password);
    if (!isLogInSucceed) {
        std::cout << "[error] log in fail!" << std::endl;
        printDelayed();
        while (!executeOperation(getCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getCmd());
    } else {
        std::cout << "[log in] succeed!" << std::endl;
        printDelayed();
        while (!executeOperation(getUserCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getUserCmd());
    }
}

std::string AgendaUI::getUserCmd(void) {
    std::string userCmd;
    
    printUserScreen();
    std::cin >> userCmd;
    return userCmd;
}

void AgendaUI::printUserScreen(void) {
    std::cout << "\n" << "----------------------Agenda---------------" << "\n"
    << "Action : $" << "\n"
    << "o   - log out Agenda" << "\n"
    << "dc  - delate Agenda account" << "\n"
    << "lu  - list all Agenda user" << "\n"
    << "cm  - create a meetings" << "\n"
    << "la  - list all meetings" << "\n"
    << "las - list all sponsor meetings" << "\n"
    << "lap - list all participate meetings" << "\n"
    << "qm  - query meeting by title" << "\n"
    << "qt  - query meeting by time interval" << "\n"
    << "dm  - delete meeting by title" << "\n"
    << "da  - delete all meetings" << "\n"
    << "-----------------------------------------------" << "\n" << "\n"
    << "Agenda@pear # " << std::flush;
}

void AgendaUI::userRegister(void) {
    std::cout << "[register] [user name] [password] [email] [phone]" << "\n"
    << "[register] " << std::flush;
    
    std::string name, password, email, phone;
    std::cin >> name >> password >> email >> phone;
    //format judgement
    
    bool isRegisterSuccess = agendaService_.userRegister(name, password, email, phone);
    if (isRegisterSuccess) {
        currentUser_ = new User(name, password, "", "");
        std::cout << "\n" << "[register] succeed!" << std::endl;
        printDelayed();
        while (!executeOperation(getUserCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getUserCmd());
    } else {
        std::cout << "[error] register fail!";
        printDelayed();
        while (!executeOperation(getCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getCmd());
    }
}

void AgendaUI::quitAgenda(void) {
    agendaService_.quitAgenda();
}


void AgendaUI::userLogOut(void) {
    currentUser_ = nullptr;
    while (!executeOperation(getCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getCmd());
}

void AgendaUI::deleteUser(void) {
    bool isDeleteSucceed = agendaService_.deleteUser(currentUser_->getName(), currentUser_->getPassword());
    if (isDeleteSucceed) {
        std::cout << "[delete agenda account] succeed!" << std::endl;
        printDelayed();
        while (!executeOperation(getCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getCmd());
    } else {
        std::cout << "[error] delete agenda account fail!" << std::endl;
        printDelayed();
        while (!executeOperation(getUserCmd())){
            std::cout << "[error] wrong commend!" << std::endl;
            printDelayed();
        }
        //executeOperation(getUserCmd());
    }
}

void AgendaUI::listAllUsers(void) {
    std::list<User> userList = agendaService_.listAllUsers();
    printUserList(userList);
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::printUserList(std::list<User> users) {
    std::cout << "\n" << "[list all meetings]" << "\n" << std::endl;
    std::cout << "name" << "\t" << "email" << "\t" << "phone" << std::endl;
    
    std::list<User>::iterator iterOfUserList = users.begin();
    for (; iterOfUserList != users.end(); iterOfUserList++) {
        std::cout << iterOfUserList->getName() << "\t"
        << iterOfUserList->getEmail() << "\t"
        << iterOfUserList->getPhone() << std::endl;
    }
}

void AgendaUI::createMeeting(void) {
    std::cout << "\n" << "[create meeting] [title] [participator] "
    << "[start time<yyyy-mm-dd/hh:mm> [end time<yyyy-mm-dd/hh:mm>]]"
    << "\n" << "[create meeting] " << std::flush;
    
    std::string title, participator, startTime, endTime;
    std::cin >> title >> participator >> startTime >> endTime;
    //repeat judgement
    bool isCreateMeetingSucceed = agendaService_.createMeeting(currentUser_->getName(),
                                                               title,
                                                               participator,
                                                               startTime,
                                                               endTime);
    if (isCreateMeetingSucceed)
        std::cout << "[create meeting] succeed!" << std::endl;
    else
        std::cout << "[error] create meeting fail!" << std::endl;
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::listAllMeetings(void) {
    std::cout << "\n" << "[list all meetings]" << std::endl;
    
    std::list<Meeting> listOfMeeting = agendaService_.listAllMeetings(currentUser_->getName());
    printMeetings(listOfMeeting);
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << "\n" << "[list all meetings]" << std::endl;
    
    std::list<Meeting> listOfSponsorMeeting = agendaService_.listAllSponsorMeetings(currentUser_->getName());
    printMeetings(listOfSponsorMeeting);
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << "\n" << "[list all meetings]" << std::endl;
    std::list<Meeting> listOfParticipatorMeeting = agendaService_.listAllParticipateMeetings(currentUser_->getName());
    printMeetings(listOfParticipatorMeeting);
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << "[query meeting] [title]" << "\n"
    << "[query meeting] " << std::flush;
    std::string title;
    std::cin >> title;
    
    std::list<Meeting> meeting = agendaService_.meetingQuery(title);
    
    if (meeting.size() == 0) {
        std::cout << "[error] meeting not found!" << std::endl;
    } else {
        printMeetings(meeting);
    }
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << "[query meeting] [start time<yyyy-mm-dd/hh:mm>] "
    << "[end time<yyyy-mm-dd/hh:mm>]" << "\n"
    << "[query meeting]"
    << std::endl;
    std::string startTime, endTime;
    std::cin >> startTime >> endTime;
    
    std::list<Meeting> listMeeting = agendaService_.meetingQuery(currentUser_->getName(),
                                                                 startTime, endTime);
    printMeetings(listMeeting);
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << "[delete meeting] [title]" << "\n"
    << "[delete meeting] " << std::flush;
    
    std::string title;
    std::cin >> title;
    
    bool isDeleteMeetingSucceed = agendaService_.deleteMeeting(currentUser_->getName(), title);
    
    if (isDeleteMeetingSucceed)
        std::cout << "[delete meeting by title] succeed!" << std::endl;
    else
        std::cout << "[error] delete meeting fail!" << std::endl;
    
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::deleteAllMeetings(void) {
    bool isDeleteAllMeetingSucceed = agendaService_.deleteAllMeetings(currentUser_->getName());
    if (isDeleteAllMeetingSucceed)
        std::cout << "[delete all meetings] succeed!" << std::endl;
    else
        std::cout << "[error] delete all meeting fail!" << std::endl;
    
    printDelayed();
    while (!executeOperation(getUserCmd())){
        std::cout << "[error] wrong commend!" << std::endl;
        printDelayed();
    }
    //executeOperation(getUserCmd());
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::list<Meeting>::iterator iter = meetings.begin();
    std::cout << "title" << "\t" << "sponsor" << "\t"
    << "participator" << "\t" << "start time" << "\t"
    << "end time" << std::endl;
    
    for (; iter != meetings.end(); iter++) {
        std::cout << iter->getTitle() << "\t"
        << iter->getSponsor() << "\t"
        << iter->getParticipator() << "\t"
        << Date::dateToString(iter->getStartDate()) << "\t"
        << Date::dateToString(iter->getEndDate()) << std::endl;
    }
}

void AgendaUI::printDelayed(void) {
    std::cout << "press any key to continue!";
    getchar();
    getchar();
}