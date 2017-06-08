#include "AgendaService.h"
#include "AgendaUI.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

AgendaUI::AgendaUI() {
	startAgenda();
}

void AgendaUI::OperationLoop(void) {
    if (userName_.empty() && userPassword_.empty()) return;
    std::cout << std:: endl;
    std::cout << "---------------------------------*~Agenda~*---------------------------------" << std::endl << std::endl
                   << "\t" << "Action : " << std::endl
                   << "\t" << "o       ---- Logout Agenda" << std::endl
                   << "\t" << "dc      ---- Delete Agenda account" << std::endl
                   << "\t" << "lu      ---- List all Agenda users" << std::endl
                   << "\t" << "cm      ---- Create a meeting " << std::endl
                   << "\t" << "la      ---- List all meetings " << std::endl
                   << "\t" << "las     ---- List all sponsor meetings " << std::endl
                   << "\t" << "lap     ---- List all participator meetings " << std::endl
                   << "\t" << "qm      ---- Query meetings by title " << std::endl
                   << "\t" << "qt      ---- Query meetings by time interval " << std::endl
                   << "\t" << "dm      ---- Delete a meeting by title" << std::endl
                   << "\t" << "da      ---- Delete all meetings" << std::endl << std::endl;
    std::cout << "*~--------------------------------------------------------------------------~*"
    << std::endl << std::endl << std::endl;
    std::cout << "Agenda@ " << userName_ << ": # ";
    std::string ss = getOperation();
	if (ss != "o" && ss != "dc" && ss != "lu" && ss != "cm" && ss !="la"
	    && ss !="las" && ss != "lap" && ss != "qm" && ss != "qt" &&
	    ss != "dm" && ss != "da") {
	    std::cout << "[Error] : Invalid order, please enter again" << std::endl;
	    OperationLoop();
	    // startAgenda();
	} else {
	    executeOperation(ss);
	}
}

  // task functions
void AgendaUI::startAgenda(void) {
	userName_.clear();
	userPassword_.clear();
	std::cout << std:: endl;
	std::cout << "---------------------------------*~Agenda~*---------------------------------" << std::endl << std::endl;
	std::cout << "\t" << "Action : " << std::endl;
	std::cout << "\t" << "l       ---- Login an Agenda by user name and password " << std::endl;
	std::cout << "\t" << "r       ---- Register an Agenda account " << std::endl;
	std::cout << "\t" << "q       ---- Quit Agenda " << std::endl << std::endl;
	std::cout << "*~-------------------------------------------------------------------------~*" << std::endl << std::endl << std::endl;
	std::cout << "Agenda : ~$ ";
	std::string ss = getOperation();
	if (ss != "l" && ss != "r" && ss != "q") {
	    std::cout << "[Error] : Invalid order, please enter again" << std::endl;
	    startAgenda();
	} else {
	    executeOperation(ss);
	}
}

std::string AgendaUI::getOperation() {
    std::string temp;
    std::cin >> temp;
    return temp;
}

bool AgendaUI::executeOperation(std::string s) {
        if (s == "l") {
            userLogIn();
            return true;
        } else if (s == "r") {
            userRegister();
            return true;
        } else if (s == "q") {
            quitAgenda();
            return true;
        }
        if (s == "o") {
            userLogOut();
            return true;
        } else if (s == "dc") {
            deleteUser();
            return true;
        } else if (s == "lu") {
            listAllUsers();
            return true;
        } else if (s == "cm") {
            createMeeting();
            return true;
        } else if (s == "la") {
            listAllMeetings();
            return true;
        } else if (s == "las") {
            listAllSponsorMeetings();
            return true;
        } else if (s == "lap") {
            listAllParticipateMeetings();
            return true;
        } else if (s == "qm") {
            queryMeetingByTitle();
            return true;
        } else if (s == "qt") {
            queryMeetingByTimeInterval();
            return true;
        } else if (s == "dm") {
            deleteMeetingByTitle();
            return true;
        } else if (s == "da") {
            deleteAllMeetings();
            return true;
        }

    return false;
}

