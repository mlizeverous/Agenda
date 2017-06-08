#include "Storage.h"
#include "Meeting.h"
#include "AgendaService.h"
#include <list>
#include <string>

AgendaService::AgendaService(){
	storage_ = Storage::getInstance();
}

AgendaService::~AgendaService(){
	if (storage_ != NULL) {
		delete storage_;
	}
	storage_ = NULL;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
	if (storage_->queryUser([=] (const User& u) {
	    if (u.getName() == userName && u.getPassword() == password)
	        return true;
	    else
	        return false;}).empty()) {
	            return false;
	        } else {
	            return true;
	        }
}

bool AgendaService::userRegister(std::string userName, std::string password,
                    std::string email, std::string phone){
                    if (storage_->queryUser([userName] (const User& u) {
                        if (u.getName() == userName) return true;
                        else return false; }).empty()) {
                            User uu(userName, password, email, phone);
                            storage_->createUser(uu);
                            return true;
                        } else {
                            return false;
                        }
                    }

bool AgendaService::deleteUser(std::string userName, std::string password) {

	    if (storage_->deleteUser([=] (const User& u) {
	        if (u.getName() == userName && u.getPassword() == password)
	            return true;
	        else return false;}) == 1) {
	            deleteAllMeetings(userName);
	            if (storage_->deleteMeeting([=] (const Meeting& m) {
                if (m.getParticipator() == userName) return true;
                else return false; })) {
                    return true;
                 } // else {
                   // return false;
                // }
	               return true;
	            } else {
	                return false;
	            }
}	// a user can only delete itself


std::list<User> AgendaService::listAllUsers(void) {
	std::list<User> users = storage_->queryUser([] (const User& u) {return true;});
	return users;
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate) {

                     Date start = Date::stringToDate(startDate);
                     Date end = Date::stringToDate(endDate);

                     if (userName == participator) return false;

                     if (Date::isValid(start) == 0 || Date::isValid(end) == 0) return false;

                     if (start >= end) return false;

                     if (storage_->queryUser([userName] (const User& u) {
                        if (u.getName() == userName) return true;
                        else return false; }).empty()) return false;

                     if (storage_->queryUser([participator] (const User& u) {
                        if (u.getName() == participator) return true;
                        else return false; }).empty()) return false;

                    if (storage_->queryMeeting([title] (const Meeting &m) {
                    	if (m.getTitle() == title) return true;
                    	else return false; }).empty() == 0) return false;

                     if (storage_->queryMeeting([=] (const Meeting& m) {
                        if ((start >= m.getStartDate() && start < m.getEndDate() ||
                        end > m.getStartDate() && end <= m.getEndDate()) &&
                        (m.getSponsor() == userName || m.getParticipator() == userName
                        || m.getSponsor() == participator || m.getParticipator() == participator)) return true;
                        else if (start <= m.getStartDate() && end >= m.getEndDate()
                        && (m.getSponsor() == userName || m.getParticipator() == userName
                        || m.getSponsor() == participator || m.getParticipator() == participator)) return true;
                        else return false; }).empty()) {
                            Meeting meeting(userName, participator, start, end, title);
                            // std::cout << ".." << std::endl;
                            storage_->createMeeting(meeting);
                            return true;
                        } else {
                        	return false;
                        }

                     }

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string title) {
    std::list<Meeting> m = storage_->queryMeeting([=] (const Meeting& m) {
        if ((m.getSponsor() == userName || m.getParticipator() == userName) && m.getTitle() == title) return true;
        else return false;});
        return m;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
                                  std::string endDate) {
                                  Date startdate = Date::stringToDate(startDate);
                                  Date enddate = Date::stringToDate(endDate);
                                  std::list<Meeting> m = storage_->queryMeeting([=] (const Meeting& m1) {
                                    if ((m1.getSponsor() == userName || m1.getParticipator() == userName)
                                    && !(m1.getStartDate() > enddate || m1.getEndDate() < startdate)) return true;
                                    else return false; });
                                  return m;
                                  }

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    std::list<Meeting> m = storage_->queryMeeting([=] (const Meeting& mm) {
    if (mm.getSponsor() == userName || mm.getParticipator() == userName) return true;
        else return false;});
    return m;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    std::list<Meeting> m = storage_->queryMeeting([=] (const Meeting &meeting) {
        if (meeting.getSponsor() == userName) return true;
        else return false;});
    return m;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
     std::list<Meeting> m = storage_->queryMeeting([=] (const Meeting &meeting) {
        if (meeting.getParticipator() == userName) return true;
        else return false;});
    return m;
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    if (storage_->deleteMeeting([=] (const Meeting& m) {
        if (m.getSponsor() == userName && m.getTitle() == title) return true;
        else return false; }) > 0) {
            return true;
        } else {
            return false;
        }
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    if (storage_->deleteMeeting([=] (const Meeting& m) {
        if (m.getSponsor() == userName) return true;
        else return false; }) > 0) {
            return true;
        } else {
            return false;
        }
}

void AgendaService::startAgenda(void) {}

void AgendaService::quitAgenda(void) {
    storage_->sync();
}

