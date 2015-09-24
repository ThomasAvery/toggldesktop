// Copyright 2014 Toggl Desktop developers.

#ifndef SRC_RELATED_DATA_H_
#define SRC_RELATED_DATA_H_

#include <vector>
#include <set>
#include <string>
#include <map>

#include "./autocomplete_item.h"
#include "./timeline_event.h"
#include "./types.h"

namespace toggl {

class AutotrackerRule;
class Client;
class Project;
class Tag;
class Task;
class TimeEntry;
class Workspace;

template<typename T>
T *modelByID(const Poco::UInt64 id, std::vector<T *> const *list);

template <typename T>
T *modelByGUID(const guid GUID, std::vector<T *> const *list);

class RelatedData {
 public:
    std::vector<Workspace *> Workspaces;
    std::vector<Client *> Clients;
    std::vector<Project *> Projects;
    std::vector<Task *> Tasks;
    std::vector<Tag *> Tags;
    std::vector<TimeEntry *> TimeEntries;
    std::vector<AutotrackerRule *> AutotrackerRules;
    std::vector<TimelineEvent *> TimelineEvents;

    void Clear();

    Task *TaskByID(const Poco::UInt64 id) const;
    Client *ClientByID(const Poco::UInt64 id) const;
    Project *ProjectByID(const Poco::UInt64 id) const;
    Tag *TagByID(const Poco::UInt64 id) const;
    Workspace *WorkspaceByID(const Poco::UInt64 id) const;
    TimeEntry *TimeEntryByID(const Poco::UInt64 id) const;

    void TagList(std::vector<std::string> *) const;
    void WorkspaceList(std::vector<Workspace *> *) const;
    void ClientList(std::vector<Client *> *) const;

    TimeEntry *TimeEntryByGUID(const guid GUID) const;
    Tag *TagByGUID(const guid GUID) const;
    Project *ProjectByGUID(const guid GUID) const;
    Client *ClientByGUID(const guid GUID) const;
    TimelineEvent *TimelineEventByGUID(const guid GUID) const;

    Poco::Int64 NumberOfUnsyncedTimeEntries() const;

    // Find the time entry that was stopped most recently
    TimeEntry *LatestTimeEntry() const;

    // Collect visible timeline events
    std::vector<TimelineEvent *> VisibleTimelineEvents() const;

    // Collect visible time entries
    std::vector<TimeEntry *> VisibleTimeEntries() const;

    Poco::Int64 TotalDurationForDate(const TimeEntry *match) const;

    // avoid duplicates
    bool HasMatchingAutotrackerRule(const std::string lowercase_term) const;

    error DeleteAutotrackerRule(const Poco::Int64 local_id);

    void TimeEntryAutocompleteItems(std::vector<AutocompleteItem> *) const;
    void MinitimerAutocompleteItems(std::vector<AutocompleteItem> *) const;
    void ProjectAutocompleteItems(std::vector<AutocompleteItem> *) const;

    void ProjectLabelAndColorCode(
        const TimeEntry *te,
        std::string *workspace_name,
        std::string *project_and_task_label,
        std::string *task_label,
        std::string *project_label,
        std::string *client_label,
        std::string *color_code) const;

    AutotrackerRule *FindAutotrackerRule(const TimelineEvent event) const;

 private:
    void timeEntryAutocompleteItems(
        std::set<std::string> *unique_names,
        std::vector<AutocompleteItem> *list) const;

    void taskAutocompleteItems(
        std::set<std::string> *unique_names,
        std::map<Poco::UInt64, std::string> *ws_names,
        std::vector<AutocompleteItem> *list) const;

    void projectAutocompleteItems(
        std::set<std::string> *unique_names,
        std::map<Poco::UInt64, std::string> *ws_names,
        std::vector<AutocompleteItem> *list) const;

    void workspaceAutocompleteItems(
        std::set<std::string> *unique_names,
        std::map<Poco::UInt64, std::string> *ws_names,
        std::vector<AutocompleteItem> *list) const;

    Client *clientByProject(Project *p) const;
};

template<typename T>
void clearList(std::vector<T *> *list);

}  // namespace toggl

#endif  // SRC_RELATED_DATA_H_
