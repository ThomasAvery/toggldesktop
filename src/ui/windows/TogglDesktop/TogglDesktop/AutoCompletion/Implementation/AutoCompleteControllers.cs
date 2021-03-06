using System;
using System.Collections.Generic;
using System.Linq;

namespace TogglDesktop.AutoCompletion.Implementation
{
    static class AutoCompleteControllers
    {
        public static AutoCompleteController ForTimer(IEnumerable<Toggl.TogglAutocompleteView> items)
        {
            var splitList = items.ToLookup(i => string.IsNullOrEmpty(i.Description));
            
            var entries = splitList[false];
            var projects = splitList[true];

            int entriesCount;
            int projectsCount;

            var list = new List<IAutoCompleteListItem>
            {
                new SimpleNoncompletingCategory("Time Entries",
                    entries.Select(i => new TimerItem(i, false)).ToList<IAutoCompleteListItem>().GetCount(out entriesCount)
                    ),
                new SimpleNoncompletingCategory("Projects",
                    projects.Select(i => new TimerItem(i, true)).ToList<IAutoCompleteListItem>().GetCount(out projectsCount)
                    )
            };

            return new AutoCompleteController(list, string.Format("Timer(entries: {0}, projects: {1})", entriesCount, projectsCount));
        }


        public static AutoCompleteController ForTags(IEnumerable<string> items, Func<string, bool> ignoreTag)
        {
            var list = items.Select(i => new StringItem(i, ignoreTag)).Cast<IAutoCompleteListItem>().ToList();

            return new AutoCompleteController(list, string.Format("Tags({0})", list.Count));
        }

        public static AutoCompleteController ForProjects(List<Toggl.TogglAutocompleteView> projects)
        {
            // categorise by workspace and client
            var list = NoProjectItem.Create()
                .Prepend(projects
                    .Where(p => p.ProjectID != 0) // TODO: get rid of these at an earlier stage (they are workspace entries which are not needed anymore)
                    .GroupBy(p => p.WorkspaceID)
                    .Select(ps => new WorkspaceCategory(
                        ps.First().WorkspaceName,
                        ps.GroupBy(p => p.ClientID)
                            .OrderBy(g => g.Key != 0) // TODO: decide how clients should be sorted
                            .Select(c =>
                            {
                                var projectItems = c.Select(ProjectItem.Create);
                                if (c.Key == 0)
                                    return projectItems;
                                var clientName = c.First().ClientLabel;
                                return new ClientCategory(clientName, projectItems.ToList<IAutoCompleteListItem>()).Yield<IAutoCompleteListItem>();
                            })
                            .SelectMany(i => i).ToList()
                        ))
                    ).ToList();

            return new AutoCompleteController(list, string.Format("Projects({0})", projects.Count));
        }

        public static AutoCompleteController ForDescriptions(List<Toggl.TogglAutocompleteView> items)
        {
            var list = items.Select(i => new TimerItem(i, false)).Cast<IAutoCompleteListItem>().ToList();

            // TODO: categorize by workspace/client/project?

            return new AutoCompleteController(list, string.Format("Descriptions({0})", list.Count));
        }

        public static AutoCompleteController ForClients(List<Toggl.TogglGenericView> clients)
        {
            // categorise by workspace
            var list =
                ((IAutoCompleteListItem)new NoClientItem()).Prepend(
                    clients.GroupBy(c => c.WID).Select(
                        cs =>
                            new WorkspaceCategory(cs.First().WorkspaceName,
                                cs.Select(ModelItem.Create).ToList<IAutoCompleteListItem>()
                                )
                    )
                ).ToList();

            return new AutoCompleteController(list, string.Format("Clients({0})", clients.Count));
        }

        public static AutoCompleteController ForWorkspaces(List<Toggl.TogglGenericView> list)
        {
            var items = list.Select(m => new ModelItem(m))
                .Cast<IAutoCompleteListItem>().ToList();

            return new AutoCompleteController(items, string.Format("Workspaces({0})", list.Count));
        }
    }
}