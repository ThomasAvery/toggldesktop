//
//  IdleNotificationWindowController.h
//  Toggl Desktop on the Mac
//
//  Created by Tanel Lebedev on 06/11/2013.
//  Copyright (c) 2013 Toggl Desktop Developers. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "IdleEvent.h"

@interface IdleNotificationWindowController : NSWindowController

@property IBOutlet NSTextField *idleSinceTextField;
@property IBOutlet NSTextField *idleAmountTextField;

- (IBAction)stopButtonClicked:(id)sender;
- (IBAction)ignoreButtonClicked:(id)sender;
- (IBAction)addIdleTimeAsNewTimeEntry:(id)sender;
- (IBAction)discardIdleAndContinue:(id)sender;

- (void)displayIdleEvent:(IdleEvent *)idleEvent;

@property IdleEvent *idleEvent;

@end