void AgendaUI::userLogIn(void) {
    std::cout << std::endl;
    std::cout << "[Log in] : [User Name] [Password]" << std::endl;
    std::cout << "[Log in] : ";
    std::cin >> userName_ >> userPassword_;
    if (agendaService_.userLogIn(userName_, userPassword_)) {
        std::cout << "[Log in] : Succeed!" << std::endl;
        OperationLoop();
    } else {
        std::cout << "[error] : Log in fail!" << std::endl;
        startAgenda();
    }
}

void AgendaUI::userRegister(void) {

    std::cout << std::endl;
    std::cout << "[Register] : [User Name] [Password] [Email] [Phone]" << std::endl
                   << "[Register] :  ";
    std::string name, password, email, phone;
    std:: cin >> name >> password >> email >> phone;
    if (agendaService_.userRegister(name, password, email, phone)) {
        std::cout << "[Register] : Succeed!" << std::endl;
        startAgenda();
    } else {
        std::cout << "[Error] : Register fail! " << std::endl;
        startAgenda();
    }
}

void AgendaUI::quitAgenda(void) {
    std::cout << "*----------------------------------*~Agenda~*---------------------------------*" << std::endl << std::endl;
    std::cout << "\t" << "~~~~~~~\\(> o <)/~~~~~~~THANKS FOR USING "
    << "~~~~~~~\\(> o <)/~~~~~~~"
    << std::endl << std::endl;
    std::cout << "*~----------------------------------------------------------------------------~*" << std::endl << std::endl;
    agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
    userName_.clear();
    userPassword_.clear();
    startAgenda();
}

void AgendaUI::deleteUser(void) {
    std::cout << std::endl;
    agendaService_.deleteUser(userName_, userPassword_);
    std::cout << "[Delete Agenda Account] : Succeed! " <<std::endl;
    userName_.clear();
    userPassword_.clear();
    startAgenda();
}

void AgendaUI::listAllUsers(void) {
    std::cout << std::endl;
    std::cout << "[List All Users] :" << std::endl << std::endl;
    std::cout << std::left << std::setw(10) << "NAME" << std::setw(20)
    << "EMAIL" << std::setw(20) << "PHONE" << std::endl;

    std::list<User> user = agendaService_.listAllUsers();
    std::list<User>::iterator u;

    for (u = user.begin(); u != user.end(); u++) {
        std::cout << std::left << std::setw(10) << u->getName()
        << std::setw(20) <<  u->getEmail() << std::setw(20)
        <<  u->getPhone() << std::endl;
    }
    // system("pause");
    OperationLoop();
}

void AgendaUI::createMeeting(void) {
    std::cout << std::endl;
    std::cout << "[Create Meeting] : [Title] [Participator] [Start Time(yyyy-mm-dd/hh:mm)] [End Time(yyyy-mm-dd/hh:mm)]"
                   << std::endl;
     std::cout << "[Create Meeting] : ";
     std:: string title, participator, stime, etime;
     std::cin >> title >> participator >> stime >> etime;
     if (agendaService_.createMeeting(userName_, title, participator, stime, etime)) {
        std::cout << "[Create Meeting] : Succeed! " <<std::endl;
        // OperationLoop();
     } else {
        std::cout << "[Error] : Create meeting failed!" << std::endl;
     }
    // system("pause");
    OperationLoop();
}

void AgendaUI::listAllMeetings(void) {
    std::cout << std::endl;
    std::cout << "[List All Meetings] :" << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "TITLE" << std::setw(20)
                   << "SPONSOR" << std::setw(20) << "PARTICIPATOR"
                   << std::setw(20) << "START TIME" << std::setw(20)
                   << "END TIME" << std::endl;

    std::list<Meeting> meeting = agendaService_.listAllMeetings(userName_);
    printMeetings(meeting);
    // system("pause");
    OperationLoop();
    }


