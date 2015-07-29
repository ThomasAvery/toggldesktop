//
//  DisplayCommand.h
//  TogglDesktop
//
//  Created by Tanel Lebedev on 13/05/14.
//  Copyright (c) 2014 Toggl Desktop Developers. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TimeEntryViewItem.h"
#import "Settings.h"

@interface DisplayCommand : NSObject
@property BOOL open;
@property NSMutableArray *timeEntries;
@property NSMutableArray *timeline;
@property TimeEntryViewItem *timeEntry;
@property Settings *settings;
@property uint64_t user_id;
@end
