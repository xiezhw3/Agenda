#include "AgendaService.h"

AgendaService::AgendaService() {
	storage_ = Storage::getInstance();
	serviceRunning_++;
}

AgendaService::~AgendaService() {
	if (!storage_)
		storage_ = nullptr;
	serviceRunning_--;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
	return !storage_->queryUser(
                               [&] (const User& user) {return user.getName() == userName &&
                                   user.getPassword() == password;}
                               ).empty();
}

bool AgendaService::userRegister(std::string userName, std::string password,
								 std::string email, std::string phone) {
	if (!storage_->queryUser(
                             [&] (const User& user) {return user.getName() == userName;}
                             ).empty())
		return false;
    
	User newUser(userName, password, email, phone);
	storage_->createUser(newUser);
	return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    if (!listAllMeetings(userName).empty()) {
        return false;
    }
    
	if (listAllSponsorMeetings(userName).empty()) {
		return (storage_->deleteUser([&] (const User& user) {return user.getName() == userName
            && user.getPassword() == password;}) > 0);
	}
	return false;
}

std::list<User> AgendaService::listAllUsers(void) {
	return storage_->queryUser([&] (const User& user) {return true;});
}

bool AgendaService::createMeeting(std::string userName, std::string title,
				   std::string participator, std::string startDate,
				   std::string endDate) {
    if (userName == participator)
        return false;
	if (!Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)))
		return false;
    
	if (!(storage_->queryMeeting([&] (const Meeting& meeting) {return (meeting.getSponsor() == userName &&
                                                                      meeting.getParticipator() == participator &&
                                                                      meeting.getTitle() == title);}
                                ).empty()))
		return false;
	if (!(meetingQuery(userName, startDate, endDate).empty()) ||
		!(meetingQuery(participator, startDate, endDate).empty()))
		return false;
    
	Meeting newMeeting(userName, participator, Date::stringToDate(startDate),
                       Date::stringToDate(endDate), title);
	storage_->createMeeting(newMeeting);
    
	return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string title) {
	return storage_->queryMeeting(
                                  [&](const Meeting& meeting) {return (meeting.getTitle() == title);}
                                  );
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
                                  			   std::string endDate) {
	std::list<Meeting> meetings;
    std::list<Meeting> meetingL = storage_->queryMeeting([&](const Meeting& meeting) {return true;});
	for (auto iter = meetingL.begin(); iter != meetingL.end(); iter++) {
		if (iter->getSponsor() == userName || iter->getParticipator() == userName) {
			if (timeConflict(Date::stringToDate(startDate), Date::stringToDate(endDate),
                             iter->getStartDate(), iter->getEndDate()))
                meetings.push_back(*iter);
		}
	}
    return meetings;
}

bool AgendaService::timeConflict(const Date& tDateBegin, const Date& tDateEnd,
								 const Date& rDateBegin, const Date& rDateEnd) {
	if (tDateBegin >= rDateBegin && tDateEnd <= rDateEnd)
		return true;
	if (tDateBegin <= rDateBegin && tDateEnd >= rDateEnd)
		return true;
	if (tDateBegin <= rDateEnd && tDateEnd >= rDateEnd)
		return true;
	if (tDateBegin <= rDateBegin && tDateEnd >= rDateBegin)
		return true;
	return false;
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
	return storage_->queryMeeting(
                                  [&](const Meeting& meeting) { return (meeting.getSponsor() == userName ||
                                                                        meeting.getParticipator() == userName); }
                                  );
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
	return storage_->queryMeeting(
                                  [&](const Meeting& meeting) { return meeting.getSponsor() == userName; }
                                  );
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
	return storage_->queryMeeting(
                                  [&](const Meeting& meeting) { return meeting.getParticipator() == userName; }
                                  );
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
	return (storage_->deleteMeeting(
                                    [&] (const Meeting& meeting) {return meeting.getSponsor() == userName && 
                                        meeting.getTitle() == title;}
                                    ) > 0);
}

bool AgendaService::deleteAllMeetings(std::string userName){
	return (storage_->deleteMeeting(
                                    [&] (const Meeting& meeting) {return meeting.getSponsor() == userName;}
                                    ) > 0);
}

void AgendaService::startAgenda(void) {
	storage_->sync();
}

void AgendaService::quitAgenda(void) {
	storage_->sync();
}

int AgendaService::serviceRunning_ = 0;