void AgendaUI::listAllSponsorMeetings(void) {
    std::cout << std::endl;
    // std::cout << "[List All Sponsor Meetings] : " << std::endl;
    std::cout << "[List All Sponsor Meetings] : " << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "TITLE" << std::setw(20)
                   << "SPONSOR" << std::setw(20) << "PARTICIPATOR"
                   << std::setw(20) << "START TIME" << std::setw(20)
                   << "END TIME" << std::endl;

    std::list<Meeting> meeting = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(meeting);
    // system("pause");
    OperationLoop();
}

void AgendaUI::listAllParticipateMeetings(void) {
    std::cout << std::endl;
    // std::cout << "[List All Participate Meetings] : " << std::endl;
    std::cout << "[List All Participate Meetings] :" << std::endl << std::endl;
    std::cout << std::left << std::setw(20) << "TITLE" << std::setw(20)
                   << "SPONSOR" << std::setw(20) << "PARTICIPATOR"
                   << std::setw(20) << "START TIME" << std::setw(20)
                   << "END TIME" << std::endl;

    std::list<Meeting> meeting = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(meeting);
    // system("pause");
    OperationLoop();
}

void AgendaUI::queryMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[Query Meeting] : [Title] " << std::endl;
    std::cout << "[Query Meeting] : ";
     std::string title;
    std::cin >> title;
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "TITLE" << std::setw(20)
                   << "SPONSOR" << std::setw(20) << "PARTICIPATOR"
                   << std::setw(20) << "START TIME" << std::setw(20)
                   << "END TIME" << std::endl;

    std::list<Meeting> meeting = agendaService_.meetingQuery(userName_, title);
    printMeetings(meeting);
    // system("pause");
    OperationLoop();
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    std::cout << std::endl;
    std::cout << "[Query Meeting] : [Start Time(yyyy-mm-dd/hh:mm)] [End Time(yyyy-mm-dd/hh:mm)] " << std::endl;
    std::cout << "[Query Meeting] :";
    std::string stime, etime;
    std::cin >> stime >> etime;
    std::cout << std::endl;
    std::cout << std::left << std::setw(20) << "TITLE" << std::setw(20)
                   << "SPONSOR" << std::setw(20) << "PARTICIPATOR"
                   << std::setw(20) << "START TIME" << std::setw(20)
                   << "END TIME" << std::endl;

    std::list<Meeting> meeting = agendaService_.meetingQuery(userName_, stime, etime);
    printMeetings(meeting);
    /*std::cout << "[Return] : return     ---- Return to menu" << std::endl;
    std::cout << "[Return] : ";
    std::string s = getOperation();
    if (s != "return") {
        std::cout << "[Error] : Invalid order, please enter again" << std::endl;
        std::cout << "[Return] : ";
	    // startAgenda();
	} else {
	    executeOperation(s);
    }*/
    // system("pause");
    OperationLoop();
}

void AgendaUI::deleteMeetingByTitle(void) {
    std::cout << std::endl;
    std::cout << "[Delete Meeting] [Title] : " << std::endl;
    std::cout << "[Delete Meeting] :";
    std::string title;
    std::cin >> title;
    std::cout << std::endl;
    if (agendaService_.deleteMeeting(userName_, title)) {
        std::cout << "[Delete Meeting by Title] :  Succeed!" << std::endl;
    } else {
        std::cout << "[Error] : Delete Meeting fail!" << std::endl;
    }
    // system("pause");
    OperationLoop();
}

void AgendaUI::deleteAllMeetings(void) {
    std::cout << std::endl;
    if (agendaService_.deleteAllMeetings(userName_)) {
        std::cout << " [Delete All Meeting] :  Succeed!" << std::endl;
    } else {
        std::cout << "[Error] : Delete Meeting fail!" << std::endl;
    }
    // system("pause");
    OperationLoop();
}



void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::list<Meeting>::iterator m;
    for (m = meetings.begin(); m != meetings.end(); m++) {
        std::cout << std::left << std::setw(20) << m->getTitle() << std::setw(20)
                   << m->getSponsor() << std::setw(20) << m->getParticipator()
                   << std::setw(20) << Date::dateToString(m->getStartDate()) << std::setw(20)
                   << Date::dateToString(m->getEndDate()) << std::endl;
    }
}
  // datescdmnuvr
